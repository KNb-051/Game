#include<math.h>
#include<graphics.h>
#include<synchapi.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

#pragma comment(lib,"winmm.lib")//音乐
#define bgcolor RGB(238, 212, 176)
#define bgcolor2 RGB(51,73,198)


int bgmstatus = 1;//bgm 开关
int flag = 0;//当前棋子颜色
int board[20][20] = { 0 };//棋盘
int whitewin = 0;//白棋获胜次数
int blackwin = 0;
int defense = 0;//防守难度
typedef struct
{	
	int score;//该点分数
	int x;//该点x坐标
	int y;//该点y坐标
	
}Stua;//棋盘每点估值

Stua stuation[400];//400个点

typedef struct
{
	int a[11];//棋型需要11个点表示
}chessform;//棋型结构体

void initBoard();//初始化棋盘
void black(int x, int y);//下黑棋
void white(int x, int y);
void music1();//落子声
void music2();//提示声
void music3();//点击声
void music4();//游标声

void boardSet(int mode);//设置棋盘 mode游戏模式
int option();//选项菜单
int judge(int a, int b);//判断获胜
void playGame();//双人游戏
void playAIgame();//人机对战
void initGame();//初始化游戏及进入菜单
chessform getform(int a, int b, int dire);//获取当前位置棋型
void roundInitStu(Stua stuation);//初始化每点估值
void reverseform(chessform *form);//reverse 棋型

int lian5(chessform tempform, int player);//连5
int huo3(chessform tempform, int player);//活三
int mian3(chessform tempform, int player);//眠三
int huo2(chessform tempform, int player);//活二
int si3(chessform tempform, int player);//死三
int mian2(chessform tempform, int player);//眠2
int huo1(chessform tempform, int player);//活1
int mian1(chessform tempform, int player);//眠1

int evaluate(Stua point);//估值函数
void bgm(int mode);//bgm设置

int main()
{	
	initGame();
	return 0;
}

int lian5(chessform tempform,int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1 )? 2 : 1;

	if (tempform.a[1] == player&&tempform.a[2] == player&& tempform.a[3] == player&& tempform.a[4] == player)
		return 1;
	if (tempform.a[2] == player&& tempform.a[3] == player&& tempform.a[4] == player&&tempform.a[6] == player)
		return 1;
	if (tempform.a[3] == player&& tempform.a[4] == player&& tempform.a[6] == player&&tempform.a[7] == player)
		return 1;
	return 0;

}
int huo3(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (tempform.a[1] == 0 && tempform.a[2] == player&& tempform.a[3] == player&& tempform.a[4] == player&&tempform.a[6] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == player&&tempform.a[6] == player&&tempform.a[7] == 0)
		return 1;
	
	return 0;

}
int mian3(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (((tempform.a[1] == opposite) || (tempform.a[1] == -1)) && tempform.a[2] == player&& tempform.a[3] == player&& tempform.a[4] == player&&tempform.a[6] == 0)
		return 1;
	if (((tempform.a[0] == opposite) || (tempform.a[0] == -1)) && tempform.a[1] == player && tempform.a[2] == player&& tempform.a[3] == 0 && tempform.a[4] == player)
		return 1;

	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player&& tempform.a[4] == player&& tempform.a[6] == player&&tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == player&& tempform.a[6] == player && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (((tempform.a[0] == opposite) || (tempform.a[0] == -1)) && tempform.a[1] == player&& tempform.a[2] == 0 && tempform.a[3] == player&&tempform.a[4] == player)
		return 1;
	return 0;

}
int huo2(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == player && tempform.a[6] == 0&&tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == 0&& tempform.a[4] == player&& tempform.a[6] == player && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player&&tempform.a[7] == 0)
		return 1;
	return 0;
}
int si3(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (((tempform.a[1] == opposite) || (tempform.a[1] == -1)) && tempform.a[2] == player&& tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player)
		return 1;
	if (((tempform.a[0] == opposite) || (tempform.a[0] == -1)) && tempform.a[1] == player && tempform.a[2] == player&& tempform.a[3] == player && tempform.a[4] == 0)
		return 1;

	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player&&tempform.a[7] == player)
		return 1;
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player&& tempform.a[4] == player&& tempform.a[6] == 0 && tempform.a[7] == player)
		return 1;
	if (tempform.a[2] == player && tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	
	
	return 0;

}
int mian2(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player&& tempform.a[4] == player && tempform.a[6] == 0 && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == player&& tempform.a[6] == 0 && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == player && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == player&&tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player&& tempform.a[4] == 0 && tempform.a[6] == player&&tempform.a[7] == 0)
		return 1;

	return 0;

}
int huo1(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (tempform.a[1] == 0 && tempform.a[2] == 0&& tempform.a[3] == 0&& tempform.a[4] == player && tempform.a[6] == 0)
		return 1;
	if (tempform.a[1] == 0 && tempform.a[2] == 0 && tempform.a[3] == player && tempform.a[4] == 0 && tempform.a[6] == 0)
		return 1;

	if (tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == 0 && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == 0 && tempform.a[6] == player && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player && tempform.a[4] == 0 && tempform.a[6] == 0 && tempform.a[7] == 0)
		return 1;
	return 0;
}
int mian1(chessform tempform, int player)//player为1表示 当前是黑棋判断 为2表示当前是白棋判断
{
	int opposite = (player == 1) ? 2 : 1;

	if (tempform.a[1] == 0 && tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == player && ((tempform.a[6] == opposite) || (tempform.a[6] == -1)))
		return 1;
	if (((tempform.a[1] == opposite) || (tempform.a[1] == -1)) && tempform.a[2] == 0 && tempform.a[3] == player && tempform.a[4] == 0 && tempform.a[6] == 0)
		return 1;
	if (((tempform.a[1] == opposite) || (tempform.a[1] == -1)) && tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == 0)
		return 1;
	if (tempform.a[1] == 0 && tempform.a[2] == 0 && tempform.a[3] == player && tempform.a[4] == 0 && ((tempform.a[6] == opposite) || (tempform.a[6] == -1)))
		return 1;

	if (tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == 0 && tempform.a[6] == player && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == 0 && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == 0 && tempform.a[4] == player && tempform.a[6] == 0 && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;

	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == player && tempform.a[4] == 0 && tempform.a[6] == 0 && tempform.a[7] == 0)
		return 1;
	if (tempform.a[2] == 0 && tempform.a[3] == player && tempform.a[4] == 0 && tempform.a[6] == 0 && ((tempform.a[7] == opposite) || (tempform.a[7] == -1)))
		return 1;
	if (((tempform.a[2] == opposite) || (tempform.a[2] == -1)) && tempform.a[3] == 0 && tempform.a[4] == 0 && tempform.a[6] == player && tempform.a[7] == 0)
		return 1;
	return 0;
}

void reverseform(chessform *form)
{
	int i = 0, j = 10;
	while (i < j)
	{
		int temp = (*form).a[i];
		(*form).a[i] = (*form).a[j];
		(*form).a[j] = temp;
		i++;
		j--;
	}
}
void roundInitStu(Stua stuation)
{
	if (board[stuation.x][stuation.y] != 0)
		stuation.score = -1;

}
chessform getform(int a, int b, int dire)//dire方向  横1 竖2 \3 /4 
{
	chessform tempform;
	switch (dire)
	{
	case 1:
	{
			  for (int i = a - 5, j = 0; i <= a + 5; i++, j++)
			  {
				  if (i<0 || i>19)
					  tempform.a[j] = -1;
				  else
					  tempform.a[j] = board[i][b];
			  }
			  return tempform;
	}
	case 2:
	{
			  for (int i = b - 5, j = 0; i <= b + 5; i++, j++)
			  {
				  if (i<0 || i>19)
					  tempform.a[j] = -1;
				  else
					  tempform.a[j] = board[a][i];
			  }
			  return tempform;
	}
	case 3:
	{
			  for (int i = a - 5, k = b - 5, j = 0; i <= a + 5; i++, j++, k++)
			  {
				  if (i<0 || i>19 || k<0 || k>19)
					  tempform.a[j] = -1;
				  else
					  tempform.a[j] = board[i][k];
			  }
			  return tempform;
	}
	case 4:
	{
			  for (int i = a - 5, k = b + 5, j = 0; i <= a + 5; i++, j++, k--)
			  {
				  if (i<0 || i>19 || k<0 || k>19)
					  tempform.a[j] = -1;
				  else
					  tempform.a[j] = board[i][k];
			  }
			  return tempform;
	}
	}

}

void initBoard()
{
	flag = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < 400; i++)
	{
		stuation[i].y = i / 20;
		stuation[i].x = i - 20 * (stuation[i].y);
		stuation[i].score = 0;
	}
}

void music1()
{
	PlaySound("drop.wav", NULL, SND_FILENAME | SND_ASYNC);

}
void music2()
{
	
	PlaySound("select.wav", NULL, SND_FILENAME | SND_ASYNC);

}
void music3()
{

	PlaySound("click.wav", NULL, SND_FILENAME | SND_ASYNC);

}

void music4()
{
	PlaySound("move.wav", NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void bgm(int mode)
{
	mciSendString("open bg.mp3 alias bgm", NULL, 0, NULL);
	if (mode)
	{
		
		mciSendString("play bgm repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("play bgm repeat", NULL, 0, NULL);
		//mciSendString("setaudio bgm volume to 0", NULL, 0, NULL);
		mciSendString("stop bgm", NULL, 0, NULL);
		mciSendString("close bgm", NULL, 0, NULL);
	}

}

void boardSet(int mode)
{
	/*设置游戏界面时需要的操作↓*/
	cleardevice();
	bgm(1);
	initBoard();
	char bw[5];
	char ww[5];
	sprintf_s(bw, "%d", blackwin);
	sprintf_s(ww, "%d", whitewin);
	
	loadimage(NULL, "bg.jpg");
	setlinecolor(BLACK);
	for (int i = 25; i < 500; i += 25)
	{
		line(i, 0, i, 500);
		line(0, i, 475, i);
	}
	line(477, 0, 477, 500);
	setlinecolor(BROWN);
	setfillcolor(bgcolor);

	settextcolor(BLACK);
	fillrectangle(485, 95, 590, 135);
	outtextxy(490, 100, "玩家1：黑");
	outtextxy(490, 115, "获胜局数：");
	outtextxy(565, 115, bw);

	fillrectangle(485, 195, 590, 235);
	settextcolor(LIGHTGRAY);
	if (mode==1)
		outtextxy(490, 200, "玩家2：白");
	else
		outtextxy(490, 200, "电脑：白");
	outtextxy(490, 215, "获胜局数：");
	outtextxy(570, 215, ww);

	settextcolor(BLACK);
	settextstyle(15, 0, "楷体");

	fillrectangle(500, 450, 580, 490);
	outtextxy(510, 460, "主菜单");//主菜单按钮
	/*设置游戏界面时需要的操作↑*/
}
int option()
{	
	cleardevice();
	
	MOUSEMSG m;
	
	
	settextcolor(WHITE);
	setbkcolor(BLACK);
	settextstyle(15, 0, "楷体");
	setfillcolor(BLACK);
	
	while (1)
	{
		m = GetMouseMsg();
		FlushMouseMsgBuffer();
		if (defense == 0)
		{
			loadimage(NULL, "attackI.jpg");
			fillrectangle(500, 450, 580, 490);
			outtextxy(510, 460, "主菜单");//主菜单按钮	
			
		}
		else
		{
			loadimage(NULL, "defenseI.jpg");
			fillrectangle(500, 450, 580, 490);
			outtextxy(510, 460, "主菜单");//主菜单按钮	
			
		}
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 500 && m.y > 450)
			{
				music3();
				return 1;
			}
			if (m.x > 173 && m.y > 218 && m.x < 422 && m.y < 291)
			{
				music3();
				defense = defense == 0 ? 400 : 0;
				
			}
		}
		
		
	}
}
void initGame()
{
	initgraph(600, 500);
	menu:
	cleardevice();
	whitewin = 0;
	blackwin = 0;
	setbkcolor(bgcolor);//与背景图片颜色一致
	
	IMAGE bg, game1I, game2I, settingI, helpI, quitI, bgI;
	loadimage(&bg, "bg.jpg", 600, 500);
	loadimage(&bgI, "bgI.jpg", 600, 500);
	loadimage(&game1I, "game1I.jpg", 600, 500);
	loadimage(&game2I, "game2I.jpg", 600, 500);
	loadimage(&settingI, "settingI.jpg", 600, 500);
	loadimage(&helpI, "helpI.jpg", 600, 500);
	loadimage(&quitI, "quitI.jpg", 600, 500);
	
	putimage(0, 0, &bgI);
	
	MOUSEMSG m;		  

	while (1)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		//清除上一下鼠标缓存
		FlushMouseMsgBuffer();

		putimage(0, 0, &bgI);
		

		if (m.uMsg == WM_MOUSEMOVE)
		{
			
			if (m.x >= 295 && m.y >= 250 && m.x <= 500 && m.y <= 300)  //(295, 250, 500, 300)   双人游戏
			{
				music4();

				putimage(0, 0, &game1I);
			}
			if (m.x >= 170 && m.y >= 380 && m.x <= 390 && m.y <= 440)  // (170, 380, 390, 440)  退出游戏
			{
				music4();
				putimage(0, 0, &quitI);
			}
			if (m.x >= 295 && m.y >= 315 && m.x <= 500 && m.y <= 365) //  (295, 315, 500, 365)  游戏说明 
			{
				music4();
				putimage(0, 0, &helpI);
			}
			if (m.x >= 50 && m.y >= 250 && m.x <= 270 && m.y <= 300) //  (50,250,270,300) 人机挑战
			{
				music4();
				putimage(0, 0, &game2I);
			}
			if (m.x >= 50 && m.y >= 315 && m.x <= 270 && m.y <= 370) //  (50,315,270,370) 设置
			{
				music4();
				putimage(0, 0, &settingI);
			}

		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			
			if (m.x >= 295 && m.y >= 250 && m.x <= 500 && m.y <= 300)   //(295, 250, 500, 300)   双人游戏
			{
				music3();
				playGame();
				goto menu;
			}
			if (m.x >= 170 && m.y >= 380 && m.x <= 390 && m.y <= 440)  // (170, 380, 390, 440)  退出游戏
			{
				music3();
				int msg;
				msg = MessageBox(NULL, TEXT("确定退出游戏？"), TEXT(" "), MB_YESNO | MB_ICONQUESTION);
				if (msg == 7)
					goto menu;
				closegraph();
				exit(0);
			}
			if (m.x >= 295 && m.y >= 315 && m.x <= 500 && m.y <= 365) //  (295, 315, 500, 365)  游戏说明 
			{	
				music3();
				cleardevice();
				loadimage(NULL, "help.jpg");
				setbkcolor(bgcolor2);
				setlinecolor(bgcolor2);
				setfillcolor(bgcolor2);
				settextcolor(WHITE);
				settextstyle(15, 0, "楷体");
				fillrectangle(520, 0, 600, 40);
				outtextxy(530, 10, "主菜单");//主菜单按钮

				while (1)
				{
					m = GetMouseMsg();
					FlushMouseMsgBuffer();

					if (m.uMsg == WM_LBUTTONDOWN&&m.x > 520 && m.y < 40)
					{
						music3();
						goto menu;
					}
				}
				
				
			}
			if (m.x >= 50 && m.y >= 315 && m.x <= 270 && m.y <= 370)  //  (50,315,270,370) 设置
			{
				music3();
				if (option())
				{
					goto menu;
				}
				

				
			}
			if (m.x >= 50 && m.y >= 250 && m.x <= 270 && m.y <= 300) //  (50,250,270,300) 人机挑战
			{
				music3();
				
				playAIgame();
				
				goto menu;
			}
		}
	}//循环结束



}

int judge(int a, int b)
{
	int i, j;
	int t = 2 - flag % 2;
	for (i = a - 4, j = b; i <= a; i++)
	{
		if (i >= 0 && i<16 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
			return 1;
	}
	for (i = a, j = b - 4; j <= b; j++)
	{
		if (j >= 0 && j<16 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
			return 1;
	}
	for (i = a - 4, j = b - 4; j <= b; i++, j++)
	{
		if (i >= 0 && i<16 && j >= 0 && j<16 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
			return 1;
	}
	for (i = a - 4, j = b + 4; i <= a; i++, j--)
	{
		if (j >= 0 && j<16 && t == board[i][j] && t == board[i + 1][j - 1] && t == board[i + 2][j - 2] && t == board[i + 3][j - 3] && t == board[i + 4][j - 4])
			return 1;
	}
	return 0;


}
void black(int x, int y)
{	
	setfillcolor(BLACK);
	solidcircle(x, y, 10);
	music1();
	
}
void white(int x, int y)
{	
	setfillcolor(WHITE);
	solidcircle(x, y, 10);
	music1();
}

void playGame()
{
	nextgame:
	IMAGE bgmonI, bgmoffI;
	loadimage(&bgmonI, "bgmonI.jpg", 40, 52);
	loadimage(&bgmoffI, "bgmoffI.jpg", 40, 52);
	boardSet(1);
	putimage(555, 0, &bgmonI);
	MOUSEMSG m;
	int x=0, y=0, a=0, b=0;

	while (1)
	{
		
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 555 && m.y > 0 && m.x < 600 && m.y < 43) //(555,0,600,43)  开关音乐
			{
				music2();
				bgmstatus = bgmstatus == 0 ? 1 : 0;
				bgm(bgmstatus);
				if (bgmstatus)
					putimage(555, 0, &bgmonI);
				else
					putimage(555, 0, &bgmoffI);
			}
			for (int i = 0; i<20; i++)
			{
				for (int j = 0; j<20; j++)
				{
					if (abs(m.x - i * 25)<12 && abs(m.y - j * 25)<12)
					{
						x = i * 25;
						y = j * 25;
						a = i;
						b = j;

					}

				}

			}
			if (m.x > 500 && m.y > 450)
			{
				music3();
				int nextround = MessageBox(NULL, TEXT("确定返回主菜单？"), TEXT(" "), MB_YESNO | MB_ICONQUESTION);
				if (nextround!=7)
				{
					bgm(0);
					return;
				}
			}
			if (board[a][b] != 0)
				continue;
			
			
			if (flag % 2 == 0)
			{
				black(x, y);

				board[a][b] = 1;
			}
			else
			{
				white(x, y);
				board[a][b] = 2;
			}


			flag++;
		}
		if (judge(a, b))
		{
			music2();
			if (flag % 2 == 0)
			{
				MessageBox(NULL, "白棋胜利", "游戏结束", MB_OK);
				whitewin++;
			}
			else
			{
				MessageBox(NULL, "黑棋胜利", "游戏结束", MB_OK);
				blackwin++;
			}
			music2();
			int nextround = MessageBox(NULL, TEXT("是否再来一局？"), TEXT("游戏结束"), MB_YESNO | MB_ICONQUESTION);
			if (nextround == 6)
				goto nextgame;
			else
				return ;

		}

	}

}
void playAIgame()
{
nextgame:
	IMAGE bgmonI, bgmoffI;
	loadimage(&bgmonI, "bgmonI.jpg", 40, 52);
	loadimage(&bgmoffI, "bgmoffI.jpg", 40, 52);
	boardSet(0);
	putimage(555, 0, &bgmonI);
	MOUSEMSG m;
	int x = 0, y = 0, a = 0, b = 0;

	while (1)
	{	
		for (int i = 0; i < 400; i++)
			roundInitStu(stuation[i]);

		
		m = GetMouseMsg();
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN:
			{	
				if (m.x > 555 && m.y > 0 && m.x < 600 && m.y < 43) //(555,0,600,43)  开关音乐
				{
					music2();
					bgmstatus = bgmstatus == 0 ? 1 : 0;
					bgm(bgmstatus);
					if (bgmstatus)
						putimage(555, 0, &bgmonI);
					else
						putimage(555, 0, &bgmoffI);
				}
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						if (abs(m.x - i * 25)<12 && abs(m.y - j * 25)<12)
						{
							x = i * 25;
							y = j * 25;
							a = i;
							b = j;
						}
					}
				}
				if (m.x > 500 && m.y > 450)
				{
					music3();
					int nextround = MessageBox(NULL, TEXT("确定返回主菜单？"), TEXT(" "), MB_YESNO | MB_ICONQUESTION);
					if (nextround != 7)
					{
						bgm(0);
						return;
					}
						
				}
				if (board[a][b] != 0)
					break;

				black(x, y);

				board[a][b] = 1;
				flag++;
				//判断是否获胜
				if (judge(a, b))
				{
					music2();
					if (flag % 2 == 0)
					{
						MessageBox(NULL, "白棋胜利", "游戏结束", MB_OK);
						whitewin++;
					}
					else
					{
						MessageBox(NULL, "黑棋胜利", "游戏结束", MB_OK);
						blackwin++;
					}
					music2();
					int nextround = MessageBox(NULL, TEXT("是否再来一局？"), TEXT("游戏结束"), MB_YESNO | MB_ICONQUESTION);
					if (nextround == 6)
						goto nextgame;
					else
						return;

				}
			}
			case 1:
			{
					  Stua maxpoint;
					  maxpoint = stuation[0];
					  for (int i = 0; i < 400; i++)
					  {
						  stuation[i].score =  evaluate(stuation[i]);
						  if (maxpoint.score < stuation[i].score)
							  maxpoint = stuation[i];
					  }

					  a = maxpoint.x;
					  b = maxpoint.y;
					  board[a][b] = 2;
					  white(25*a, 25*b);
					  flag++;
					  
					  //判断是否获胜
					  if (judge(a, b))
					  {
						  music2();
						  if (flag % 2 == 0)
						  {
							  MessageBox(NULL, "白棋胜利", "游戏结束", MB_OK);
							  whitewin++;
						  }
						  else
						  {
							  MessageBox(NULL, "黑棋胜利", "游戏结束", MB_OK);
							  blackwin++;
						  }
						  music2();
						  int nextround = MessageBox(NULL, TEXT("是否再来一局？"), TEXT("游戏结束"), MB_YESNO | MB_ICONQUESTION);
						  if (nextround == 6)
							  goto nextgame;
						  else
							  return;

					  }
			}

		}
		
	}

}
int evaluate(Stua point)
{
	int score = 0;
	if (board[point.x][point.y] != 0)
		return -1;
	chessform line = getform(point.x, point.y, 1);
	chessform column = getform(point.x, point.y, 2);
	chessform backslash = getform(point.x, point.y, 3);
	chessform slash = getform(point.x, point.y, 4);
	//白连5
	if (lian5(line, 2) || lian5(column, 2) || lian5(backslash, 2) || lian5(slash, 2))
		score += 1000000000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (lian5(line, 2) || lian5(column, 2) || lian5(backslash, 2) || lian5(slash, 2))
		score += 1000000000;
	//黑连5
	if (lian5(line, 1) || lian5(column, 1) || lian5(backslash, 1) || lian5(slash, 1))
		score += 40000000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);             
	if (lian5(line, 1) || lian5(column, 1) || lian5(backslash, 1) || lian5(slash, 1))
		score += 40000000;
	//白活3
	if (huo3(line, 2) || huo3(column, 2) || huo3(backslash, 2) || huo3(slash, 2))
		score += 1000000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo3(line, 2) || huo3(column, 2) || huo3(backslash, 2) || huo3(slash, 2))
		score += 1000000;
	//黑活3
	if (huo3(line, 1) || huo3(column, 1) || huo3(backslash, 1) || huo3(slash, 1))
		score += 400000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo3(line, 1) || huo3(column, 1) || huo3(backslash, 1) || huo3(slash, 1))
		score += 400000;
	//白眠3
	if (mian3(line, 2) || mian3(column, 2) || mian3(backslash, 2) || mian3(slash, 2))
		score += 100000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (mian3(line, 2) || mian3(column, 2) || mian3(backslash, 2) || mian3(slash, 2))
		score += 100000;
	//黑眠3
	
	if (mian3(line, 1) || mian3(column,1) || mian3(backslash, 1) || mian3(slash, 1))
		//score += 40000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (mian3(line, 1) || mian3(column,1) || mian3(backslash,1) || mian3(slash, 1))
		//score += 40000;
		

	//白活2
	if (huo2(line, 2) || huo2(column, 2) || huo2(backslash, 2) || huo2(slash, 2))
		score += 10000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo2(line, 2) || huo2(column, 2) || huo2(backslash, 2) || huo2(slash, 2))
		score += 10000;
	//黑活2
	if (huo2(line,1) || huo2(column,1) || huo2(backslash, 1) || huo2(slash, 1))
		score += 4000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo2(line, 1) || huo2(column, 1) || huo2(backslash, 1) || huo2(slash, 1))
		score += 4000;
	//白死3
	if (si3(line, 2) || si3(column, 2) || si3(backslash, 2) || si3(slash, 2))
		score += 1000;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (si3(line, 2) || si3(column, 2) || si3(backslash, 2) || si3(slash, 2))
		score += 1000;
	//黑死3
	if (si3(line, 1) || si3(column, 1) || si3(backslash, 1) || si3(slash, 1))
		score += defense;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (si3(line, 1) || si3(column, 1) || si3(backslash, 1) || si3(slash, 1))
		score += defense;
	//白活1
	if (huo1(line, 2) || huo1(column, 2) || huo1(backslash, 2) || huo1(slash, 2))
		score += 100;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo1(line, 2) || huo1(column, 2) || huo1(backslash, 2) || huo1(slash, 2))
		score += 100;
	//黑活1
	if (huo1(line, 1) || huo1(column, 1) || huo1(backslash, 1) || huo1(slash, 1))
		score += 40;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo1(line, 1) || huo1(column, 1) || huo1(backslash, 1) || huo1(slash, 1))
		score += 40;
	//白眠1
	if (huo1(line, 2) || huo1(column, 2) || huo1(backslash, 2) || huo1(slash, 2))
		score += 10;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo1(line, 2) || huo1(column, 2) || huo1(backslash, 2) || huo1(slash, 2))
		score += 10;
	//黑眠1
	if (huo1(line, 1) || huo1(column, 1) || huo1(backslash, 1) || huo1(slash, 1))
		score += 4;
	reverseform(&line);
	reverseform(&column);
	reverseform(&backslash);
	reverseform(&slash);
	if (huo1(line, 1) || huo1(column, 1) || huo1(backslash, 1) || huo1(slash, 1))
		score += 4;
	
	
	

	return score;
}


