#include "AI.h"


void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0;i < size;i++)
	{
		vector<int> row;
		for (int j = 0;j < size;j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	
	Sleep(1000);//��װ˼��
	
	chess->ChessDown(&pos, CHESS_WHITE);
	cout <<"����"<< pos.row << "," << pos.col << endl;
}

//��ͨ�Ѷ�
void AI::calculateScore() {
    int blackNum = 0; // ���ַ������壩���ٸ�����������
    int whiteNum = 0; // AI�������壩�����ж��ٸ�����������
    int emptyNum = 0; // �÷����Ͽհ�λ�ĸ���
    // ����������������
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap[i].size(); j++) {
            scoreMap[i][j] = 0;
        }
    }
    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // ��ÿ������м���
            if (chess->getChessData(row, col)) continue;

            // �����������
            for (int y = -1; y <= 0; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (y == 0 && x == 0) continue;
                    if (y == 0 && x != 1) continue;
                    blackNum = 0;
                    emptyNum = 0;
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 1) {
                            blackNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 1) {
                            blackNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // ����������͵÷�
                    if (blackNum == 1) {
                        scoreMap[row][col] += 10;
                    }
                    else if (blackNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 30;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 40;
                        }
                    }
                    else if (blackNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 60;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 5000;
                        }
                    }
                    else if (blackNum == 4) {
                        scoreMap[row][col] += 20000;
                    }
                    else if (blackNum >= 5) {
                        // �ж����ĺ�����
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 100000;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 100000;
                        }
                    }
                }
            }

            // б����Ŀ��ֲ��� 
            if (row >= 2 && col >= 2 && row < size - 2 && col < size - 2) {
                if (chess->getChessData(row - 2, col - 2) == 0 &&
                    chess->getChessData(row - 1, col - 1) == 0 &&
                    chess->getChessData(row + 1, col + 1) == 0 &&
                    chess->getChessData(row + 2, col + 2) == 0) {
                    scoreMap[row][col] += 500;
                }
            }

            // ������Ŀ��ֲ��� 
            if (row >= 2 && col >= 1 && row < size - 2 && col < size - 1) {
                if (chess->getChessData(row - 2, col - 1) == 0 &&
                    chess->getChessData(row - 1, col - 1) == 0 &&
                    chess->getChessData(row + 1, col + 1) == 0 &&
                    chess->getChessData(row + 2, col + 1) == 0) {
                    scoreMap[row][col] += 500;
                }
            }

            // �����������
            emptyNum = 0;
            for (int y = -1; y <= 0; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (y == 0 && x == 0) continue;
                    if (y == 0 && x != 1) continue;
                    whiteNum = 0;
                    emptyNum = 0;
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == -1) {
                            whiteNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == -1) {
                            whiteNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // ����������͵÷�
                    if (whiteNum == 0) {
                        scoreMap[row][col] += 5;
                    }
                    else if (whiteNum == 1) {
                        scoreMap[row][col] += 10;
                    }
                    else if (whiteNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 25;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 50;
                        }
                    }
                    else if (whiteNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 55;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 10000;
                        }
                    }
                    else if (whiteNum >= 4) {
                        scoreMap[row][col] += 30000;
                    }
                    else if (whiteNum >= 5) {
                        // �ж����ĺ�����
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 50000;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 100000;
                        }
                    }
                }
            }

            // �ж�б����
            if (row >= 2 && col >= 2 && row < size - 2 && col < size - 2) {
                if (chess->getChessData(row - 2, col - 2) == 0 &&
                    chess->getChessData(row - 1, col - 1) == 0 &&
                    chess->getChessData(row + 1, col + 1) == 0 &&
                    chess->getChessData(row + 2, col + 2) == 0) {
                    scoreMap[row][col] += 500;
                }
            }

            // �жϰ�����
            if (row >= 2 && col >= 1 && row < size - 2 && col < size - 1) {
                if (chess->getChessData(row - 2, col - 1) == 0 &&
                    chess->getChessData(row - 1, col - 1) == 0 &&
                    chess->getChessData(row + 1, col + 1) == 0 &&
                    chess->getChessData(row + 2, col + 1) == 0) {
                    scoreMap[row][col] += 500;
                }
            }
        }
    }
}
//�м��Ѷ�
void AI::calculateScore1() {
    int blackNum = 0; // ���ַ������壩���ٸ�����������
    int whiteNum = 0; // AI�������壩�����ж��ٸ�����������
    int emptyNum = 0; // �÷����Ͽհ�λ�ĸ���
    // ����������������
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap[i].size(); j++) {
            scoreMap[i][j] = 0;
        }
    }
    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // ��ÿ������м���
            if (chess->getChessData(row, col)) continue;

            // �����������
            for (int y = -1; y <= 0; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (y == 0 && x == 0) continue;
                    if (y == 0 && x != 1) continue;
                    blackNum = 0;
                    emptyNum = 0;
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 1) {
                            blackNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 1) {
                            blackNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // ����������͵÷�
                    if (blackNum == 1) {
                        scoreMap[row][col] += 10;
                    }
                    else if (blackNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 30;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 40;
                        }
                    }
                    else if (blackNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 60;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 5000;
                        }
                    }
                    else if (blackNum == 4) {
                        scoreMap[row][col] += 20000;
                    }
                    else if (blackNum >= 5) {
                        // �ж����ĺ�����
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 100000;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 100000;
                        }
                    }
                }
            }

         

            // �����������
            emptyNum = 0;
            for (int y = -1; y <= 0; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (y == 0 && x == 0) continue;
                    if (y == 0 && x != 1) continue;
                    whiteNum = 0;
                    emptyNum = 0;
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row + i * y;
                        int curCol = col + i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == -1) {
                            whiteNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // �������
                    for (int i = 1; i <= 4; i++) {
                        int curRow = row - i * y;
                        int curCol = col - i * x;
                        if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == -1) {
                            whiteNum++;
                        }
                        else if (curRow >= 0 && curRow < size &&
                            curCol >= 0 && curCol < size &&
                            chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;
                            break;
                        }
                        else {
                            break;
                        }
                    }
                    // ����������͵÷�
                    if (whiteNum == 0) {
                        scoreMap[row][col] += 5;
                    }
                    else if (whiteNum == 1) {
                        scoreMap[row][col] += 10;
                    }
                    else if (whiteNum == 2) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 25;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 50;
                        }
                    }
                    else if (whiteNum == 3) {
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 55;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 10000;
                        }
                    }
                    else if (whiteNum >= 4) {
                        scoreMap[row][col] += 30000;
                    }
                    else if (whiteNum >= 5) {
                        // �ж����ĺ�����
                        if (emptyNum == 1) {
                            scoreMap[row][col] += 50000;
                        }
                        else if (emptyNum == 2) {
                            scoreMap[row][col] += 100000;
                        }
                    }
                }
            } 
        }
    }
}

//�߼�(����)
//void AI::calculateScore() {
//    int blackNum = 0; // ���ַ������壩���ٸ�����������
//    int whiteNum = 0; // AI�������壩�����ж��ٸ�����������
//    int emptyNum = 0; // �÷����Ͽհ�λ�ĸ���
//     //����������������
//    for (int i = 0; i < scoreMap.size(); i++) {
//        for (int j = 0; j < scoreMap[i].size(); j++) {
//            scoreMap[i][j] = 0;
//        }
//    }
//    int size = chess->getGradeSize();
//    for (int row = 0; row < size; row++) {
//        for (int col = 0; col < size; col++) {
//             //��ÿ������м���
//            if (chess->getChessData(row, col)) continue;
//
//             //�����������
//            for (int y = -1; y <= 0; y++) {
//                for (int x = -1; x <= 1; x++) {
//                    if (y == 0 && x == 0) continue;
//                    if (y == 0 && x != 1) continue;
//                    blackNum = 0;
//                    emptyNum = 0;
//                     //�������
//                    for (int i = 1; i <= 4; i++) {
//                        int curRow = row + i * y;
//                        int curCol = col + i * x;
//                        if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 1) {
//                            blackNum++;
//                        }
//                        else if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 0) {
//                            emptyNum++;
//                            break;
//                        }
//                        else {
//                            break;
//                        }
//                    }
//                     //�������
//                    for (int i = 1; i <= 4; i++) {
//                        int curRow = row - i * y;
//                        int curCol = col - i * x;
//                        if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 1) {
//                            blackNum++;
//                        }
//                        else if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 0) {
//                            emptyNum++;
//                            break;
//                        }
//                        else {
//                            break;
//                        }
//                    }
//                     //����������͵÷�
//                    if (blackNum == 1) {
//                        scoreMap[row][col] += 10;
//                    }
//                    else if (blackNum == 2) {
//                        if (emptyNum == 1) {
//                            scoreMap[row][col] += 30;
//                        }
//                        else if (emptyNum == 2) {
//                            scoreMap[row][col] += 40;
//                        }
//                    }
//                    else if (blackNum == 3) {
//                        if (emptyNum == 1) {
//                            scoreMap[row][col] += 600;
//                        }
//                        else if (emptyNum == 2) {
//                            scoreMap[row][col] += 5000;
//                        }
//                    }
//                    else if (blackNum == 4) {
//                        scoreMap[row][col] += 20000;
//                    }
//                }
//            }
//
//             //б����Ŀ��ֲ��� 
//            if (row >= 2 && col >= 2 && row < size - 2 && col < size - 2) {
//                if (chess->getChessData(row - 2, col - 2) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0 &&
//                    chess->getChessData(row + 2, col + 2) == 0) {
//                    scoreMap[row][col] += 500;
//                }
//            }
//
//             //������Ŀ��ֲ��� 
//            if (row >= 2 && col >= 1 && row < size - 2 && col < size - 1) {
//                if (chess->getChessData(row - 2, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0 &&
//                    chess->getChessData(row + 2, col + 1) == 0) {
//                    scoreMap[row][col] += 500;
//                }
//            }
//
//             //�ж��Ľ���
//            if ((row == 0 && col == 0) ||
//                (row == 0 && col == size - 1) ||
//                (row == size - 1 && col == 0) ||
//                (row == size - 1 && col == size - 1)) {
//                scoreMap[row][col] += 1000;
//            }
//
//            // �ж�˫�Ľ���
//            if ((row == 0 && col == 0 && chess->getChessData(size - 1, size - 1) == 0) ||
//                (row == 0 && col == size - 1 && chess->getChessData(size - 1, 0) == 0) ||
//                (row == size - 1 && col == 0 && chess->getChessData(0, size - 1) == 0) ||
//                (row == size - 1 && col == size - 1 && chess->getChessData(0, 0) == 0)) {
//                scoreMap[row][col] += 1500;
//            }
//
//            // �ж�÷����
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �жϽ���
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �ж�����
//            if (row >= 1 && col >= 2 && row < size - 1 && col < size - 2) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row, col - 2) == 0 &&
//                    chess->getChessData(row, col + 2) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �жϰ�����
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �ж�������
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 800;
//                }
//            }
//
//             //�����������
//            emptyNum = 0;
//            for (int y = -1; y <= 0; y++) {
//                for (int x = -1; x <= 1; x++) {
//                    if (y == 0 && x == 0) continue;
//                    if (y == 0 && x != 1) continue;
//                    whiteNum = 0;
//                    emptyNum = 0;
//                     //�������
//                    for (int i = 1; i <= 4; i++) {
//                        int curRow = row + i * y;
//                        int curCol = col + i * x;
//                        if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == -1) {
//                            whiteNum++;
//                        }
//                        else if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 0) {
//                            emptyNum++;
//                            break;
//                        }
//                        else {
//                            break;
//                        }
//                    }
//                     //�������
//                    for (int i = 1; i <= 4; i++) {
//                        int curRow = row - i * y;
//                        int curCol = col - i * x;
//                        if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == -1) {
//                            whiteNum++;
//                        }
//                        else if (curRow >= 0 && curRow < size &&
//                            curCol >= 0 && curCol < size &&
//                            chess->getChessData(curRow, curCol) == 0) {
//                            emptyNum++;
//                            break;
//                        }
//                        else {
//                            break;
//                        }
//                    }
//                     //����������͵÷�
//                    if (whiteNum == 0) {
//                        scoreMap[row][col] += 5;
//                    }
//                    else if (whiteNum == 1) {
//                        scoreMap[row][col] += 10;
//                    }
//                    else if (whiteNum == 2) {
//                        if (emptyNum == 1) {
//                            scoreMap[row][col] += 25;
//                        }
//                        else if (emptyNum == 2) {
//                            scoreMap[row][col] += 50;
//                        }
//                    }
//                    else if (whiteNum == 3) {
//                        if (emptyNum == 1) {
//                            scoreMap[row][col] += 550;
//                        }
//                        else if (emptyNum == 2) {
//                            scoreMap[row][col] += 10000;
//                        }
//                    }
//                    else if (whiteNum >= 4) {
//                        scoreMap[row][col] += 30000;
//                    }
//                }
//            }
//
//             //�ж�б����
//            if (row >= 2 && col >= 2 && row < size - 2 && col < size - 2) {
//                if (chess->getChessData(row - 2, col - 2) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0 &&
//                    chess->getChessData(row + 2, col + 2) == 0) {
//                    scoreMap[row][col] += 500;
//                }
//            }
//
//             //�жϰ�����
//            if (row >= 2 && col >= 1 && row < size - 2 && col < size - 1) {
//                if (chess->getChessData(row - 2, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0 &&
//                    chess->getChessData(row + 2, col + 1) == 0) {
//                    scoreMap[row][col] += 500;
//                }
//            }
//
//             //�ж��Ľ���
//            if ((row == 0 && col == 0) ||
//                (row == 0 && col == size - 1) ||
//                (row == size - 1 && col == 0) ||
//                (row == size - 1 && col == size - 1)) {
//                scoreMap[row][col] += 1000;
//            }
//
//            // �ж�˫�Ľ���
//            if ((row == 0 && col == 0 && chess->getChessData(size - 1, size - 1) == 0) ||
//                (row == 0 && col == size - 1 && chess->getChessData(size - 1, 0) == 0) ||
//                (row == size - 1 && col == 0 && chess->getChessData(0, size - 1) == 0) ||
//                (row == size - 1 && col == size - 1 && chess->getChessData(0, 0) == 0)) {
//                scoreMap[row][col] += 1500;
//            }
//
//            // �ж�÷����
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �жϽ���
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �ж�����
//            if (row >= 1 && col >= 2 && row < size - 1 && col < size - 2) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row, col - 2) == 0 &&
//                    chess->getChessData(row, col + 2) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �жϰ�����
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0 &&
//                    chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 600;
//                }
//            }
//
//            // �ж�������
//            if (row >= 1 && col >= 1 && row < size - 1 && col < size - 1) {
//                if (chess->getChessData(row - 1, col - 1) == 0 &&
//                    chess->getChessData(row - 1, col) == 0 &&
//                    chess->getChessData(row - 1, col + 1) == 0 &&
//                    chess->getChessData(row, col - 1) == 0 &&
//                    chess->getChessData(row, col) == 0 &&
//                    chess->getChessData(row, col + 1) == 0 &&
//                    chess->getChessData(row + 1, col - 1) == 0 &&
//                    chess->getChessData(row + 1, col) == 0 &&
//                    chess->getChessData(row + 1, col + 1) == 0) {
//                    scoreMap[row][col] += 800;
//                }
//            }
//
//        }
//    }
//}

// ���������ѡ����߷ֵ�λ��
ChessPos AI::think()
{
    calculateScore1();
	int maxScore = 0;
	vector<ChessPos> maxPoints;

	int size = chess->getGradeSize();

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
			{
				int cellScore = scoreMap[row][col];

				if (cellScore > maxScore)
				{
					maxScore = cellScore;
					maxPoints.clear();
					maxPoints.emplace_back(row, col);
				}
				else if (cellScore == maxScore)
				{
					maxPoints.emplace_back(row, col);
				}
			}
		}
	}

	// ʹ�������������ѡ��һ����߷ֵ�λ��
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
