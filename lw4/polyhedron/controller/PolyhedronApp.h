#pragma once
#include "../view/Polyhedron.h"
#include "GLFWApplication.h"
#include <glm/glm.hpp>

class PolyhedronApp final : public GLFWApplication
{
public:
	PolyhedronApp(int width, int height, const char* title);

private:
	bool m_isDragging;
	glm::dvec2 m_mousePos;
	glm::dmat4 m_camera = glm::dmat4(1.0);
	Polyhedron m_polyhedron;

	static constexpr double Z_NEAR = 0.5;
	static constexpr double Z_FAR = 10;
	static constexpr double FRUSTUM_SIZE = 2.0;

	void OnInit() override;
	void OnReshape(int width, int height) override;
	void OnDisplay() override;
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;
	void OnMouseMove(double x, double y) override;

	void RotateCamera(double xAngle, double yAngle);
	static void SetLight();
};
