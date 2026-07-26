//高いリフレッシュレートでもfpsを60に貼り付ける

#include "framework.h"

void gmain()
{
	window("love", 1920, 1080, full);

	float ar = 300, ax = width / 2, ay = height / 2, vx = 5, vy = 8;
	float br = 200, bx = 0, by = 0;
	float red = 255, green = 255, blue = 0, alpha = 255;

	while (!quit())
	{
		ax += vx;
		ay += vy;
		if (ax > width)vx *= -1;
		if (ax < 0)vx *= -1;
		if (ay > height)vy *= -1;
		if (ay < 0)vy *= -1;

		bx = mouseX;
		by = mouseY;

		float x = ax - bx;
		float y = ay - by;
		float z_sq = x * x + y * y;
		float d = ar + br;
		float d_sq = d * d;
		if (z_sq > d_sq) {
			red = 255, green = 255, blue = 0, alpha = 255;
		}
		else {
			red = 255, green = 0, blue = 0, alpha = 200;
		}

		begin();
		
		fill(255,255,255);
		rect(width/2, height/2, width, height);
		
		fill(red, green, blue, alpha);
		circle(ax, ay, ar * 2);
		circle(bx, by, br * 2);
		
		printInfo();
		end();
		waitFPS();
	}
}
