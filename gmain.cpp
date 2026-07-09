//ラジアン値の説明用

#include "..\love\framework.h"

//ax,ayを始点とした弧を描く
void arc360(float ox, float oy, float ax, float ay, float radian)
{
	ax -= ox;
	ay -= oy;
	float al = sqrtf(ax * ax + ay * ay);
	if (al < 1e-5f) return;
	ax /= al;
	ay /= al;

	// 1. acosfで基本のなす角（0〜180度）を計算
	float rad = acosf(ax * 1 + ay * 0);

	// 2. 外積を使って、どちら側にあるかを判定
	float cross = ax * 0 - ay * 1;

	// 3. 外積が負の場合、180度を超えた「外側の角」にする
	// 元のコードの回転方向に合わせるため、crossの符号で分岐します
	if (cross < 0) 
	{
		rad = 2 * 3.14159265f - rad;
	}

	for (float r = rad; r < radian+rad; r += (0.0174532f/2)) 
	{
		float cr = cosf(r);
		float sr = sinf(r);
		float x = ax * cr - ay * sr;
		float y = ax * sr + ay * cr;
		// 反時計回り
		point(ox + cr * al, oy - sr * al);
	}
}

void gmain()
{
#if 1
	window("love", 1920, 1080, full);
#else
	window("love", 1280, 720, win);
#endif

	float ox = width / 2.0f;
	float oy = height / 2.0f;
	float unit = width / 6.28f;

	int deg = 60;
	while (!quit())
	{
		begin();

		/*描画する------------------------------*/
		//背景
		noStroke();
		fill(40,40,40);
		rectMode(CORNER);
		rect(0, 0, width, height);

		//線
		if (isPress(KEY_A))
		{
			if (isTrigger(MOUSE_LBUTTON))deg += 1;
			if (deg >= 360)deg = 360;
			if (isTrigger(MOUSE_RBUTTON))deg -= 1;
			if (deg <= 0)deg = 0;
		}
		else
		{
			if (isTrigger(MOUSE_LBUTTON))deg += 30;
			//if (deg >= 360)deg = 360;
			if (isTrigger(MOUSE_RBUTTON))deg -= 30;
			if (deg <= 0)deg = 0;
		}
		float rad = 3.1415926f / 180 * deg;
		float radius = 300;
		float px = ox + cos(rad) * radius;
		float py = oy - sin(rad) * radius;
		strokeWeight(3);
		stroke(RED);
		line(ox, oy, ox + radius, oy);
		line(ox, oy, px, py);

		//中心角の弧
		stroke(YELLOW);
		arc360(ox, oy, ox + 36, oy, rad);
		
		//扇形の弧
		stroke(GREEN);
		arc360(ox, oy, ox + radius, oy, rad);
		
		//中心点
		strokeWeight(9);
		stroke(RED);
		point(ox, oy);
		
		//テキスト
		py = oy - radius - 120;
		fontRectMode(CORNER);
		fontColor(RED);
		text(ox - 600, py, "半径１の扇形");
		fontColor(YELLOW);
		text(ox - 165, py, "中心角%3d度", deg);
		fontColor(GREEN);
		text(ox + 250, py, "%fラジアン", rad);


		end();
	}
}
