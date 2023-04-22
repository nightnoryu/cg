#pragma once

#include "BaseWindow.h"
#include "Cottage.h"
#include "Environment.h"
#include "TextureLoader.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, char const* title);

	~Window() noexcept;

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	// ¬ращаем камеру вокруг начала координат
	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnKey(int key) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;

	void SetupCameraMatrix();

	// –ассто€ние от камеры до точки вращени€
	static constexpr double DISTANCE_TO_ORIGIN = 12;

	static constexpr glm::vec4 NO_FOG = { 1, 1, 1, 1 };
	static constexpr glm::vec4 PLAIN_FOG = { 0.3f, 0.3f, 0.3f, 1 };
	static constexpr glm::vec4 NIGHT_FOG = { 0, 0, 0, 1 };

	TextureLoader m_textureLoader;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, -DISTANCE_TO_ORIGIN, 10.0 },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 0.0, 1.0 });

	bool m_fogEnabled = false;
	glm::vec4 m_fogColor = NO_FOG;

	Cottage m_cottage;
	Environment m_environment;

	TextureHandle m_groundTexture;

	TextureHandle m_wallTexture;
	TextureHandle m_windowTexture;
	TextureHandle m_doorTopTexture, m_doorBottomTexture;
};
