#include "ChessGame.h"


ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->chess = chess;
	this->ai = ai;

	
	man->init(chess);
	ai->init(chess);
}

void ChessGame::play()
{
	//���̳�ʼ��
	chess->Start_The_Game();
	chess->init();
	while (1)
	{
		//������������
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
		//ai����
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
