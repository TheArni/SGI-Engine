/* 
 * File:   ControllableEntity.cpp
 * Author: arnau
 * 
 * Created on 11 / de setembre / 2015, 20:54
 */

#include "ControllableEntity.h"

ControllableEntity::ControllableEntity(float speed) {
    this->speed = speed;
}


//TODO: Mappable controls

bool ControllableEntity::processSDLEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        cameraYaw += (event.motion.xrel) * 0.1f;
        cameraPitch += (event.motion.yrel) * -0.1f;
        if (cameraPitch > 89.0f)
            cameraPitch = 89.0f;
        else if (cameraPitch < -89.0f)
            cameraPitch = -89.0f;
        if (cameraYaw > 360)
            cameraYaw = 0;
        else if (cameraYaw < 0)
            cameraYaw = 360;
    } else {
        return false;
    }
    return true;
}

void ControllableEntity::update() {
    motionX = 0;
    motionY = 0;
    motionZ = 0;
    float movSpeed = speed;

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) motionX++;
    if (keystate[SDL_SCANCODE_S]) motionX--;
    if (keystate[SDL_SCANCODE_A]) motionZ--;
    if (keystate[SDL_SCANCODE_D]) motionZ++;
    if (keystate[SDL_SCANCODE_F] || keystate[SDL_SCANCODE_SPACE]) motionY++;
    if (keystate[SDL_SCANCODE_C]) motionY--;
    if (keystate[SDL_SCANCODE_LSHIFT]) movSpeed *= 2;
    if (keystate[SDL_SCANCODE_LCTRL]) movSpeed /= 2;

    glm::vec3 front;
    front.x = cos(glm::radians(cameraPitch)) * cos(glm::radians(cameraYaw));
    front.y = sin(glm::radians(cameraPitch));
    front.z = cos(glm::radians(cameraPitch)) * sin(glm::radians(cameraYaw));
    front = glm::normalize(front);
    position += front * motionX * movSpeed;
    position += glm::vec3(sin(glm::radians(-cameraYaw)), 0, cos(glm::radians(-cameraYaw))) * motionZ * movSpeed;
    position += glm::vec3(0, 1, 0) * motionY * movSpeed;
}