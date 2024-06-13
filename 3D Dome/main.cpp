#include <graphics.h>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include "Util.h"
using namespace std::chrono;


class Game {
public:
	Shape3D shape;
	void gameUpdate();
	void gameInit();
	high_resolution_clock::time_point start;
};


int main() {
	initgraph(Screen::width, Screen::height, EX_SHOWCONSOLE);
	outtextxy(0, 0, _T("Press q to quit."));
	Game game3D;
	game3D.gameInit();
	while (true) {
		game3D.gameUpdate();
		if (_kbhit()) {
			char ch = _getch();
			if ('q' == ch || 27 == ch) {
				break;
			}
		}
	}
	closegraph();
	return 0;
}

void Game::gameInit() {

	// 获取当前时间点
	start = high_resolution_clock::now();

}

void Game::gameUpdate() {
	// 获取当前时间点
	auto end = high_resolution_clock::now();
	// 计算经过的时间（以秒为单位）
	double elapsedTime = duration_cast<duration<double>>(end - start).count();
	cleardevice();
	BeginBatchDraw();
	shape.draw(elapsedTime);
	EndBatchDraw();
}
