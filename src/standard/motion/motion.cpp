#include "standard/motion/motion.hpp"
#include "component/component.hpp"
#include "geometry/vector_2d.hpp"
#include "hash.hpp"

JamJar::Standard::Motion::Motion(Vector2D velocity, Vector2D acceleration, float angularVelocity,
                                 float angularAcceleration)
    : Component(JamJar::Standard::Motion::MOTION_KEY), m_velocity(velocity), m_acceleration(acceleration),
      m_angularVelocity(angularVelocity), m_angularAcceleration(angularAcceleration) {}

JamJar::Standard::Motion::Motion(Vector2D velocity, Vector2D acceleration, float angularVelocity)
    : Motion(velocity, acceleration, angularVelocity, 0) {}

JamJar::Standard::Motion::Motion(Vector2D velocity, Vector2D acceleration) : Motion(velocity, acceleration, 0, 0) {}

JamJar::Standard::Motion::Motion(Vector2D velocity) : Motion(velocity, Vector2D(), 0, 0) {}

JamJar::Standard::Motion::Motion() : Motion(Vector2D(), Vector2D(), 0, 0) {}
