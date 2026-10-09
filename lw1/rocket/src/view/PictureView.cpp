#include "PictureView.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transform.hpp>

void PictureView::Render(sf::RenderTarget& target, const Picture& picture)
{
	sf::Transform transform;
	transform.translate(picture.GetPosition());
	const sf::RenderStates states(transform);

	for (const Primitive& primitive : picture.GetPrimitives())
	{
		std::visit(
			[&target, &states](const auto& shape)
			{
				target.draw(shape, states);
			},
			primitive);
	}
}
