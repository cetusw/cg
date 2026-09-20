#include "Garage.h"

namespace Material
{
constexpr MaterialDescription Ground{
	{ 0.10f, 0.20f, 0.10f },
	{ 0.35f, 0.65f, 0.30f },
	{ 0.05f, 0.05f, 0.05f },
	4.0f
};

constexpr MaterialDescription Wall{
	{ 0.30f, 0.10f, 0.08f },
	{ 0.75f, 0.25f, 0.15f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};

constexpr MaterialDescription Roof{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.60f, 0.60f, 0.60f },
	{ 0.15f, 0.15f, 0.15f },
	12.0f
};

constexpr MaterialDescription Foundation{
	{ 0.15f, 0.15f, 0.15f },
	{ 0.50f, 0.50f, 0.50f },
	{ 0.10f, 0.10f, 0.10f },
	4.0f
};

constexpr MaterialDescription Window{
	{ 0.10f, 0.15f, 0.20f },
	{ 0.25f, 0.45f, 0.65f },
	{ 0.80f, 0.80f, 0.80f },
	64.0f
};

constexpr MaterialDescription Door{
	{ 0.18f, 0.08f, 0.03f },
	{ 0.45f, 0.20f, 0.08f },
	{ 0.10f, 0.10f, 0.10f },
	8.0f
};
} // namespace Material

Garage::Garage(const Vector3 position)
	: m_position(position)
{
}

std::vector<SceneObject> Garage::CreateObjects() const
{
	return {
		{ "Garage body",
			{ GeometryType::Box, 3.0f, 4.0f, 2.5f },
			{ m_position },
			Material::Wall,
			"assets/brick.jpg" },
		{ "Garage door",
			{ GeometryType::Box, 2.2f, 0.10f, 2.0f },
			{ { m_position.x, m_position.y - 2.05f, m_position.z } },
			Material::Door,
			{} },
		{ "Garage window",
			{ GeometryType::Box, 0.8f, 0.08f, 0.8f },
			{ { m_position.x + 1.54f, m_position.y, m_position.z + 1.1f },
				{ 0.0f, 0.0f, 90.0f } },
			Material::Window,
			{} }
	};
}
