#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAX_SNAKE 100
enum DIR
{
	UP,
    DOWN,
    LEFT,
    RIGHT,
};
struct Snake_tig
{
	int num;
	int  dir;//方向
	int score;//分数
	int size;
	POINT coor[MAX_SNAKE];
}snake;
struct Food_tlg
{
	POINT fd;
	int flag;
	DWORD color;
}food;
void GameInit()
{
	srand(unsigned int(time(NULL)));
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = 0 + snake.size;;
	snake.coor[1].y = 0;
	snake.coor[0].x = 0 + 2 * snake.size;
	snake.coor[0].y = 0;
	food.fd.x = rand() % 639/10*10;
	food.fd.y = rand() % 479/10*10;
	food.flag = 1;
	food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
	mciSendString(L"open 卡路里.mp3 alias a", 0, 0, 0);
	//mciSendString(L"open 最美的期待.mp3 alias a", 0, 0, 0);
	mciSendString(L"play a repeat", 0, 0, 0);
	//mciSendString("open zmdqd.mp3",NULL,0,NULL);
	//PlaySound("C:\\Users\\61676\\Desktop\\snake\\Debug\\最美的期待.mp3", NULL, SND_ASYNC);
	//system("pause");
}
void GameDraw()
{
	setbkcolor(RGB(122,142,141));
	cleardevice();
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		solidrectangle(snake.coor[i].x,snake.coor[i].y, snake.coor[i].x+snake.size, snake.coor[i].y + snake.size);
		//printf("%d%d", snake.coor[i].x, snake.coor[i].y);
		if (food.flag == 1)
		{
			setlinecolor(YELLOW);
			setfillcolor(food.color);
			solidellipse(food.fd.x, food.fd.y, food.fd.x + 10, food.fd.y + 10);
		}
	}
	char temp[20];
	sprintf(temp, "%d", snake.score);
	setbkmode(TRANSPARENT);
	outtextxy(30, 20, *temp);
}
void SnakeMove()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= 10;
		if (snake.coor[0].y - 10 < 0)
		{
			snake.coor[0].y = WIN_HEIGHT;
		}
		break;
	case DOWN:
		snake.coor[0].y += 10;
		if (snake.coor[0].y + 10 > WIN_HEIGHT)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= 10;
		if (snake.coor[0].x - 10 < 0)
		{
			snake.coor[0].x = WIN_WIDTH;
		}
		break;
	case RIGHT:
		snake.coor[0].x += 10;
		if (snake.coor[0].x + 10 > WIN_WIDTH)
		{
			snake.coor[0].x =0;
		}
		break;
	default:
		break;
	}
	//snake.coor[0].x += 10;
}
void KeyControl()
{
	if (GetAsyncKeyState(VK_UP))
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		snake.dir = RIGHT;
	}
}
void EatFood()
{
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y)
	{
		snake.num++;
		snake.score += 10;
		food.flag = 0;
	}
	if (food.flag == 0)
	{
		food.fd.x = (rand() % WIN_WIDTH) / 10 * 10;
		food.fd.y = (rand() % WIN_HEIGHT) / 10 * 10;
		food.flag = 1;
		food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
	}
}
void DontEatSelf()
{
	char arr[20] = { "GAME OVER!" };
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			outtextxy(200, 200, *arr);
			_getch();
			exit(666);
		}
	}
}
//void Pause()
//{
//	char ch = _getch();
//	if (_getch() == 32)
//	{
//		while (1)
//		{
//			if()
//		}
//	}
//}
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw();
		if (t2 - t1 > 100)
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
	while (1)
	{
		if (t2 - t1 > 100)
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
	  // SnakeMove();

		GameDraw();
		EatFood();
		DontEatSelf();
		FlushBatchDraw();
		KeyControl();
		//Pause()
	}
	getchar();
	closegraph();
	return 0;
}