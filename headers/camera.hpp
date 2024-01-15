#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum class Direction {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Camera {

    glm::dvec3 position;
    glm::dvec3 lookDirection;
    glm::dvec3 up;
    glm::dvec3 front;
    glm::dvec3 right;
    glm::dvec3 worldUp = glm::dvec3(0.0, 1.0, 0.0);

    glm::dvec3* directionVectors[3];

    double yaw;
    double pitch;
    double speed;
    double sensitivity;
    double zoom;
    double aspectRatio;
    double nearField = 0.1;
    double farField = 1000.0;

    bool viewChanged = true;
    bool projectionChanged = true;

    glm::dmat4 projection;
    glm::dmat4 view;

    void updateCameraVectors();

public:

    Camera(
        const glm::dvec3 position = glm::dvec3(0.0),
        double yaw = 270, double pitch = 0, 
        double speed = 1, double sensitivity = 0.1,
        double zoom = 45, double aspectRatio = 16.0 / 9.0
    );

    glm::dmat4 getView();
    glm::dmat4 getProjection();

    glm::dvec3 getPosition() const;
    void setPosition(const glm::dvec3 position);
    void pan(Direction direction, double dt);

    double getYaw() const;
    void setYaw(double yaw);
    void dYaw(double dYaw);

    double getPitch() const;
    void setPitch(double pitch);
    void dPitch(double dPitch);

    double getZoom() const;
    void setZoom(double zoom);
    void dZoom(double dZoom);

    void setAspectRatio(double aspectRadio);

    double getSensitivity() const {
        return sensitivity;
    }
    void setSensitivity(double sensitivity) {
        this->sensitivity = sensitivity;
    }
    double getSpeed() const {
        return speed;
    }
    void setSpeed(double speed) {
        this->speed = speed;
    }
    double getNearField() const {
        return nearField;
    }
    double getFarField() const {
        return farField;
    }

    glm::dvec3 getLookDirection() {
        updateCameraVectors();
        return lookDirection;
    }

    glm::dvec3 getRight() {
        updateCameraVectors();
        return right;
    }

    glm::dvec3 getUp() {
        updateCameraVectors();
        return up;
    }

    glm::dvec3 getWorldUp() {
        updateCameraVectors();
        return worldUp;
    }



};

#endif