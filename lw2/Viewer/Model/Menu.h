#pragma once

#include "Observable/Observable.h"
#include <SFML/System/Vector2.hpp>

class Menu : public Observable
{
public:
	enum class Item
	{
		None,
		File,
		OpenFile
	};

	static constexpr float TOP_BAR_HEIGHT = 70.f;
	static constexpr float DROPDOWN_WIDTH = 240.f;

	[[nodiscard]] Item GetItemAt(sf::Vector2i mousePosition) const;
	void ToggleFileMenu();
	void Close();
	[[nodiscard]] bool IsFileMenuOpen() const;

private:
	bool m_isFileMenuOpen = false;
};
