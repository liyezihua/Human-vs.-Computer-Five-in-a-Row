#include <iostream>
#include "Chess.h"
#include<mmsystem.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <windows.h>
#include"AI.h"

using namespace std::chrono;
//ʵ�����ӱ���͸��
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

Chess::Chess(int grideSize, int marginX, int marginY, float chessSize)
{
	this->grideSize = grideSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0;i < grideSize;i++)
	{
		vector<int> row;
		for (int j = 0;j < grideSize;j++)
		{
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::Start_The_Game()
{
	initgraph(908, 936, EW_SHOWCONSOLE);
	loadimage(0, "res/����11.png");
	_getch();//��ͣ������������˳�
}

void Chess::init()
{
	//������Ϸ����
	initgraph(908, 936, EW_SHOWCONSOLE);
	//��ʾ���ǵ�����ͼƬ
	loadimage(0, "res/����.jpg");
	//���ſ�ʼ����
	mciSendString("play res/start.wav",0,0,0);
	//���غ���Ͱ����ͼƬ
	if (!chessLoaded) {
		loadChessImages();
		chessLoaded = true; // ��־��������Ϊ�Ѽ���  
	}
	//��������
	for (int i = 0; i < grideSize; i++)
	{
		for (int j = 0; j < grideSize; j++)
		{
			chessMap[i][j] = 0;
		}
	}
}

void Chess::loadChessImages()
{
		char a;
		cout << "��ѡ�����Ƥ��(A:����  B:ԭ��  C:����С����  D:һ��֮��)" << endl;
		cin >> a;

		switch (a)
		{
		case 'A':
			loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
			loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
			break;
		case 'B'://ԭ��
			ischess = 1;
			loadimage(0, "res/����1.png");
			loadimage(&chessBlackImg, "res/black1.png", chessSize, chessSize, true);
			loadimage(&chessWhiteImg, "res/white1.png", chessSize, chessSize, true);
			break;
		case 'C'://����
			ischess = 2;
			loadimage(0, "res/����3.png");
			loadimage(&chessBlackImg, "res/black3.png", chessSize, chessSize, true);
			loadimage(&chessWhiteImg, "res/white3.png", chessSize, chessSize, true);
			break;
		case 'D'://һ��֮��
			ischess = 3;
			loadimage(0, "res/����4.png");
			loadimage(&chessBlackImg, "res/black4.png", chessSize, chessSize, true);
			loadimage(&chessWhiteImg, "res/white4.png", chessSize, chessSize, true);
			break;
		default:
			cout << "��Ч��ѡ��������ѡ��" << endl;
			break;
		}
	}


bool Chess::clickBoard(int x, int y, ChessPos* pos) {
	int col = (x - margin_x) / chessSize; // ������λ�����ڵ�����  
	int row = (y - margin_y) / chessSize; // ������λ�����ڵ�����  
	int leftTopPosX = margin_x + chessSize * col; // �������Ͻǵ� x ����  
	int leftTopPosY = margin_y + chessSize * row; // �������Ͻǵ� y ����  
	int offset = chessSize * 0.4; // �������ģ����������  
	bool set = false;
	do {
		int len = calculateDistance(x, y, leftTopPosX, leftTopPosY); // ������λ����������Ͻǵľ���  
		if (len < offset) {
			pos->row = row; // ���������浽 pos ��  
			pos->col = col; // ���������浽 pos ��  
			if (chessMap[pos->row][pos->col] == 0) { // �����λ��Ϊ�գ���������  
				set = true; // ���� set Ϊ true  
			}
			break; // ����ѭ��  
		}
		len = calculateDistance(x, y, leftTopPosX + chessSize, leftTopPosY); // ������λ����������Ͻǵľ���  
		if (len < offset) {
			pos->row = row; // ���������浽 pos ��  
			pos->col = col + 1; // ���������浽 pos ��  
			if (chessMap[pos->row][pos->col] == 0) { // �����λ��Ϊ�գ���������  
				set = true; // ���� set Ϊ true  
			}
			break; // ����ѭ��  
		}
		len = calculateDistance(x, y, leftTopPosX, leftTopPosY + chessSize); // ������λ����������½ǵľ���  
		if (len < offset) {
			pos->row = row + 1; // ���������浽 pos ��  
			pos->col = col; // ���������浽 pos ��  
			if (chessMap[pos->row][pos->col] == 0) { // �����λ��Ϊ�գ���������  
				set = true; // ���� set Ϊ true  
			}
			break; // ����ѭ��  
		}
		len = calculateDistance(x, y, leftTopPosX - chessSize, leftTopPosY + chessSize); // ������λ����������½ǵľ���  
		if (len < offset) {
			pos->row = row + 1; // ���������浽 pos ��  
			pos->col = col + 1; // ���������浽 pos ��  
			if (chessMap[pos->row][pos->col] == 0) { // �����λ��Ϊ�գ���������  
				set = true; // ���� set Ϊ true  
			}
			break; // ����ѭ��  
		}
	} while (0);
	return set; // ���� set ��ֵ  
}

int Chess::calculateDistance(int x1, int y1, int x2, int y2) {
	int dx = x1 - x2;
	int dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}
//
void Chess::ChessDown(ChessPos* pos, chess_Kind_t kind)
{
	mciSendString("play res/down7.WAV", 0, 0, 0);

	int x = margin_x + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return grideSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

//�ָ�
int s1 = 0;
int s2 = 0;
bool Chess::checkOver() {
	  
        if (chickWin()) {
            Sleep(1500);
            if (playerFlag == false) {
				// ����Ӯ��
				if (s2 == 2)// Ӯ����
				{
					mciSendString("play res/����.mp3", 0, 0, 0);
					loadimage(0, "res/c13.jpg");
					++s1;
				}
				else
				{
					mciSendString("play res/����.mp3", 0, 0, 0);
					loadimage(0, "res/ʤ��.jpg");
					++s1;
				}
            } else {
				
                // ����Ӯ��
				if (s2 == 2 && s1 == 0) // ��Ӯ����
				{
					mciSendString("play res/ʧ��.mp3", 0, 0, 0);
					loadimage(0, "res/c12.jpg");
					++s2;
					if (surrender())
					{
						return true;
					}
			
				}
				else
				{
					mciSendString("play res/ʧ��.mp3", 0, 0, 0);
					loadimage(0, "res/ʧ��.jpg");
					++s2;
				}
            }

            cout << "���嵱ǰ�ĵ÷���" << s1 << endl;
            cout << "���嵱ǰ�ĵ÷���" << s2 << endl;

            // ������д���ļ�
            saveScores();

            _getch(); // ��ͣ
            return true;
        }
        return false;
    }
  
bool Chess::surrender() {
	  bool isLost = false;
	  char input;
	  while (true) {
		  cout << "�����������֣��Ƿ�����? (Y/N)" << endl;
		  cin >> input;
		  if (input == 'Y') {
			  isLost = true;
			  mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			  loadimage(0, "res/c15.jpg");
			  Sleep(2000); // �ȴ�  
			  // �����˳�����  
			  exit(1);
		  }
		  else if (input == 'N') {
			  loadimage(0, "res/c14.jpg");
			  Sleep(1000);
			  break;
		  }
	  }
	  return isLost;
  }

void Chess::saveScores()
  {
	  // ������д���ļ�
	  ofstream file("D:/scores.txt");
	  if (file.is_open()) {
		  file << s1 << " " << s2;
		  file.close();
	  }
	  else {
		  cout << "�޷����ļ��Ա������" << endl;
	  }
  }

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;//�ڰ׷���������
}

bool Chess::chickWin()
{
	//������ӵ��λ��
	int row = lastPos.row;
	int col = lastPos.col;

	//���ӵ��ˮƽ����
	for (int i = 0;i < 5;i++)
	{
		//���ڵ�i��
		//�������������λ��
		if (col - i >= 0 && col - i + 4 < grideSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] && 
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
		{
			return true;
		}
	}
	//��ֱ����
	for (int i = 0;i < 5;i++)
	{
		if (row - i >= 0 && row - i + 4 < grideSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col] )
		{
			return true;
		}
	}

	//��б����
	for (int i = 0;i < 5;i++)
	{
		if (row + i < grideSize && row + i - 4 >= 0 && col - i >= 0 && col - i + 4 < grideSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
		{
			return true;
		}
	}

	//��б����
	for (int i = 0;i < 5;i++)
	{
		if (row - i >= 0 && row - i + 4 < grideSize && col - i >= 0 && col - i + 4 < grideSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
		{
			return true;
		}
	}
	return false;
}