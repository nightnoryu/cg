#pragma once

#include "BaseWindow.h"
#include "Cottage.h"
#include "TextureLoader.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, char const* title);

	~Window() noexcept;

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	// ������� ������ ������ ������ ���������
	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;

	void SetupCameraMatrix();

	// ���������� �� ������ �� ����� ��������
	static constexpr double DISTANCE_TO_ORIGIN = 15;

	TextureLoader m_textureLoader;

	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 1.0, 0.0 });

	Cottage m_cottage;
	TextureHandle m_wallTexture;
	TextureHandle m_windowTexture;
	TextureHandle m_doorTopTexture, m_doorBottomTexture;
};