#pragma once

#include "Observable/Observable.h"
#include <SFML/System/Vector2.hpp>

class WindowSettings : public Observable
{
public:
	void SetWindowSize(sf::Vector2u size);
	[[nodiscard]] sf::Vector2u GetWindowSize() const;

private:
	sf::Vector2u m_windowSize{ 1920, 1080 };
};
