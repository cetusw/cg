#pragma once
#include "GLApplication.h"
#include "model/Ship.h"
#include "view/GameView.h"

class AsteroidsApplication final : public GLApplication
{
public:
	AsteroidsApplication(const char* title, int width, int height);

protected:
	void OnInit() override;
	void OnDisplay() override;
	void OnReshape(int width, int height) override;
	void OnIdle() override;

private:
	Ship m_ship;
	GameView m_view;
	float m_worldWidth = 1.0f;
	float m_worldHeight = 1.0f;
};