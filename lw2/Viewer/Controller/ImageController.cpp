#include "ImageController.h"
#include "../Utils/PipeDescriptor.h"

ImageController::ImageController(Image& model)
	: m_image(model)
{
}

void ImageController::OnOpenFile() const
{
	std::string result;

	const PipeDescriptor pipe("zenity --file-selection --title=\"Open Image\" --file-filter=\"*.png *.jpg *.jpeg *.bmp\"", "r");

	if (!pipe.IsOpen())
	{
		return;
	}

	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), pipe.Get()))
	{
		result += buffer;
	}

	if (!result.empty() && result.back() == '\n')
	{
		result.pop_back();
	}

	if (!result.empty())
	{
		m_image.LoadImage(result);
	}
}