#include "Man.h"
#include<stdio.h>
#include<easyx.h>
#include"Chess.h"
#include"ChessGame.h"
#include<iostream>
using namespace std;


void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	//ExMessage msg;
	//MOUSEMSG msg;
	ChessPos pos;
		while (true)
		{
			// ��ȡ�������Ϣ
			ExMessage msg = getmessage();
			//msg = getmessage();
			//ͨ��chess�����������ж������Ƿ���Ч �Լ����ӹ���
			if (msg.message == WM_LBUTTONDOWN && chess->clickBoard(msg.x,msg.y,&pos) ) {
				break;
			}
		}
		cout <<"����"<< pos.row << "," << pos.col << endl;
	//����
	chess->ChessDown(&pos, CHESS_BLACK);

}

