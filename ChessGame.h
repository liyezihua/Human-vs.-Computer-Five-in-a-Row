#pragma once
#include"AI.h"
#include"Chess.h"
#include"Man.h"
class ChessGame
{
public:

	int dfdfdf;

	ChessGame(Man* man, AI* ai, Chess* chess);
	//��ʼ�Ծ�
	void play();

	//����վݳ�Ա
private:
	Man* man;
	AI* ai;
	Chess* chess;
};


 