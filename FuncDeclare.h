/*
 * ���ϸ� : FuncDelcare
 * ��� : ��� �Լ� ���� ����
 * ���� ��¥ : 2019-11-25
 * ���� ������ : �������б�
 *				���¼ҽ�����[Pro.�幮��] - Team5 (������, ���μ�, ������, ����)
 */

#ifndef FuncDeclare
#define FuncDeclare

#include "basedef.h"
/*Declare of function template in TTTFunc.c*/
void printRanking(void);
int insertRanking(float, int);
void initBoard(int[][A_SIZE]);
void printBoard(const int[][A_SIZE]);
int isBoardFull(const int[][A_SIZE]);
void makeMove(int[][A_SIZE], int, int, const int);
int is3inARow(const int[][A_SIZE], const int);
int isAWin(const int[][A_SIZE], const int);
void ComputerTurn(int[][A_SIZE], int , int);
void HumanTurn(int[][A_SIZE],const int);
void runGameVSCom(void);
void runGameVSHuman(void);
void showMenu(void);
void consoleClear(void);

/*Declare of function template in MIN_MAX_Alg.c*/
int Max(int[], int, int[], int*);
int Min(int[], int, int[], int*);
int minMax_EASY(int[][A_SIZE], int);
int minMax_NORMAL(int[][A_SIZE], int, int*);
int minMax_HARD(int[][A_SIZE], int, int*);
int computerLvlSelect();
#endif