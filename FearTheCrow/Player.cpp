//
// Created by Brandon Friend on 8/27/24.
//

#include "Player.h"
#include "Player.h"

#include <godot_cpp/variant/utility_functions.hpp>

namespace FearTheCrow {

    void Player::_bind_methods()
    {

        ClassDB::bind_method(D_METHOD("CreateCamera"), &Player::CreateCamera);
        ClassDB::bind_method(D_METHOD("_handle_ground_physics"), &Player::_handle_ground_physics);
        ClassDB::bind_method(D_METHOD("_handle_air_physics"), &Player::_handle_air_physics);
    }

    Player::Player() {}

    void Player::CreateHead()
    {
        HeadOriginalPosition = memnew(Node3D);
        add_child(HeadOriginalPosition);
        HeadOriginalPosition->set_transform(Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1.79, 0));

        Head = memnew(Node3D);
        HeadOriginalPosition->add_child(Head);

        CameraSmooth = memnew(Node3D);
        Head->add_child(CameraSmooth);
    }

    void Player::_ready()
    {
        CharacterBody3D::_ready();
        CreateHead();
        CreateCamera();
        CreateStepRays();
        CreateCollider();

        SetMouseMode(Input::MOUSE_MODE_CAPTURED);
    }
    void Player::CreateCamera()
    {
        camera = memnew(Camera3D);
        if (camera == nullptr) {
            UtilityFunctions::print("Camera creation failed!");
        } else {
            UtilityFunctions::print("Camera created successfully.");
        }

        CameraSmooth->add_child(camera);
        camera->set_position(Vector3(0, 1.5f, 0));

        if (camera->is_inside_tree()) {
            UtilityFunctions::print("Camera added to tree successfully.");
        } else {
            UtilityFunctions::print("Camera not added to tree.");
        }
    }

    void Player::SetMouseMode(const Input::MouseMode _mode) const {
        if(Engine::get_singleton()->is_editor_hint()) return;
        Input::get_singleton()->set_mouse_mode(_mode);
    }

    void Player::_process(double p_delta)
    {
        CharacterBody3D::_process(p_delta);
        //_handle_controller_look_input(p_delta);

    }




    void Player::_exit_tree()
    {
        CharacterBody3D::_exit_tree();
    }

    void Player::_physics_process(double p_delta)
    {
        CharacterBody3D::_physics_process(p_delta);
        if (Engine::get_singleton()->is_editor_hint()) return;

        if(is_on_floor())
            _last_frame_was_on_floor = Engine::get_singleton()->get_physics_frames();

        inputDir = Input::get_singleton()->get_vector("Left", "Right", "Forward", "Backward").normalized();
        wishDir = get_transform().basis.xform(Vector3(inputDir.x, 0, inputDir.y));
        cam_aligned_wish_dir = camera->get_global_transform().basis.xform(Vector3(inputDir.x, 0, inputDir.y));

        _handle_crouch(p_delta);

        if(!_handle_noclip(p_delta))
        {
            if(!_handle_water_physics(p_delta))
            {
                if(is_on_floor() || _snapped_to_stairs_last_frame)
                {
                    if(Input::get_singleton()->is_action_just_pressed("Jump") || (auto_bhop && Input::get_singleton()->is_action_pressed("Jump")))
                    {
                        Vector3 v = this->get_velocity();
                           v.y = jump_velocity;
                        this->set_velocity(v);
                    }
                    _handle_ground_physics(p_delta);
                }
                else
                {
                    _handle_air_physics(p_delta);
                }
            }

            if(!StepUpStairsCheck(p_delta))
            {
                _push_away_rigid_bodies();
                move_and_slide();
                SnapDownToStairsCheck();
            }
        }

        SmoothCamera(p_delta);

    }

    void Player::_enter_tree()
    {
        CharacterBody3D::_enter_tree();
    }

    void Player::_unhandled_input(const Ref<InputEvent>& p_event)
    {
        if(Input::get_singleton()->is_action_just_pressed("Pause"))
        {
            get_tree()->quit();
        }
        if (p_event->is_class("InputEventMouseMotion")) {
            auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
            rotate_y(-mouseMotionEvent->get_relative().x * look_sensitivity);
            camera->rotate_x(-mouseMotionEvent->get_relative().y * look_sensitivity);
            camera->set_rotation(Vector3(Math::clamp(camera->get_rotation().x , Math::deg_to_rad(-90.f), Math::deg_to_rad(90.f)) , camera->get_rotation().y, camera->get_rotation().z));
        }

        if(p_event->is_class("InputEventMouseButton") && p_event->is_pressed())
        {

            auto *mouseMotionEvent = dynamic_cast<InputEventMouseButton *>(*p_event);
            if(mouseMotionEvent->get_button_index() == MOUSE_BUTTON_WHEEL_UP)
            {
                noclip_speed_mult = Math::min(100.0, noclip_speed_mult * 1.1);
            }
            else if(mouseMotionEvent->get_button_index() == MOUSE_BUTTON_WHEEL_DOWN)
            {
                noclip_speed_mult = Math::max(0.1, noclip_speed_mult * 0.9);

            }
        }
    }

    void Player::_headbob_effect(double delta)
    {
        headbob_time += delta * this->get_velocity().length();
        camera->get_transform().origin = Vector3(
        cos(headbob_time * HEADBOB_FREQUENCY * 0.5) * HEADBOB_MOVE_AMOUNT,
        sin(headbob_time * HEADBOB_FREQUENCY) * HEADBOB_MOVE_AMOUNT,
        0);

    }

    void Player::_handle_controller_look_input(double delta)
    {
        if(Engine::get_singleton()->is_editor_hint()) return;
        Vector2 target_look = Input::get_singleton()->get_vector("look_left", "look_right", "look_down", "look_up").normalized();

        if (target_look.length() >= _cur_controller_look.length())
        {
            _cur_controller_look = _cur_controller_look.lerp(target_look, 5.0 * delta);
        }
        else
        {
            _cur_controller_look = target_look;
        }


        rotate_y(-_cur_controller_look.x * controller_look_sensitivity); // turn left and right
        camera->rotate_x(_cur_controller_look.y * controller_look_sensitivity); // look up and down
        camera->set_rotation(Vector3(Math::clamp(camera->get_rotation().x , Math::deg_to_rad(-90.f), Math::deg_to_rad(90.f)) , camera->get_rotation().y, camera->get_rotation().z)); // clamp up and down range
    }



    void Player::_handle_ground_physics(double delta)
    {

        float fDelta = static_cast<float>(delta);
        float cur_speed_in_wish_dir = this->get_velocity().dot(wishDir);
        float add_speed_till_cap = get_move_speed() - cur_speed_in_wish_dir;
        if(add_speed_till_cap > 0)
        {
            float accel_speed = ground_accel * fDelta * get_move_speed();
            accel_speed = Math::min(accel_speed, add_speed_till_cap);
            Vector3 v = this->get_velocity();
            v += accel_speed * wishDir;
            this->set_velocity(v);
        }

        //Apply Friction
        float control = Math::max(this->get_velocity().length(), ground_decel);
        float drop = control * ground_friction * fDelta;
        float new_speed = Math::max(this->get_velocity().length() - drop, 0.0f);
        if(this->get_velocity().length() > 0)
        {
            new_speed /= this->get_velocity().length();
        }
        Vector3 v = this->get_velocity();
        v *= new_speed;
        this->set_velocity(v);

        _headbob_effect(delta);
    }

    void Player::_handle_air_physics(double delta)
    {
        float fDelta = static_cast<float>(delta);
        Vector3 v = this->get_velocity();
        v.y -= 9.8f * fDelta;
        this->set_velocity(v);
        float cur_speed_in_wish_dir = this->get_velocity().dot(wishDir);
        float add_speed_till_cap = get_move_speed() - cur_speed_in_wish_dir;
        if(add_speed_till_cap > 0)
        {
            float accel_speed = air_accel * air_move_speed * fDelta;
            accel_speed = Math::min(accel_speed, add_speed_till_cap);
            v += accel_speed * wishDir;
            this->set_velocity(v);
        }

        if (is_on_wall()) {
            if (IsSurfaceTooSteep(get_wall_normal())) {
                set_motion_mode(MOTION_MODE_FLOATING);  // Enables smoother surf movement
            } else {
                set_motion_mode(MOTION_MODE_GROUNDED);
            }
            clip_velocity(get_wall_normal(), 1.0f, fDelta);  // Clip velocity for surf
        }

    }


    bool Player::IsSurfaceTooSteep(const Vector3 _normal)
    {
    return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
    }

    void Player::CreateCollider() {
        col = memnew(CollisionShape3D);
        col->set_name("Collider");

        Ref<CapsuleShape3D> colShape;
        colShape.instantiate();
        colShape->set_height(2.0f);
        colShape->set_radius(0.5f);
        col->set_shape(colShape);
        col->set_transform(Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0));
        this->add_child(col);
    }

    void Player::CreateBody() {
        body = memnew(MeshInstance3D);
        body->set_name("_body");
        body->set_cast_shadows_setting(GeometryInstance3D::ShadowCastingSetting::SHADOW_CASTING_SETTING_ON);
        body->set_position(Vector3(0.0f, 0.0f, 0.0f));
        col->add_child(body);
        if (const Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres"); meshLibrary.is_valid())
        {
            const Ref<Mesh> bodyMesh = meshLibrary->get_item_mesh(0);
            body->set_mesh(bodyMesh);
        }

    }
    void Player::CreateStepRays() {
        stepDownRay = memnew(RayCast3D);
        stepDownRay->set_name("_stepDownRay");
        stepDownRay->set_position(Vector3(0.0f, 0.0f, 0.0f));
        stepDownRay->set_target_position(Vector3(0, -1, 0));
        add_child(stepDownRay);

        stepAheadRay = memnew(RayCast3D);
        stepAheadRay->set_name("_stepAheadRay");
        stepAheadRay->set_position(Vector3(0.0f, 0.55f, -0.55f));
        stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
        stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
        add_child(stepAheadRay);
    }

    void Player::SnapDownToStairsCheck()
    {
	    bool did_snap = false;


	    stepDownRay->force_raycast_update();
	    const bool floor_below = stepDownRay->is_colliding() && !IsSurfaceTooSteep(stepDownRay->get_collision_normal());
	    bool was_on_floor_last_frame = Engine::get_singleton()->get_physics_frames() == _last_frame_was_on_floor;
	    if(!is_on_floor() && this->get_velocity().y <= 0 && (was_on_floor_last_frame || _snapped_to_stairs_last_frame) && floor_below)
	    {
		    KinematicCollision3D* body_test_result = memnew(KinematicCollision3D);
		    if(test_move(get_global_transform(), Vector3(0, -MAX_STEP_HEIGHT, 0), body_test_result))
		    {
			    SaveCamPosForSmoothing();
			    float translate_y = body_test_result->get_travel().y;
			    Vector3 pos = get_position();
			    pos.y += translate_y;
			    set_position(pos);
			    apply_floor_snap();
		        did_snap = true;

		    }
	    }
	    _snapped_to_stairs_last_frame = did_snap;

}
bool Player::StepUpStairsCheck(const double delta) {
	if (!is_on_floor() && !_snapped_to_stairs_last_frame)
	{
	    return false;
	}
    if(get_velocity().y > 0 || (get_velocity() * Vector3(1,0,1)).length() == 0.f)
    {
        return false;
    }

	const Vector3 expected_move_motion = this->get_velocity() * Vector3(1,0,1) * static_cast<float>(delta);

	//Makes sure you can't step up if something is blocking you
	const Transform3D step_pos_with_clearance = get_global_transform().translated(expected_move_motion + Vector3(0, MAX_STEP_HEIGHT *2, 0));
    KinematicCollision3D* down_check_result = memnew(KinematicCollision3D);
	if (test_move(step_pos_with_clearance, Vector3(0, -MAX_STEP_HEIGHT*2.0f, 0), down_check_result) && (down_check_result->get_collider()->is_class("StaticBody3D") || down_check_result->get_collider()->is_class("CSGShape3D")))
	{
		//how much higher is the step_height
	    float step_height = ((step_pos_with_clearance.origin + down_check_result->get_travel()) - get_global_position()).y;
		if(step_height > MAX_STEP_HEIGHT || step_height <= 0.01f || (down_check_result->get_position() - get_global_position()).y > MAX_STEP_HEIGHT) return false;
		stepAheadRay->set_global_position(down_check_result->get_position() + Vector3(0, MAX_STEP_HEIGHT, 0) + expected_move_motion.normalized() * 0.025f);
		stepAheadRay->force_raycast_update();
		//UtilityFunctions::print(step_height);
		if(stepAheadRay->is_colliding() && !IsSurfaceTooSteep(stepAheadRay->get_collision_normal()))
		{

			SaveCamPosForSmoothing();
			set_global_position(step_pos_with_clearance.origin + down_check_result->get_travel());
			apply_floor_snap();
			_snapped_to_stairs_last_frame = true;
			return true;
		}
	}
	return false;
}

    void Player::SaveCamPosForSmoothing()
    {
        if(savedCameraPosition == Vector3(0,0,0))
        {
            savedCameraPosition = camera->get_global_position();
        }
    }


    void Player::SmoothCamera(double delta) {
        if(savedCameraPosition == Vector3(0,0,0)) return;
        Vector3 gp = CameraSmooth->get_global_position();
        gp.y = savedCameraPosition.y;
        CameraSmooth->set_global_position(gp);
        Vector3 camSmoothPos = CameraSmooth->get_position();
        camSmoothPos.y = Math::clamp(camSmoothPos.y, -CROUCH_TRANSLATE, CROUCH_TRANSLATE);
        float moveAmount = Math::max(this->get_velocity().length() * static_cast<float>(delta), walk_speed/2 * static_cast<float>(delta));
        camSmoothPos.y = Math::move_toward(camSmoothPos.y, 0.0f, moveAmount);
        CameraSmooth->set_position(camSmoothPos);
        savedCameraPosition = camera->get_global_position();
        if(camSmoothPos.y == 0)
        {
            savedCameraPosition = Vector3(0,0,0);
        }
    }

    void Player::_push_away_rigid_bodies()
    {
        for(int i = 0; i < get_slide_collision_count(); i++)
        {
            Ref<KinematicCollision3D> c = get_slide_collision(i);
            if(c->get_collider()->is_class("RigidBody3D"))
            {
                auto *rb = Object::cast_to<RigidBody3D>(c->get_collider());
                Vector3 push_dir = -c->get_normal();
                real_t velocity_diff_in_push_dir = this->get_velocity().dot(push_dir) - rb->get_linear_velocity().dot(push_dir);
                velocity_diff_in_push_dir = Math::max(0.0f, velocity_diff_in_push_dir);

                const float my_mass = 1.25f;
                float mass_ratio = Math::min(1.0f, my_mass / (float)rb->get_mass());
                push_dir.y = 0;
                float push_force = mass_ratio * 5.0f;
                rb->apply_impulse(push_dir * velocity_diff_in_push_dir * push_force, rb->get_position() - rb->get_global_position());
            }
        }
    }

    bool Player::_handle_water_physics(double delta)
    {
        return false;
        float fDelta = static_cast<float>(delta);


        if(!is_on_floor())
        {

            Vector3 v = this->get_velocity();
            v.y -= 9.8f * 0.1f * static_cast<float>(fDelta);
            this->set_velocity(v);
        }

            if(Input::get_singleton()->is_action_pressed("Jump"))
                _add_velocity_y(swim_up_speed * fDelta);

            this->set_velocity(this->get_velocity().lerp(Vector3(0,0,0), 2 * fDelta));
            return false;


    }


    void Player::_handle_crouch(double delta)
    {
        if(Engine::get_singleton()->is_editor_hint()) return;
        bool was_crouched_last_frame = is_crouched;



        Vector3 colPos = col->get_position();
        Ref<CapsuleShape3D> colShape = col->get_shape();

        if(Input::get_singleton()->is_action_pressed("Crouch"))
        {
            is_crouched = true;
        }
        else if (is_crouched && !test_move(get_transform(), Vector3(0, CROUCH_TRANSLATE,0)))
        {
            is_crouched = false;
        }

        float translate_y_if_possible = 0;

        if(was_crouched_last_frame != is_crouched && !is_on_floor() && !_snapped_to_stairs_last_frame)
        {
            translate_y_if_possible = (is_crouched) ? CROUCH_JUMP_ADD : -CROUCH_JUMP_ADD;
        }

        Vector3 cPos = camera->get_position();
        if(translate_y_if_possible != 0)
        {
            Ref<KinematicCollision3D> result = memnew(KinematicCollision3D);
            test_move(get_transform(), Vector3(0, translate_y_if_possible, 0), result);
            Vector3 pos = get_position();
            pos.y += result->get_travel().y;
            set_position(pos);
            cPos.y -= result->get_travel().y;
            cPos.y = Math::clamp(cPos.y, -CROUCH_TRANSLATE, 1.0f);
            camera->set_position(cPos);
        }


        camera->set_position(Vector3(0, Math::move_toward(camera->get_position().y, (is_crouched) ? CROUCH_TRANSLATE : 1 , 3.0f * (float)delta),0));
        colShape->set_height((is_crouched) ? 1.5 - CROUCH_TRANSLATE : 1.5f);

        col->set_shape(colShape);
        colPos.y = (float)colShape->get_height() / 2.0f;
        col->set_position(colPos);
        //UtilityFunctions::print(actor_vars._snapped_to_stairs_last_frame);

    }

    bool Player::_handle_noclip(double delta)
    {
        if(Input::get_singleton()->is_action_just_pressed("Noclip") && OS::get_singleton()->has_feature("debug"))
        {
            noclip = !noclip;
            noclip_speed_mult = 3.f;
        }

        col->set_disabled(noclip);
        if(!noclip)
            return false;

        float speed = get_move_speed() * noclip_speed_mult;

        if(Input::get_singleton()->is_action_pressed("Sprint"))
        {
            speed *= 3.f;
        }
        this->set_velocity(cam_aligned_wish_dir * speed);
        Vector3 gp = get_global_position();
        gp += this->get_velocity() * delta;
        set_global_position(gp);
        return true;
    }

    void Player::clip_velocity(Vector3 normal, float overbounce, float _delta)
    {
        float backoff = this->get_velocity().dot(normal) * overbounce;

        if(backoff >= 0)
            return;

        Vector3 change = normal * backoff;
        Vector3 v = this->get_velocity();
        v -= change;
        this->set_velocity(v);

        // Second iteration to ensure no movement through the plane
        float adjust = this->get_velocity().dot(normal);
        if(adjust < 0.0f)
        {
            v -= normal * adjust;
            this->set_velocity(v);
        }
    }

    void Player::_mouse_look(const Ref<InputEventMouseMotion>& p_event)
    {
        if (camera == nullptr) {
            UtilityFunctions::print("Camera is null during mouse look!");
            return;
        }

        if (Engine::get_singleton()->is_editor_hint()) return;

        Vector2 mouseMotion = p_event->get_relative();
        camera->rotate_y(Math::deg_to_rad(-mouseMotion.x * look_sensitivity));
        mouseRotation.x += Math::deg_to_rad(-mouseMotion.y * look_sensitivity);
        mouseRotation.x = Math::clamp(mouseRotation.x, Math::deg_to_rad(-89.0f), Math::deg_to_rad(89.0f));

        mouseRotation.z += Math::deg_to_rad(-mouseMotion.y * look_sensitivity * inputDir.length());
        mouseRotation.z = Math::clamp(mouseRotation.z, Math::deg_to_rad(-85.0f), Math::deg_to_rad(85.0f));

        mouseRotation.z = Math::lerp(mouseRotation.z, 0.0f, static_cast<float>(get_physics_process_delta_time()) * 7.0f);

        Transform3D t = camera->get_transform();
        t.basis = get_basis();
        camera->set_transform(t);

        camera->rotate_object_local(Vector3(1, 0, 0), mouseRotation.x);
    }

    float Player::get_move_speed()
    {
        if(is_crouched)
        {
            return walk_speed * 0.8;
        }
        if(Input::get_singleton()->is_action_pressed("Sprint"))
        {
            return sprint_speed;
        }
        return walk_speed;
    }



    void Player::_add_velocity_x(float value)
{
    Vector3 v = this->get_velocity();
    v.x += value;
    this->set_velocity(v);
}

    void Player::_add_velocity_y(float value)
{
    Vector3 v = this->get_velocity();
    v.y += value;
    this->set_velocity(v);
}

    void Player::_add_velocity_z(float value)
{
    Vector3 v = this->get_velocity();
    v.z += value;
    this->set_velocity(v);
}
    void Player::_subtract_velocity_x(float value)
{
    Vector3 v = this->get_velocity();
    v.x -= value;
    this->set_velocity(v);
}

    void Player::_subtract_velocity_y(float value)
{
    Vector3 v = this->get_velocity();
    v.y -= value;
    this->set_velocity(v);
}

    void Player::_subtract_velocity_z(float value)
{
    Vector3 v = this->get_velocity();
    v.z -= value;
    this->set_velocity(v);
}

} // FearTheCrow