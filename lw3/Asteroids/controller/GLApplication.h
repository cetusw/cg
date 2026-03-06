#pragma once

class GLApplication
{
public:
	void MainLoop();

protected:
	explicit GLApplication(
		const char* title,
		int width = 0,
		int height = 0,
		bool needDepth = true,
		bool needStencil = false);
	virtual ~GLApplication();

	virtual void OnInit();
	virtual void OnDisplay() = 0;
	virtual void OnReshape(int width, int height);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	[[nodiscard]] bool IsKeyPressed(unsigned char key) const;
	[[nodiscard]] bool IsSpecialKeyPressed(int key) const;
	virtual void OnMouse(int button, int state, int x, int y);
	virtual void OnMotion(int x, int y);
	virtual void OnIdle();

	static void PostRedisplay();

	[[nodiscard]] float GetDeltaTime() const;

private:
	static void InitEventHandlers();
	static void DisplayHandler();
	static void ReshapeHandler(int width, int height);
	static void KeyboardHandler(unsigned char key, int x, int y);
	static void KeyboardUpHandler(unsigned char key, int x, int y);
	static void SpecialHandler(int key, int x, int y);
	static void SpecialUpHandler(int key, int x, int y);
	static void MouseHandler(int button, int state, int x, int y);
	static void MotionHandler(int x, int y);
	static void IdleHandler();

	static GLApplication* m_pApplication;
	bool m_keys[256] = { false };
	bool m_specialKeys[256] = { false };
	int m_lastTime = 0;
	float m_deltaTime = 0;
};
