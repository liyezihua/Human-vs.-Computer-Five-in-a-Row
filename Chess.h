#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<graphics.h>//ͼ�ο�
//#include<easyx.h>
#include<stack>
struct ChessPos
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0):row(r), col(c) {}
};

typedef enum {
	CHESS_WHITE = -1,//����
    CHESS_BLACK = 1//����
}chess_Kind_t;

class Chess
{
public:
	//���̹��캯��
	Chess(int grideSize, int marginX, int marginY, float cheesSize);
	//���ֻ���(���)
	void Start_The_Game();
	//���̵ĳ�ʼ��(���)
	void init();
	//�������Ƥ��(���)
	void loadChessImages();

	//�ж���ָ�����꣨x��y��λ���Ƿ�����Ч���,�����Ч����Ч��������б�����Pos��(���)
	bool clickBoard(int x, int y,ChessPos *pos);

	//��������֮��ľ���(���)
	int calculateDistance(int x1, int y1, int x2, int y2);

	//������ָ����λ������
	void ChessDown(ChessPos *pos,chess_Kind_t Kind);
	//��ȡ���̵Ĵ�С
	int getGradeSize();
	//��ȡָ��λ���ǰ��廹�Ǻ�����߿հ�
	int getChessData(ChessPos* pos);
	int getChessData(int row,int col);
	//�������Ƿ����(���)
	bool checkOver();
	//���书��(���)
	bool surrender();
	// ������д���ļ��÷���һֱ����(���)
	void saveScores();

private:
	IMAGE chessBlackImg;//����
	IMAGE chessWhiteImg;//����

	int grideSize;//���̴�С
	int margin_x;//���̵����߾�
	int margin_y;//���̵Ķ����߾�
	float chessSize = 0.0;//���Ӵ�С
	//�洢��ǰ��Ϸ��ֵ����ӷֲ����� 0 �հף�-1���ӣ�1����
	vector<vector<int>> chessMap;

	stack<ChessPos> history; // ��ʷ��¼��ջ(���)


	//���ڸ�˭����
	bool playerFlag;//true���� false ����

	void updateGameMap(ChessPos* pos);
	
	//����Ƿ�ʤ����ʤ���ѷ�true����false
	bool chickWin();

	ChessPos lastPos;//��������ӵ�λ��

	bool chessLoaded; // ��־��������ʾ�Ƿ��Ѿ����ع�����ͼƬ(���)
	int ischess;

};
