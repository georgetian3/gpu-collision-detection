#include <camera.hpp>
#include <utils.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(
    const glm::dvec3 position,
    double yaw, double pitch,
    double speed, double sensivity,
    double zoom, double aspectRatio
) : position(position), yaw(yaw), pitch(pitch), speed(speed), sensitivity(sensivity), zoom(zoom), aspectRatio(aspectRatio) {

    directionVectors[0] = &front;
    directionVectors[1] = &right;
    directionVectors[2] = &worldUp;

    updateCameraVectors();
}

double       Camera::getZoom     () const {return zoom       ;}
double       Camera::getYaw      () const {return yaw        ;}
double       Camera::getPitch    () const {return pitch      ;}
glm::dvec3   Camera::getPosition () const {return position   ;}

glm::dmat4 Camera::getView() {
    updateCameraVectors();
    return view;
}

glm::dmat4 Camera::getProjection() {
    if (projectionChanged) {
        projection = glm::perspective(glm::radians(zoom), aspectRatio, nearField, farField);
        projectionChanged = false;
    }
    return projection;
}

void Camera::setPosition(const glm::dvec3 position) {
    this->position = position;
    viewChanged = true;
}

void Camera::pan(Direction direction, double dt) {
    std::cout << "panning\n";
    int dInt = static_cast<int>(direction);
    glm::dvec3* directionVectors[] = {&front, &right, &worldUp};
    position += *directionVectors[dInt / 2] * ((dInt % 2 ? -1 : 1) * speed * dt);
    viewChanged = true;
}

void Camera::setYaw(double yaw) {
    this->yaw = yaw;
    viewChanged = true;
}
void Camera::dYaw(double dYaw) {
    setYaw(yaw + dYaw * sensitivity);
}

void Camera::setPitch(double pitch) {
    this->pitch = clamp(pitch, -89.9, 89.9);
    viewChanged = true;
}
void Camera::dPitch(double dPitch) {
    setPitch(pitch + dPitch * sensitivity);
}

void Camera::setZoom(double zoom) {
    this->zoom = clamp(zoom, 0.0, 90.0);
    projectionChanged = true;
}
void Camera::dZoom(double dZoom) {
    setZoom(zoom + dZoom);
}

void Camera::setAspectRatio(double aspectRatio) {
    this->aspectRatio = clamp(aspectRatio, 0.0, 999.0);
    projectionChanged = true;
}

void Camera::updateCameraVectors() {
    if (!viewChanged) {
        return;
    }
    viewChanged = false;
    double yawRadians = glm::radians(yaw);
    double pitchRadians = glm::radians(pitch);
    double cosPitchRadians = cos(pitchRadians);

    lookDirection.x = cos(yawRadians) * cosPitchRadians;
    lookDirection.y = sin(pitchRadians);
    lookDirection.z = sin(yawRadians) * cosPitchRadians;
    lookDirection = glm::normalize(lookDirection);

    front.x = lookDirection.x;
    front.y = 0;
    front.z = lookDirection.z;
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(lookDirection, worldUp));
    up    = glm::normalize(glm::cross(right, lookDirection));

    view = glm::lookAt(position, position + lookDirection, up);

}