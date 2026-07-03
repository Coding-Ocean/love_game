#include "..\love\framework.h"

// なす角の弧（180度を超えてもAからBまで正しく描画）
void arc360(float ox, float oy, float ax, float ay, float bx, float by, float radius)
{
	ax -= ox;
	ay -= oy;
	float al = sqrtf(ax * ax + ay * ay);
	if (al < 1e-5f) return;
	ax /= al;
	ay /= al;

	bx -= ox;
	by -= oy;
	float bl = sqrtf(bx * bx + by * by);
	if (bl < 1e-5f) return;
	bx /= bl;
	by /= bl;

	// 1. acosfで基本のなす角（0〜180度）を計算
	float rad = acosf(ax * bx + ay * by);

	// 2. 外積を使って、BがAに対してどちら側にあるかを判定
	float cross = ax * by - ay * bx;

	// 3. 外積が負（または環境により正）の場合、180度を超えた「外側の角」にする
	// 元のコードの回転方向に合わせるため、crossの符号で分岐します
	if (cross > 0) {
		rad = 2.0f * 3.14159265f - rad;
	}

	for (float r = 0; r < rad; r += (0.0174532f/2)) {
		float cr = cosf(r);
		float sr = sinf(r);
		float x = ax * cr - ay * sr;
		float y = ax * sr + ay * cr;
		// 反時計回り
		point(ox + x * radius, oy - y * radius);
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

	int deg = 0;
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
		if (isTrigger(MOUSE_LBUTTON))deg += 30;
		deg %= 360;
		float rad = 3.1415926f / 180 * deg;
		float radius = 300;
		float px = ox + cos(rad) * radius;
		float py = oy - sin(rad) * radius;
		strokeWeight(3);
		stroke(YELLOW);
		line(ox, oy, ox + radius, oy);
		line(ox, oy, px, py);
		arc360(ox, oy, ox + radius, oy, px, py, 30);
		//弧
		//strokeWeight(9);
		stroke(GREEN);
		arc360(ox, oy, ox + radius, oy, px, py, radius);
		//中心点
		strokeWeight(9);
		stroke(YELLOW);
		point(ox, oy);
		
		//テキスト
		fontRectMode(CORNER);
		fontColor(YELLOW);
		text(ox - 250, oy - radius - 80, "%d度", deg);
		fontColor(GREEN);
		text(ox, oy - radius - 80, "%fラジアン", rad);

		end();
	}
}
