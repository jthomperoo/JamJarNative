#ifndef STANDARD_CAMERA_CAMERA_HPP
#define STANDARD_CAMERA_CAMERA_HPP

#include "component/component.hpp"
#include "geometry/matrix_4d.hpp"
#include "geometry/vector_2d.hpp"
#include "render/color.hpp"

namespace JamJar {
namespace Standard {
class Camera : public Component {
  public:
    constexpr static uint32_t CAMERA_KEY = JamJar::hash("jamjar_camera");
    explicit Camera();
    explicit Camera(Color backgroundColor);
    explicit Camera(Color backgroundColor, Vector2D viewportPosition);
    explicit Camera(Color backgroundColor, Vector2D viewportPosition, Vector2D viewportScale);
    explicit Camera(Color backgroundColor, Vector2D viewportPosition, Vector2D viewportScale, Vector2D virtualScale);

    Color m_backgroundColor;
    Vector2D m_viewportPosition;
    Vector2D m_viewportScale;
    Vector2D m_virtualScale;

    [[nodiscard]] Matrix4D ProjectionMatrix() const;
};
}; // namespace Standard
}; // namespace JamJar

#endif
