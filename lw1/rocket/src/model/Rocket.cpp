#include "Rocket.h"

#include <utility>

#include <SFML/Graphics/Shape.hpp>

namespace
{
	constexpr float OutlineThickness = 3.0f;

	void SetOutline(sf::Shape& shape)
	{
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(OutlineThickness);
	}
}

Rocket::Rocket()
	: m_picture({450.0f, 350.0f})
{
	sf::ConvexShape leftFin;
	leftFin.setPointCount(3);
	leftFin.setPoint(0, {-50.0f, 40.0f});
	leftFin.setPoint(1, {-90.0f, 120.0f});
	leftFin.setPoint(2, {-50.0f, 120.0f});
	leftFin.setFillColor(sf::Color::Green);
	SetOutline(leftFin);
	m_picture.AddPrimitive(std::move(leftFin));

	sf::ConvexShape rightFin;
	rightFin.setPointCount(3);
	rightFin.setPoint(0, {50.0f, 40.0f});
	rightFin.setPoint(1, {90.0f, 120.0f});
	rightFin.setPoint(2, {50.0f, 120.0f});
	rightFin.setFillColor(sf::Color::Green);
	SetOutline(rightFin);
	m_picture.AddPrimitive(std::move(rightFin));

	sf::RectangleShape body;
	body.setPosition({-50.0f, -100.0f});
	body.setSize({100.0f, 220.0f});
	body.setFillColor(sf::Color::Blue);
	SetOutline(body);
	m_picture.AddPrimitive(std::move(body));

	sf::ConvexShape nose;
	nose.setPointCount(3);
	nose.setPoint(0, {-50.0f, -100.0f});
	nose.setPoint(1, {0.0f, -190.0f});
	nose.setPoint(2, {50.0f, -100.0f});
	nose.setFillColor(sf::Color::Red);
	SetOutline(nose);
	m_picture.AddPrimitive(std::move(nose));

	sf::CircleShape window;
	window.setRadius(22.0f);
	window.setOrigin({22.0f, 22.0f});
	window.setPosition({0.0f, -30.0f});
	window.setFillColor(sf::Color::White);
	SetOutline(window);
	m_picture.AddPrimitive(std::move(window));
}

Picture& Rocket::GetPicture()
{
	return m_picture;
}

const Picture& Rocket::GetPicture() const
{
	return m_picture;
}
