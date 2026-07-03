#include "..\love\framework.h"

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

	float ofstRad = 0.0f;
	float radInc = 1.57f / 2.0f;

	hideCursor();
	while (!quit())
	{
		begin();

		/*動かす---------------------------------*/
		if (isPress(MOUSE_LBUTTON)) {
			ox += mouseVx;
			oy -= mouseVy;
		}
		unit += mouseWheel * 5;

		/*描画する------------------------------*/
		//背景
		noStroke();
		fill(40,40,40);
		rectMode(CORNER);
		rect(0, 0, width, height);
		//XY軸
		strokeWeight(1);
		stroke(255,255,255);
		mathAxis(ox, oy, unit);
		//sin,cosカーブ
		ofstRad += radInc * fixed_delta;
		strokeWeight(10);
		for(int deg = -180; deg<=180; deg+=3){
			float rad = 3.1415926f / 180 * deg;
			stroke(GREEN);
			mathPoint(rad, cos(rad));
			stroke(RED);
			mathPoint(rad, sin(rad + ofstRad));
		}
		//sin,cosで円周に矩形
		strokeWeight(3);
		stroke(YELLOW);
		rectMode(CENTER);
		noFill();
		for (int deg = 0; deg < 360; deg += 30) {
			float rad = 3.1415926f / 180 * deg;
			float px = cos(rad + ofstRad);
			float py = sin(rad + ofstRad);
			mathRect(px, py, 0.1f, 0.1f,rad+ofstRad);
		}

		//矢印
		strokeWeight(3);
		stroke(GRAY);
		mathArrow(0, 0, mathMouseX, mathMouseY, 0.05f,20.f);
		mathArc(1, 0, mathMouseX, mathMouseY, 0.2f);
		//矢印の先にテキスト
		fontRectMode(CENTER);
		fontSize(20);
		fontColor(WHITE);
		float2 v(mathMouseX, mathMouseY);
		float2 ofst = v.normalize()*0.05f;
		mathText("あ",mathMouseX+ofst.x, mathMouseY+ofst.y);
		
		//テキスト
		fontRectMode(CORNER);
		fontColor(BLUE);
		fontSize(30);
		winInfo();

		end();
	}
	showCursor();
}
