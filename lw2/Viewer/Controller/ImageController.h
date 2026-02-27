#pragma once

#include "../Model/Image.h"

class ImageController
{
public:
	explicit ImageController(Image& model);
	void OnOpenFile() const;
private:
	Image& m_image;
};
