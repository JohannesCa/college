#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat YAW        =  180.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.2f;
const GLfloat ZOOM       =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Eular Angles
    GLfloat Yaw;
    GLfloat Pitch;
    // Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
    {
        this->Position = position;
        this->WorldUp = up;
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
    {
        this->Position = glm::vec3(posX, posY, posZ);
        this->WorldUp = glm::vec3(upX, upY, upZ);
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime, GLfloat offsetY, GLboolean Colision = true)
    {
        GLfloat velocity = this->MovementSpeed * deltaTime;
        if (direction == FORWARD)
            this->Position += glm::normalize(glm::rotate(this->Front, glm::radians(this->Pitch), -this->Right)) * velocity;
        if (direction == BACKWARD)
            this->Position -= glm::normalize(glm::rotate(this->Front, glm::radians(this->Pitch), -this->Right)) * velocity;
        if (direction == LEFT)
            this->Position -= this->Right * velocity;
        if (direction == RIGHT)
            this->Position += this->Right * velocity;

        this->Position.y += offsetY;

        if(Colision)
            testMapColision();
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        this->Yaw   += xoffset;
        this->Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (this->Pitch > 89.0f)
                this->Pitch = 89.0f;
            if (this->Pitch < -89.0f)
                this->Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Eular angles
        this->updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(GLfloat yoffset)
    {
        if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
            this->Zoom -= yoffset;
        if (this->Zoom <= 1.0f)
            this->Zoom = 1.0f;
        if (this->Zoom >= 45.0f)
            this->Zoom = 45.0f;
    }

private:
    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
        front.y = sin(glm::radians(this->Pitch));
        front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
        this->Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
    }

    void testMapColision()
    {
        // Test outer map boundaries
        if(this->Position.z > 4.8)
            this->Position.z = 4.8;
        if(this->Position.z < -4.8)
            this->Position.z = -4.8;
        if(this->Position.x > 7.3)
            this->Position.x = 7.3;
        if(this->Position.x < -7.3)
            this->Position.x = -7.3;


        // Check intern map boundaries
        if((this->Position.x > -2.2)&&(this->Position.x < 2.2)){
            if((this->Position.z < 2.2)&&(this->Position.z > 2))
                this->Position.z = 2.2;
            if((this->Position.z > -2.2)&&(this->Position.z < -2))
                this->Position.z = -2.2;
            if((this->Position.z > 1.6)&&(this->Position.z < 2))
                this->Position.z = 1.6;
            if((this->Position.z < -1.6)&&(this->Position.z > -2))
                this->Position.z = -1.6;
        }

        if((this->Position.x > -2.8)&&(this->Position.x < -1.9)){
            if((this->Position.z < 1.2)&&(this->Position.z > 0.8))
                this->Position.z = 1.2;
            if((this->Position.z > -1.2)&&(this->Position.z < -0.8))
                this->Position.z = -1.2;

            if((this->Position.z < 1)&&(this->Position.z > -1)){
                this->Position.y = 0.667 * (this->Position.x + 3) + 1.6; // Ramp equation
                if((this->Position.z > 0.6)&&(this->Position.z < 1))
                    this->Position.z = 0.6;
                if((this->Position.z < -0.6)&&(this->Position.z > -1))
                    this->Position.z = -0.6;
            }
        }

        if((this->Position.z < 2.2)&&(this->Position.z > -2.2)){
            if((this->Position.x > -2.3)&&(this->Position.x < -2)){
                if((this->Position.z > 1)||(this->Position.z < -1))
                    this->Position.x = -2.3;
            }
            if((this->Position.x < -1.6)&&(this->Position.x > -2)){
                if((this->Position.z > 1)||(this->Position.z < -1))
                    this->Position.x = -1.6;
            }
            if((this->Position.x < 2.3)&&(this->Position.x > 2))
                this->Position.x = 2.3;
            if((this->Position.x > 1)&&(this->Position.x < 2))
                this->Position.x = 1;
        }
    }
};


