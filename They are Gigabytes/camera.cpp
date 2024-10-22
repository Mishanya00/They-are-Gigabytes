#include <glut.h>

#include "camera.hpp"


namespace rgl
{
    //------------------------------------------------//
    //              Quaternion camera                 //
    //------------------------------------------------//

    Camera::Camera(int WindowWidth, int WindowHeight)
    {
        window_width_ = WindowWidth;
        window_height_ = WindowHeight;
        position_ = Vector3f(0.0f, 0.0f, 0.0f);
        target_ = Vector3f(0.0f, 0.0f, 1.0f);
        up_ = Vector3f(0.0f, 1.0f, 0.0f);

        Init();
    }

    Camera::Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up, const Vector3f& Left)
    {
        window_width_ = WindowWidth;
        window_height_ = WindowHeight;
        position_ = Pos;

        target_ = Target;
        target_.Normalize();

        up_ = Up;
        up_.Normalize();

        left_ = Up;
        left_.Normalize();

        Init();
    }

    void Camera::MoveAcrossVector(Vector3f const & target_vector, bool isNotVertMove, float distance)
    {
        if (distance == 0)
        {
            if (isNotVertMove)
                position_ += target_vector * speed_;
            else
            {
                position_.x += target_vector.x * speed_;
                position_.z += target_vector.z * speed_;
            }
        }   
        else
        {
            if (isNotVertMove)
                position_ += target_vector * distance;
            else
            {
                position_.x += target_vector.x * distance;
                position_.z += target_vector.z * distance;
            }
        }
    }

    void Camera::SetWindowSize(int width, int height)
    {
        window_width_ = width;
        window_height_ = height;
    }

    void Camera::Rotate(float rotX, float rotY, float rotZ)
    {
        angle_vert_ += rotX;
        angle_horz_ += rotY;

        Update();
    }

    void Camera::RotateAroundTargetPoint(float alfa)
    {
        float sf = fabs(position_.y / target_.y); // scale factor
        Vector3f old_position = position_;
        MoveAcrossVector(target_, true, sf); // sf equals distance because vector is normalized
        Rotate(0, alfa, 0);
        MoveAcrossVector(-target_, true, sf);
        /*
        float radius = sqrtf(sqrf(sf * target_.x) + sqrf(sf * target_.z));
        float theta = atanf( ( (sf * target_.x) - fabs(position_.x) ) / ( (sf * target_.z) - fabs(position_.z) ) );
        
        position_.x *= sinf(theta + ToRadian(alfa));
        position_.z *= cosf(theta + ToRadian(alfa));*/
    }

    void Camera::Init()
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

    void Camera::OnKeyboard(unsigned char key)
    {
        switch (key)
        {
        case GLUT_KEY_PAGE_UP:
            if (speed_ < 0.2f)
                speed_ += 0.01f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            if (speed_ > 0.01f)
                speed_ -= 0.01f;
            break;
        }
    }

    void Camera::SetSpeed(float new_speed)
    {
        speed_ = new_speed;
    }

    void Camera::SetRotationSpeed(float new_rotation_speed)
    {
        rotation_speed_ = new_rotation_speed;
    }

    void Camera::OnFrame()
    {
        bool isMoved = false;
        // OS dependent realization
        // Camera movement without height change
        if (GetAsyncKeyState('W'))
        {
            MoveAcrossVector(target_, false);
            isMoved = true;
        }
        if (GetAsyncKeyState('S'))
        {
            MoveAcrossVector(-target_, false);
            isMoved = true;
        }
        if (GetAsyncKeyState('A'))
        {
            MoveAcrossVector(-left_, false);
            isMoved = true;
        }
        if (GetAsyncKeyState('D'))
        {
            MoveAcrossVector(left_, false);
            isMoved = true;
        }
        if (GetAsyncKeyState('E') && !is_lower_edge_ && !is_upper_edge_ && !is_left_edge_ && !is_right_edge_ && !isMoved)
        {
            RotateAroundTargetPoint(rotation_speed_);
            //Rotate(0, rotation_speed_, 0);
        }
        if (GetAsyncKeyState('Q') && !is_lower_edge_ && !is_upper_edge_ && !is_left_edge_ && !is_right_edge_ && !isMoved)
        {
            RotateAroundTargetPoint(-rotation_speed_);
            //Rotate(0, -rotation_speed_, 0);
        }

        Update();
    }

    void Camera::OnMouse(int button, int state, int x, int y)
    {
        mouse_pos_.x = x;
        mouse_pos_.y = y;

        switch (button)
        {   // mouse wheel lacks special const to determine. So according to docs its 3 and 4
        case 3:
            if (position_.y > 1.0f)
                position_ += target_ * speed_;
            break;
        case 4:
            position_ -= target_ * speed_;
            break;
        }

        if (x <= margin_) {
            is_left_edge_ = true;
        }
        else if (x >= (window_width_ - margin_)) {
            is_right_edge_ = true;
        }
        else {
            is_left_edge_ = false;
            is_right_edge_ = false;
        }

        if (y <= margin_) {
            is_upper_edge_ = true;
        }
        else if (y >= (window_height_ - margin_)) {
            is_lower_edge_ = true;
        }
        else {
            is_upper_edge_ = false;
            is_lower_edge_ = false;
        }

        Update();
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

    void Camera::OnRender()
    {
        bool ShouldUpdate = false;

        if (is_left_edge_) {
            MoveAcrossVector(-left_, false);
        }
        else if (is_right_edge_) {
            MoveAcrossVector(left_, false);
        }

        if (is_upper_edge_) {
                MoveAcrossVector(target_, false);
        }
        else if (is_lower_edge_) {
                MoveAcrossVector(-target_, false);
        }
    }

    void Camera::Update()
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

        left_ = U;
        left_.Normalize();
    }

    Matrix4f Camera::GetMatrix()
    {
        Matrix4f CameraTransformation;
        CameraTransformation.InitCameraTransform(position_, target_, up_);

        return CameraTransformation;
    }
}