#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "../model/Picture.h"

class PictureView
{
public:
	static void Render(sf::RenderTarget& target, const Picture& picture);
};
