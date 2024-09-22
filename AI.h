#pragma once
#include "Chess.h"
#include<vector>
class AI
{
public:
	//AI��ʼ��
	void init(Chess *chess);
	//AI��ʼ����
	void go();
private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	//AI�ж�(���)
	//��ͨ
	void calculateScore();
	//�߼�
	void calculateScore1();

	ChessPos think();

};

