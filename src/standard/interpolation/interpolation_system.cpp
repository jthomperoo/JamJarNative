#include "standard/interpolation/interpolation_system.hpp"
#include "component/component.hpp"
#include "entity/entity.hpp"
#include "game.hpp"
#include "message/message.hpp"
#include "message/message_bus.hpp"
#include "standard/transform/transform.hpp"

JamJar::Standard::InterpolationSystem::InterpolationSystem(MessageBus *messageBus)
    : MapSystem(messageBus, JamJar::Standard::InterpolationSystem::evaluator) {
    this->m_messageBus->Subscribe(this, JamJar::Game::MESSAGE_POST_RENDER);
}

bool hasTransform(JamJar::Component *component) {
    return component->m_key == JamJar::Standard::Transform::TRANSFORM_KEY;
}

// NOLINTNEXTLINE(misc-unused-parameters)
bool JamJar::Standard::InterpolationSystem::evaluator(Entity *entity,
                                                      const std::vector<JamJar::Component *> &components) {
    return std::any_of(components.begin(), components.end(), hasTransform);
}

void JamJar::Standard::InterpolationSystem::OnMessage(JamJar::Message *message) {
    MapSystem::OnMessage(message);
    switch (message->m_type) {
    case JamJar::Game::MESSAGE_POST_RENDER: {
        this->interpolate();
        break;
    }
    }
}

void JamJar::Standard::InterpolationSystem::interpolate() {
    for (const auto &entityPair : this->m_entities) {
        auto entity = entityPair.second;
        auto *transform =
            static_cast<JamJar::Standard::Transform *>(entity.Get(JamJar::Standard::Transform::TRANSFORM_KEY));

        transform->m_previous = transform->m_position;
    }
}
