#pragma once

#include "math_3d.h"

namespace rgl
{
	class Camera
	{
	public:

		Camera();

		void SetPosition(float x, float y, float z);
		void SetPosition(Vector3f new_position);

		void OnKeyboard(unsigned char key);

		Matrix4f GetMatrix();


	private:

		Vector3f position_;
		Vector3f target_;
		Vector3f up_;
		float speed_;
	};

	class QuaternionCamera
	{
	public:

        QuaternionCamera(int WindowWidth, int WindowHeight);

        QuaternionCamera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

        void SetPosition(float x, float y, float z);
		void SetPosition(Vector3f new_position);
		void SetWindowSize(int width, int height);

        void OnKeyboard(unsigned char key);

        void OnMouse(int x, int y);

        void OnRender();

        Matrix4f GetMatrix();

    private:

        void Init();
        void Update();

		Vector3f position_;
		Vector3f target_;
		Vector3f up_;

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