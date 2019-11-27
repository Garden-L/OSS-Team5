/*
 * ���ϸ� : basedef.h
 * ��� : ��� ��ȯ ��, �Ǵ� �ɺ� ���� ���� ����
 * ���� ��¥ : 2019-11-25
 * ���� ������ : �������б�
 *				���¼ҽ�����[Pro.�幮��] - Team5 (������, ���μ�, ������, ����)
 */
#ifndef BASE_DEFINE
#define BASE_DEFINE

/* Define of array size */
#define A_SIZE 3  // Array size

/* Default number of return */
#define FALSE 0
#define TRUE 1

/*Define number of game point*/
#define WIN 10
#define LOSE -10
#define DRAW 0	

/*Define nuber of board check*/
enum { HUMAN, COMP, EMPTY };

/*Define number of level*/
#define EASY 100
#define NORMAL 200
#define HARD 300


/*Define ranking's element*/
struct ranking 
{
	float score;
	int status;
	int id;
};

#endif