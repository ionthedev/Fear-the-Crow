using Godot;
using System;
using Mathf = Godot.Mathf;

public partial class Player : CharacterBody3D
{
	[ExportCategory("Dimension Settings")]
	[Export] private Vector2 _playerHeight = new Vector2(5, 10);
	[Export] private float _eyeHeight;
	[Export] private float _capsuleHeight = 2.0f;
	[Export] private float _capsuleRadius = 0.5f;

	[ExportCategory("Ground Movement Settings")] 
	[Export] private float _walkSpeed = 7.0f;
	[Export] private float _sprintSpeed = 8.5f;
	[Export] private float _groundAccel = 7.0f;
	[Export] private float _groundDecel = 5.0f;
	[Export] private float _groundFriction = 6.0f;
	
	[ExportCategory("Air Movement Settings")]
	[Export] private float _airCap = 2.85f; // Can surf steeper ramps if this is higher, makes it easier to stick and bhop
	[Export] private float _airAccel = 1.0f;
	[Export] private float _airMoveSpeed = 17.0f;
	[Export] private float _gravity = 15.24f;
	
	[ExportCategory("Crouch Settings")]
	[Export] private float _crouchTranslate = 0.7f;
	[Export] private float _crouchJumpAdd;
	[Export] private bool _isCrouched = false;
	
	[ExportCategory("Jump settings")]
	[Export]
	private float _lookSensitivity= 0.006f;
	[Export] private float _controllerLookSensitivity = 0.05f;
	[Export] private float _jumpVelocity = .27f;
	[Export] private bool _autoBhop = true;
	[Export] private float _speedJumpMult = 3.25f;
	
	[ExportCategory("Headbob Settings")]
	[Export] private float _headbobMoveAmount = 0.06f;
	[Export] private float _headbobFrequency = 2.4f;
	[Export] private float _headbobTime = 0.0f;
	
	[ExportCategory("Noclip Settings")]
	[Export] private float _noclipSpeedMult = 3.0f;
	[Export] private bool _noclip = false;

	[ExportCategory("Stair Settings")]
	[Export] private float _maxStepHeight = 0.5f;
	[Export] private bool _snappedToStairsLastFrame = false;
	private UInt64 _lastFrameWasOnFloor;
	
	//TODO: Ladder Settings
	
	//TODO: Swim Settings
	
	[ExportCategory("Nodes")]
	[Export] private Camera3D _camera;
	[Export] private RayCast3D _stepDownRay;
	[Export] private RayCast3D _stepAheadRay;
	[Export] private CollisionShape3D _col;

	[Export] private Node3D _headOriginalPosition;
	[Export] private Node3D _head;
	[Export] private Node3D _cameraSmooth;

	private Vector2 _inputDir;
	private Vector3 _wishDir;
	private Vector3 _mouseRotation;
	private Vector3 _savedCameraPosition;
	private Vector2 _curControllerLook;
	private Vector3 _camAlignedWishDir = Vector3.Zero;

	public Player(RayCast3D stepAheadRay, Vector2 inputDir)
	{
		_stepAheadRay = stepAheadRay;
		this._inputDir = inputDir;
	}

	public Player()
	{
	}

	public override void _Ready()
	{
		SetMouseMode(DisplayServer.MouseMode.Captured);
	}

	public override void _Process(double delta)
	{
		_handle_controller_look_input(delta);
		if (Engine.IsEditorHint())
		{
			UpdatePlayerSizeAttributes();
		}
	}

	public override void _PhysicsProcess(double delta)
	{
		if (Engine.IsEditorHint()) return;

		if (IsOnFloor())
			_lastFrameWasOnFloor = Engine.GetPhysicsFrames();
		_inputDir = Input.GetVector("Left", "Right", "Forward", "Backward").Normalized();
		_wishDir = Transform.Basis * new Vector3(_inputDir.X, 0, _inputDir.Y);
		_camAlignedWishDir = _camera.GlobalTransform.Basis * new Vector3(_inputDir.X, 0, _inputDir.Y);
		
		_handle_crouch(delta);

		if (!_handle_noclip(delta))
		{
			//TODO: Add !_handle_water_physics check
			if (IsOnFloor() || _snappedToStairsLastFrame)
			{
				if (Input.IsActionJustPressed("Jump") || (_autoBhop && Input.IsActionPressed("Jump")))
				{
					Vector3 v = GetVelocity();
					v.Y += _jumpVelocity * (new Vector2(GetVelocity().X, GetVelocity().Z).Length() >= _sprintSpeed ? new Vector2(GetVelocity().X, GetVelocity().Z).Length()  * _speedJumpMult : 23.444444444f);
					SetVelocity(v);
				}
				_handle_ground_physics(delta);
			}
			else
			{
				_handle_air_physics(delta);
			}
		}

		if (!StepUpStairsCheck(delta))
		{
			_push_away_rigid_bodies(delta);
			MoveAndSlide();
			SnapDownToStairsCheck();
		}
		
		SmoothCamera(delta);
	}

	void SwitchWeapon(int index)
	{
		
	}

	float get_move_speed()
	{
		if(_isCrouched)
			return _walkSpeed * 0.8f;
		if (Input.IsActionJustPressed("Sprint"))
			return _sprintSpeed;
		return _walkSpeed;
	}
	
	public override void _UnhandledInput(InputEvent @event)
	{
		if (Input.IsActionPressed("Pause")) GetTree().Quit();

		if (@event is InputEventMouseMotion eventMouseMotion)
		{
			RotateY(-eventMouseMotion.GetRelative().X * _lookSensitivity);
			_camera.RotateX(-eventMouseMotion.GetRelative().Y * _lookSensitivity);
			float camX = IsOnFloor() ? Mathf.Clamp(_camera.GetRotation().X, Mathf.DegToRad(-90.0f), Mathf.DegToRad(90.0f)) : _camera.GetRotation().X;
			_camera.SetRotation(new Vector3(camX, _camera.GetRotation().Y, _camera.GetRotation().Z));
		}

		if (@event is InputEventMouseButton mouseEvent && mouseEvent.Pressed)
		{
			if(mouseEvent.GetButtonIndex() == MouseButton.WheelUp) _noclipSpeedMult = Mathf.Min(100.0f, _noclipSpeedMult * 1.1f);
			if(mouseEvent.GetButtonIndex() == MouseButton.WheelDown) _noclipSpeedMult = Mathf.Max(0.1f, _noclipSpeedMult * 0.9f);
		}

		if (Input.IsActionJustReleased("Weapon_1"))
			SwitchWeapon(1);
		if (Input.IsActionJustPressed("Weapon_2"))
			SwitchWeapon(2);
		if (Input.IsActionJustReleased("Weapon_3"))
			SwitchWeapon(3);
		if (Input.IsActionJustPressed("Weapon_4"))
			SwitchWeapon(4);
		if (Input.IsActionJustPressed("Weapon_5"))
			SwitchWeapon(5);
	}

	void _handle_ground_physics(double delta)
	{
		float fDelta = (float)delta;
		float curSpeedInWishDir = GetVelocity().Dot(_wishDir);
		float addSpeedTilCap = get_move_speed() - curSpeedInWishDir;
		Vector3 v;
		if (addSpeedTilCap > 0)
		{
			float accelSpeed = _groundAccel * fDelta * get_move_speed();
			accelSpeed = Mathf.Min(accelSpeed, addSpeedTilCap);
			v = GetVelocity();
			v += accelSpeed * _wishDir;
			SetVelocity(v);
		}
		
		//ApplyFriction
		float control = Mathf.Max(GetVelocity().Length(), _groundDecel);
		float drop = control * _groundDecel * fDelta;
		float newSpeed = Mathf.Max(GetVelocity().Length() - drop, 0.0f);
		if (GetVelocity().Length() > 0)
		{
			newSpeed /= GetVelocity().Length();
		}
		v = GetVelocity();
		v *= newSpeed;
		SetVelocity(v);

		_headbob_effect(fDelta);

	}

	void _headbob_effect(float delta)
	{
		_headbobTime += delta * GetVelocity().Length();
		Transform3D _t = _camera.GetTransform();
		Vector3 o;

		float t = _headbobTime;
		float f = _headbobFrequency;
		float a = _headbobMoveAmount;

		float x = Mathf.Cos(t * f * 0.5f) * a;
		float y = Mathf.Sin(t * f) * a;
		o = new Vector3(x, y ,0);
		_t.Origin = o;
		_camera.SetTransform(_t);

	}
	
	
	void _handle_air_physics(double delta)
	{
		float fDelta = (float)delta;
		Vector3 v = GetVelocity();
		v.Y -= _gravity * fDelta;
		SetVelocity(v);
		float cur_speed_in_wish_dir = GetVelocity().Dot(_wishDir);
		float add_speed_till_cap = get_move_speed() - cur_speed_in_wish_dir;
		if(add_speed_till_cap > 0)
		{
			float accel_speed = _airAccel * _airMoveSpeed * fDelta;
			accel_speed = Mathf.Min(accel_speed, add_speed_till_cap);
			v += accel_speed * _wishDir;
			SetVelocity(v);
		}

		if (IsOnWall()) {
			if (IsSurfaceTooSteep(GetWallNormal())) {
				SetMotionMode(MotionModeEnum.Floating);  // Enables smoother surf movement
			} else {
				SetMotionMode(MotionModeEnum.Grounded);
			}
			clip_velocity(GetWallNormal(), 1.0f, fDelta);  // Clip velocity for surf
		}

	}

	void _handle_controller_look_input(double delta)
	{
		
	}
	
	bool IsSurfaceTooSteep(Vector3 _normal)
	{
		return _normal.AngleTo(Vector3.Up) > GetFloorAngle();
	}

	bool StepUpStairsCheck(double delta)
	{
		float fDelta = (float)delta;
		
		if (!IsOnFloor() && !_snappedToStairsLastFrame)
		{
			return false;
		}
		if(GetVelocity().Y > 0 || (GetVelocity() * new Vector3(1,0,1)).Length() == 0.0f)
		{
			return false;
		}

		Vector3 expected_move_motion = GetVelocity() * new Vector3(1.0f, 0.0f, 1.0f) * fDelta;

		//Makes sure you can't step up if something is blocking you
		Transform3D step_pos_with_clearance = GlobalTransform.Translated(expected_move_motion + new Vector3(0.0f, _maxStepHeight *2.0f, 0.0f));
		KinematicCollision3D down_check_result = new KinematicCollision3D();
		if (TestMove(step_pos_with_clearance, new Vector3(0, -_maxStepHeight*2.0f, 0), down_check_result) && (down_check_result.GetCollider().IsClass("StaticBody3D") || down_check_result.GetCollider().IsClass("CSGShape3D")))
		{
			//how much higher is the step_height
			float step_height = ((step_pos_with_clearance.Origin + down_check_result.GetTravel()) - GetGlobalPosition()).Y;
			if(step_height > _maxStepHeight || step_height <= 0.01f || (down_check_result.GetPosition() - GetGlobalPosition()).Y > _maxStepHeight) return false;
			_stepAheadRay.SetGlobalPosition(down_check_result.GetPosition() + new Vector3(0, _maxStepHeight, 0) + expected_move_motion.Normalized() * 0.025f);
			_stepAheadRay.ForceRaycastUpdate();
			//UtilityFunctions::print(step_height);
			if(_stepAheadRay.IsColliding() && !IsSurfaceTooSteep(_stepAheadRay.GetCollisionNormal()))
			{

				SaveCamPosForSmoothing();
				SetGlobalPosition(step_pos_with_clearance.Origin + down_check_result.GetTravel());
				ApplyFloorSnap();
				_snappedToStairsLastFrame = true;
				return true;
			}
		}
		return false;
	}

	void SnapDownToStairsCheck()
	{
		bool did_snap = false;
		
		_stepDownRay.ForceRaycastUpdate();
		bool floor_below = _stepDownRay.IsColliding() && !IsSurfaceTooSteep((_stepDownRay.GetCollisionNormal()));
		bool was_on_floor_last_frame = Engine.GetPhysicsFrames() == _lastFrameWasOnFloor;
		if (!IsOnFloor() && GetVelocity().Y < 0 && (was_on_floor_last_frame || _snappedToStairsLastFrame) && floor_below)
		{
			KinematicCollision3D body_test_result = new KinematicCollision3D();
			if (TestMove(GlobalTransform, new Vector3(0, -_maxStepHeight, 0), body_test_result))
			{
				SaveCamPosForSmoothing();
				float translate_y = body_test_result.GetTravel().Y;
				Vector3 pos = GetPosition();
				pos.Y += translate_y;
				SetPosition(pos);
				ApplyFloorSnap();
				did_snap = true;
			}
		}
		_snappedToStairsLastFrame = did_snap;
	}

	void SaveCamPosForSmoothing()
	{
		if(_savedCameraPosition == Vector3.Zero)
		{
			_savedCameraPosition = _camera.GlobalPosition;
		}
	}

	void SmoothCamera(double delta)
	{
		float fDelta = (float)delta;
		
		if (_savedCameraPosition == Vector3.Zero) return;
		Vector3 CS_GP = _cameraSmooth.GetGlobalPosition();
		Vector3 CS_LP = _cameraSmooth.GetPosition();
		CS_GP.Y = _savedCameraPosition.Y;
		CS_LP.Y = Mathf.Clamp(CS_LP.Y, -_crouchTranslate, _crouchTranslate);
		float move_amount = Mathf.Max(GetVelocity().Length() * fDelta, _walkSpeed/2 * fDelta);
		CS_LP.Y = Mathf.MoveToward(CS_LP.Y, 0.0f, move_amount);
		_savedCameraPosition = CS_GP;
		if(CS_LP.Y == 0)
		{
			_savedCameraPosition = Vector3.Zero;
		}
		_cameraSmooth.SetGlobalPosition(CS_GP);
		_cameraSmooth.SetPosition(CS_LP);
	}

	void _push_away_rigid_bodies(double delta)
	{
		for(int i = 0; i < GetSlideCollisionCount(); i++)
		{
			KinematicCollision3D c = GetSlideCollision(i);
			if(c.GetCollider().IsClass("RigidBody3D"))
			{
				RigidBody3D rb = (RigidBody3D)c.GetCollider();
				Vector3 push_dir = -c.GetNormal();
				float velocity_diff_in_push_dir = GetVelocity().Dot(push_dir) - rb.GetLinearVelocity().Dot(push_dir);
				velocity_diff_in_push_dir = Mathf.Max(0.0f, velocity_diff_in_push_dir);

				const float my_mass = 1.25f;
				float mass_ratio = Mathf.Min(1.0f, my_mass / rb.GetMass());
				push_dir.Y = 0;
				float push_force = mass_ratio * 5.0f;
				rb.ApplyImpulse(push_dir * velocity_diff_in_push_dir * push_force, rb.GetPosition() - rb.GetGlobalPosition());
			}
		}
	}

	void _handle_crouch(double delta)
	{
		if(Engine.IsEditorHint()) return;
		bool was_crouched_last_frame = _isCrouched;

		Vector3 colPos = _col.GetPosition();
		CapsuleShape3D colShape = (CapsuleShape3D)_col.GetShape();

		if(Input.IsActionPressed("Crouch"))
		{
			_isCrouched = true;
		}
		else if (_isCrouched && !TestMove(GetTransform(), new Vector3(0, _crouchTranslate,0)))
		{
			_isCrouched = false;
		}

		float translate_y_if_possible = 0;

		if(was_crouched_last_frame != _isCrouched && !IsOnFloor() && !_snappedToStairsLastFrame)
		{
			translate_y_if_possible = (_isCrouched) ? _crouchJumpAdd : -_crouchJumpAdd;
		}

		Vector3 hPos = _head.GetPosition();
		if(translate_y_if_possible != 0)
		{
			KinematicCollision3D result = new KinematicCollision3D();
			TestMove(GetGlobalTransform(), new Vector3(0, translate_y_if_possible, 0), result);
			Vector3 pos = GetPosition();
			pos.Y += result.GetTravel().Y;
			SetPosition(pos);
			hPos.Y -= result.GetTravel().Y;
			hPos.Y = Mathf.Clamp(hPos.Y, -_crouchTranslate, 0.0f);
			_head.SetPosition(hPos);
		}


		hPos.Y = Mathf.MoveToward(hPos.Y, (_isCrouched) ? -_crouchTranslate : 0.0f , 7.0f * (float)delta);
		colShape.SetHeight(_isCrouched ? ConvertImperialToMetric(_playerHeight) - _crouchTranslate : ConvertImperialToMetric(_playerHeight));

		_col.SetShape(colShape);
		colPos.Y = (float)colShape.GetHeight() / 2.0f;
		_col.SetPosition(colPos);
		_head.SetPosition(hPos);
		//UtilityFunctions::print(actor_vars._snapped_to_stairs_last_frame);

	}

	bool _handle_noclip(double delta)
	{if(Input.IsActionJustPressed("Noclip") && OS.HasFeature("debug"))
		{
			_noclip = !_noclip;
			_noclipSpeedMult = 3.0f;
		}

		_col.SetDisabled(_noclip);
		if(!_noclip)
			return false;

		float speed = get_move_speed() * _noclipSpeedMult;

		if(Input.IsActionPressed("Sprint"))
		{
			speed *= 3.0f;
		}
		SetVelocity(_camAlignedWishDir * speed);
		Vector3 gp = GetGlobalPosition();
		gp += GetVelocity() * (float)delta;
		SetGlobalPosition(gp);
		return true;
	}

	void clip_velocity(Vector3 normal, float overbounce, float _delta)
	{
		float backoff = GetVelocity().Dot(normal) * overbounce;

		if(backoff >= 0)
			return;

		Vector3 change = normal * backoff;
		Vector3 v = GetVelocity();
		v -= change;
		SetVelocity(v);

		// Second iteration to ensure no movement through the plane
		float adjust = GetVelocity().Dot(normal);
		if(adjust < 0.0f)
		{
			v -= normal * adjust;
			SetVelocity(v);
		}
	}

	void SetMouseMode(DisplayServer.MouseMode mode)
	{
		if (Engine.IsEditorHint()) return;
		DisplayServer.MouseSetMode(mode);
	}

	void _mouse_look(InputEventMouseMotion p_event)
	{
		if (_camera == null) {
			GD.Print("Camera is null during mouse look!");
			return;
		}

		if (Engine.IsEditorHint())
			return;

		Vector2 mouseMotion = p_event.GetRelative();
		_camera.RotateY(Mathf.DegToRad(-mouseMotion.X * _lookSensitivity));
		_mouseRotation.X += Mathf.DegToRad(-mouseMotion.Y * _lookSensitivity);

		_mouseRotation.X = Mathf.Clamp(_mouseRotation.X, Mathf.DegToRad(-89.0f), Mathf.DegToRad(89.0f));

		_mouseRotation.Z += Mathf.DegToRad(-mouseMotion.Y * _lookSensitivity * _inputDir.Length());
		_mouseRotation.Z = Mathf.Clamp(_mouseRotation.Z, Mathf.DegToRad(-85.0f), Mathf.DegToRad(85.0f));

		_mouseRotation.Z = Mathf.Lerp(_mouseRotation.Z, 0.0f, (float)GetPhysicsProcessDeltaTime() * 7.0f);

		Transform3D t = _camera.GetTransform();
		t.Basis = GetBasis();
		_camera.SetTransform(t);

		_camera.RotateObjectLocal(new Vector3(1, 0, 0), _mouseRotation.X);
	}

	float ConvertImperialToMetric(Vector2 height)
	{
		float feet = height.X;
		float inches = height.Y;
		const float feet_to_meters = 0.3048f;
		const float inches_to_meters = 0.0254f;

		float meters_from_feet = feet * feet_to_meters;
		float metersFromInches;
		metersFromInches = inches * inches_to_meters;
		float totalMeters = meters_from_feet + metersFromInches;
		return totalMeters;
	}

	void UpdatePlayerSizeAttributes()
	{
		Vector3 headPos = _headOriginalPosition.GetPosition();
		headPos.Y = ConvertImperialToMetric(_playerHeight) - (6 * 0.0254f);
		_headOriginalPosition.SetPosition(headPos);
		_savedCameraPosition = GetGlobalPosition();
		CapsuleShape3D shape = (CapsuleShape3D)_col.GetShape();
		shape.SetHeight(ConvertImperialToMetric(_playerHeight));
		shape.SetRadius(_capsuleRadius);
		_crouchJumpAdd = _crouchTranslate * 0.9f;
	}
}
