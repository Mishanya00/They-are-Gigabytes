#include <glut.h>

#include "camera.hpp"


namespace rgl
{
	Camera::Camera()
	{
		position_ = Vector3f(0.0f, 0.0f, 0.0f);
		target_ = Vector3f(0.0f, 0.0f, 1.0f);
		up_ = Vector3f(0.0f, 1.0f, 0.0f);
		speed_ = 1.0f;
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		position_.x = x;
		position_.y = y;
		position_.z = z;
	}
	void Camera::SetPosition(Vector3f new_position)
	{
		position_.x = new_position.x;
		position_.y = new_position.y;
		position_.z = new_position.z;
	}

	void Camera::OnKeyboard(unsigned char key)
	{
		switch (key)
		{
		case 'w':
		case 'W':
			position_ += (target_ * speed_);
			break;

		case 's':
		case 'S':
			position_ -= (target_ * speed_);
			break;

		case 'a':
		case 'A':
		{
			Vector3f Left = target_.Cross(up_); 
			Left.Normalize();
			Left *= speed_;
			position_ += Left;
		}
		break;

		case 'd':
		case 'D':
		{
			Vector3f Right = up_.Cross(target_);
			Right.Normalize();
			Right *= speed_;
			position_ += Right;
		}
		break;

		case GLUT_KEY_PAGE_UP:
			position_.y += speed_;
			break;
		case GLUT_KEY_PAGE_DOWN:
			position_.y -= speed_;
			break;
		}
	}

	Matrix4f Camera::GetMatrix()
	{
		Matrix4f CameraTransformation;
		CameraTransformation.InitCameraTransform(position_, target_, up_);

		return CameraTransformation;
	}

    //------------------------------------------------//
    //              Quaternion camera                 //
    //------------------------------------------------//

    QuaternionCamera::QuaternionCamera(int WindowWidth, int WindowHeight)
    {
        window_width_ = WindowWidth;
        window_height_ = WindowHeight;
        position_ = Vector3f(0.0f, 0.0f, 0.0f);
        target_ = Vector3f(0.0f, 0.0f, 1.0f);
        up_ = Vector3f(0.0f, 1.0f, 0.0f);

        Init();
    }

    QuaternionCamera::QuaternionCamera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
    {
        window_width_ = WindowWidth;
        window_height_ = WindowHeight;
        position_ = Pos;

        target_ = Target;
        target_.Normalize();

        up_ = Up;
        up_.Normalize();

        Init();
    }

    void QuaternionCamera::SetWindowSize(int width, int height)
    {
        window_width_ = width;
        window_height_ = height;
    }

    void QuaternionCamera::Init()
    {
        Vector3f HTarget(target_.x, 0.0, target_.z);
        HTarget.Normalize();

        float Angle = ToDegree(asin(abs(HTarget.z)));

        if (HTarget.z >= 0.0f)
        {
            if (HTarget.x >= 0.0f)
            {
                angle_horz_ = 360.0f - Angle;
            }
            else
            {
                angle_horz_ = 180.0f + Angle;
            }
        }
        else
        {
            if (HTarget.x >= 0.0f)
            {
                angle_horz_ = Angle;
            }
            else
            {
                angle_horz_ = 180.0f - Angle;
            }
        }

        angle_vert_ = -ToDegree(asin(target_.y));

        is_upper_edge_ = false;
        is_lower_edge_ = false;
        is_left_edge_ = false;
        is_right_edge_ = false;

        mouse_pos_.x = window_width_ / 2;
        mouse_pos_.y = window_height_ / 2;

        speed_ = 1.0f;
        margin_ = 10;
        rotation_speed_ = 1.0f;
    }

    void QuaternionCamera::OnKeyboard(unsigned char key)
    {
        switch (key)
        {
        case 'w':
        case 'W':
            position_ += (target_ * speed_);
            break;

        case 's':
        case 'S':
            position_ -= (target_ * speed_);
            break;

        case 'a':
        case 'A':
        {
            Vector3f Left = target_.Cross(up_);
            Left.Normalize();
            Left *= speed_;
            position_ += Left;
        }
        break;

        case 'd':
        case 'D':
        {
            Vector3f Right = up_.Cross(target_);
            Right.Normalize();
            Right *= speed_;
            position_ += Right;
        }
        break;

        case GLUT_KEY_PAGE_UP:
            position_.y += speed_;
            break;
        case GLUT_KEY_PAGE_DOWN:
            position_.y -= speed_;
            break;
        }
    }

    void QuaternionCamera::OnMouse(int x, int y)
    {
        int DeltaX = x - mouse_pos_.x;
        int DeltaY = y - mouse_pos_.y;

        mouse_pos_.x = x;
        mouse_pos_.y = y;

        angle_horz_ += (float)DeltaX / 20.0f;
        angle_vert_ += (float)DeltaY / 50.0f;

        if (DeltaX == 0) {
            if (x <= margin_) {
                is_left_edge_ = true;
            }
            else if (x >= (window_width_ - margin_)) {
                is_right_edge_ = true;
            }
        }
        else {
            is_left_edge_ = false;
            is_right_edge_ = false;
        }

        if (DeltaY == 0) {
            if (y <= margin_) {
                is_upper_edge_ = true;
            }
            else if (y >= (window_height_ - margin_)) {
                is_lower_edge_ = true;
            }
        }
        else {
            is_upper_edge_ = false;
            is_lower_edge_ = false;
        }

        Update();
    }

    void QuaternionCamera::SetPosition(float x, float y, float z)
    {
        position_.x = x;
        position_.y = y;
        position_.z = z;
    }

    void QuaternionCamera::SetPosition(Vector3f new_position)
    {
        position_.x = new_position.x;
        position_.y = new_position.y;
        position_.z = new_position.z;
    }

    void QuaternionCamera::OnRender()
    {
        bool ShouldUpdate = false;

        if (is_left_edge_) {
            angle_horz_ -= rotation_speed_;
            ShouldUpdate = true;
        }
        else if (is_right_edge_) {
            angle_horz_ += rotation_speed_;
            ShouldUpdate = true;
        }

        if (is_upper_edge_) {
            if (angle_vert_ > -90.0f) {
                angle_vert_ -= rotation_speed_;
                ShouldUpdate = true;
            }
        }
        else if (is_lower_edge_) {
            if (angle_vert_ < 90.0f) {
                angle_vert_ += rotation_speed_;
                ShouldUpdate = true;
            }
        }

        if (ShouldUpdate) {
            Update();
        }
    }

    void QuaternionCamera::Update()
    {
        Vector3f Yaxis(0.0f, 1.0f, 0.0f);

        // Rotate the view vector by the horizontal angle around the vertical axis
        Vector3f View(1.0f, 0.0f, 0.0f);
        View.Rotate(angle_horz_, Yaxis);
        View.Normalize();

        // Rotate the view vector by the vertical angle around the horizontal axis
        Vector3f U = Yaxis.Cross(View);
        U.Normalize();
        View.Rotate(angle_vert_, U);

        target_ = View;
        target_.Normalize();

        up_ = target_.Cross(U);
        up_.Normalize();
    }

    Matrix4f QuaternionCamera::GetMatrix()
    {
        Matrix4f CameraTransformation;
        CameraTransformation.InitCameraTransform(position_, target_, up_);

        return CameraTransformation;
    }
}