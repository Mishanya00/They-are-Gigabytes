#pragma once

#include "math_3d.h"

namespace rgl
{
	class Camera
	{
	public:

        Camera(int WindowWidth, int WindowHeight);

        Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, 
						const Vector3f& Target, const Vector3f& Up, const Vector3f & Left);

        void SetPosition(float x, float y, float z);
		void SetPosition(Vector3f new_position);
		void SetWindowSize(int width, int height);
		void SetSpeed(float new_speed);
		void SetRotationSpeed(float new_rotation_speed);

		void Rotate(float rotX, float rotY, float rotZ);
		void RotateAroundTargetPoint(float alfa);
		void MoveAcrossVector(Vector3f const & target_vector, bool isNotVertMove = true, float distance = 0);

		void OnKeyboard(unsigned char key);
        void OnMouse(int button, int state, int x, int y);
        void OnRender();
		void OnFrame();

        Matrix4f GetMatrix();

    private:

        void Init();
        void Update();

		Vector3f position_;
		Vector3f target_;
		Vector3f up_;
		Vector3f left_;

		float speed_;
		float rotation_speed_;

        int window_height_;
        int window_width_;

        float angle_horz_;
        float angle_vert_;

        bool is_upper_edge_;
        bool is_lower_edge_;
        bool is_left_edge_;
        bool is_right_edge_;

		int margin_;

        Vector2i mouse_pos_;
	};
}