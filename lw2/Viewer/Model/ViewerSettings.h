#pragma once

enum class BackgroundType
{
	Chessboard,
	White,
};

struct ViewerSettings
{
	BackgroundType bgType = BackgroundType::Chessboard;
};