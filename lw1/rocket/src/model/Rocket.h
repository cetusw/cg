#pragma once

#include "Picture.h"

class Rocket
{
public:
	Rocket();

	[[nodiscard]] Picture& GetPicture();
	[[nodiscard]] const Picture& GetPicture() const;

private:
	Picture m_picture;
};
