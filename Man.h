#pragma once
#include"Chess.h"
class Man
{
public:
	//���ֳ�ʼ��
	void init(Chess* chess);
	void go();

private:
	Chess *chess;
};

