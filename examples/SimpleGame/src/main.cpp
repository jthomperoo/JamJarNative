#include "emscripten/html5.h"
#include "entity/entity_manager.hpp"
#include "game.hpp"
#include "message/message_bus.hpp"
#include "message/message_payload.hpp"
#include "simple_game.hpp"
#include "standard/interpolation/interpolation_system.hpp"
#include "standard/motion/motion_system.hpp"
#include "standard/primitive/primitive_system.hpp"
#include "standard/webgl2/webgl2_system.hpp"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {

    std::cout << "game start" << std::endl;

    // Set up canvas
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    auto context = emscripten_webgl_create_context("#game-canvas", &attrs);
    auto res = emscripten_webgl_make_context_current(context);

    auto messageBus = new JamJar::MessageBus();
    new JamJar::EntityManager(messageBus);
    auto game = new SimpleGame(messageBus);
    new JamJar::Standard::WebGL2System(messageBus, context);
    new JamJar::Standard::MotionSystem(messageBus);
    new JamJar::Standard::PrimitiveSystem(messageBus);
    new JamJar::Standard::InterpolationSystem(messageBus);
    game->Start();

    return 0;
}
