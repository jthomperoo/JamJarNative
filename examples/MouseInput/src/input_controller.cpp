#include "input_controller.hpp"
#include "message/message_payload.hpp"
#include "render/material.hpp"
#include "standard/2d/camera/camera.hpp"
#include "standard/2d/sprite/sprite.hpp"
#include "standard/2d/transform/transform.hpp"
#include "standard/sdl2_input/sdl2_input_system.hpp"
#include <SDL2/SDL.h>

bool InputController::evaluator(JamJar::Entity *entity, const std::vector<JamJar::Component *> &components) {
    for (const auto &component : components) {
        if (component->key == JamJar::Standard::_2D::Camera::KEY) {
            return true;
        }
    }
    return false;
}

InputController::InputController(JamJar::MessageBus *messageBus, SDL_Window *window)
    : JamJar::MapSystem(messageBus, InputController::evaluator), window(window) {
    this->messageBus->Subscribe(this, JamJar::Standard::SDL2InputSystem::MESSAGE_MOUSE_BUTTON_DOWN_EVENT);
}

void InputController::OnMessage(JamJar::Message *message) {
    MapSystem::OnMessage(message);
    switch (message->type) {
    case JamJar::Standard::SDL2InputSystem::MESSAGE_MOUSE_BUTTON_DOWN_EVENT: {
        auto *eventMessage = static_cast<JamJar::MessagePayload<JamJar::Standard::SDL2MouseEvent> *>(message);
        auto event = eventMessage->payload;

        if (this->entities.size() <= 0) {
            break;
        }

        auto cameraEntity = this->entities.begin()->second;
        auto transform =
            static_cast<JamJar::Standard::_2D::Transform *>(cameraEntity.Get(JamJar::Standard::_2D::Transform::KEY));
        auto camera =
            static_cast<JamJar::Standard::_2D::Camera *>(cameraEntity.Get(JamJar::Standard::_2D::Camera::KEY));

        auto worldPos = JamJar::Standard::_2D::MousePositionToWorldPosition(event.position, transform->position, camera,
                                                                            this->window);

        auto smiley = new JamJar::Entity(messageBus);
        smiley->Add(std::move(std::make_unique<JamJar::Standard::_2D::Transform>(worldPos, JamJar::Vector2D(5, 5))));
        smiley->Add(std::move(std::make_unique<JamJar::Standard::_2D::Sprite>(
            JamJar::Material(JamJar::Color(0, 1, 1, 1), JamJar::Texture(JamJar::hash("smiley"))))));
        break;
    }
    }
}
