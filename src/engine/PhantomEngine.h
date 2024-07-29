//
// Created by Brandon Friend on 7/25/24.
//

#ifndef PHANTOMENGINE_H
#define PHANTOMENGINE_H

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include "rlImGui.h"
#include "imgui.h"
#include "main/PE_Core.h"
#include "main/Game.h"
#include "classes/Artifact.h"
#include "classes/Husk.h"
#include "../../thirdparty/linalg/linalg.h"

class PhantomEngine
{
    public:
    static float m_Clip(float n, float lower, float upper)
    {
        return std::max(lower, std::min(n, upper));
    }

    static Vector3 MatrixMultiplyVector3(Matrix matrix, Vector3 vector) {
        Vector3 result;
        result.x = matrix.m0 * vector.x + matrix.m4 * vector.y + matrix.m8 * vector.z + matrix.m12 * 1.0f;
        result.y = matrix.m1 * vector.x + matrix.m5 * vector.y + matrix.m9 * vector.z + matrix.m13 * 1.0f;
        result.z = matrix.m2 * vector.x + matrix.m6 * vector.y + matrix.m10 * vector.z + matrix.m14 * 1.0f;

        float w = matrix.m3 * vector.x + matrix.m7 * vector.y + matrix.m11 * vector.z + matrix.m15 * 1.0f;
        if (w != 1.0f && w != 0.0f) {
            result.x /= w;
            result.y /= w;
            result.z /= w;
        }

        return result;
    }

    static Matrix MatrixFromYawPitchRoll(double yaw, double pitch, double roll) {

        double ch = std::cos(yaw);
        double sh = std::sin(yaw);
        double cp = std::cos(pitch);
        double sp = std::sin(pitch);
        double cb = std::cos(roll);
        double sb = std::sin(roll);

        Matrix m = {0};

        m.m0 = ch * cb + sh * sp * sb;
        m.m4 = -ch * sb + sh * sp * cb;
        m.m8 = sh * cp;
        m.m12 = 0.0;

        m.m1 = sb * cp;
        m.m5 = cb * cp;
        m.m9 = -sp;
        m.m13 = 0.0;

        m.m2 = -sh * cb + ch * sp * sb;
        m.m6 = sb * sh + ch * sp * cb;
        m.m10 = ch * cp;
        m.m14 = 0.0;

        m.m3 = 0.0;
        m.m7 = 0.0;
        m.m11 = 0.0;
        m.m15 = 1.0;  // Homogeneous coordinate

        return m;
    }

    static Vector3 QuaternionMultiplyVector3(Quaternion q, Vector3 v) {

        Vector3 u = { q.x, q.y, q.z };

        float s = q.w;

        Vector3 u_cross_v = {
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
        };

        Vector3 u_cross_u_cross_v = {
            u.y * u_cross_v.z - u.z * u_cross_v.y,
            u.z * u_cross_v.x - u.x * u_cross_v.z,
            u.x * u_cross_v.y - u.y * u_cross_v.x
        };

        Vector3 result = {
            v.x + 2.0f * (s * u_cross_v.x + u_cross_u_cross_v.x),
            v.y + 2.0f * (s * u_cross_v.y + u_cross_u_cross_v.y),
            v.z + 2.0f * (s * u_cross_v.z + u_cross_u_cross_v.z)
        };

        return result;
    }

    static Quaternion QuaternionAngleAxis(float angle_radians, const Vector3& axis) {
        Quaternion q;
        float t = angle_radians * 0.5f;
        Vector3 v = Vector3Normalize(axis);
        v.x *= std::sin(t);
        v.y *= std::sin(t);
        v.z *= std::sin(t);
        q.x = v.x;
        q.y = v.y;
        q.z = v.z;
        q.w = std::cos(t);
        return q;
    }

};

#endif //PHANTOMENGINE_H
