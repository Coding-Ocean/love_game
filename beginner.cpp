#include"beginner.h"

void begin()
{
	setDeltaTime();
	getInputState();
	if (isTrigger(KEY_ESC))
	{
		closeWindow();
	}
	beginMsaaRender();
}

void end()
{
	cursor();
	endMsaaRender();
}

void info()
{
	print("w:%d h:%d", (int)width, (int)height);
	print("mx:%d my:%d", (int)mouseX, (int)mouseY);
	print("%.3f", delta);
}
