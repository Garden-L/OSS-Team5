
/*
 * 파일명 : Ranking.c
 * 기능 : 랭킹 시스템 관련 정의
 * 수정 날짜 : 2019-11-29
 * 파일 제작자 : 세종대학교
 *				오픈소스개론[Pro.장문정] - Team5 (임정원, 강민성, 원성훈, 고선엽)
 */


#include <stdio.h>
#include "basedef.h"
#include "FuncDeclare.h"

/*
-기능: 게임 시작 전 이전에 저장된 랭킹을 보여줌
-상세: rank.txt파일이 있는지 확인하고 있다면 구조체 ranking에 입력받아 출력
-출력예시: 
	score	status	id
	10.1	W		16011038
*/
void printRanking(void)
{
	//랭킹 파일의 구성
	/*시간 승/무승 이름\n*/
	struct ranking r[5];

	FILE* rankingFile = NULL;

	fopen_s(&rankingFile, "rank.txt", "r");


	//랭킹을 입력받을 구조체를 초기화
	for (int i = 0; i < 5; i++)
	{
		r[i].id = -1;
		r[i].score = -1;
		r[i].status = -1;
	}

	//랭킹 파일이 있을시 파일에서 랭킹을 받아옴
	if (rankingFile != NULL)
	{

		for (int i = 0; i < 5; i++)
		{
			if (feof(rankingFile) == EOF) { break; }
			fscanf_s(rankingFile, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}

		fclose(rankingFile);
	}
	//랭킹파일이 없을시 파일을 생성해줌
	else
	{
		fopen_s(&rankingFile, "rank.txt", "w");
		fclose(rankingFile);
	}

	//출력 순서
	/*score status name*/
	printf_s("\nNow Ranking\nScore(time)\tStatus\t\tStudent ID\n");
	for (int i = 0; i < 5; i++)
	{
		char status = '\0';
		if (r[i].score == -1)
		{
			break;
		}

		if (r[i].status == WIN)
		{
			status = 'W';
		}
		else
		{
			status = 'D';
		}

		printf_s("%.2f\t\t%c\t\t%d\n", r[i].score, status, r[i].id);
	}

	printf_s("\n\n");

}

/*
-기능: 게임이 끝난 후 랭킹을 삽입함
-상세: 게임을 비기거나 이겼을시 얻은 점수를 이전의 랭킹과 비교해보고 순위(5등)에 들수 있을경우
학번(id)을 입력받고 랭킹파일에 삽입
*/
int insertRanking(float time, int status)
{

	if (status == LOSE) { return 0; }
	
	//랭킹 파일의 구성
	/*시간 승/무승 이름\n*/
	struct ranking r[5];

	//랭킹을 입력받을 구조체를 초기화
	for (int i = 0; i < 5; i++)
	{
		r[i].score = -1;
		r[i].status = -1;
		r[i].id = -1;
	}
	
	//랭킹에 들 수 있는지 확인해주는 seat 변수
	int seat = -1;
	int id = -1;
	FILE* rankingFile = NULL;

	fopen_s(&rankingFile, "rank.txt", "r");

	//랭킹파일이 있는지 확인하고 랭킹을 받아옴
	if (rankingFile != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (feof(rankingFile) == EOF) { break; }
			fscanf_s(rankingFile, "%f %d %d\n", &r[i].score, &r[i].status, &r[i].id);
		}
		fclose(rankingFile);
	}

	//랭킹과 현재 받은 점수를 바교해줌
	for (int i = 0; i < 5; i++)
	{
		if (r[i].score == -1)
		{
			seat = i;
			break;
		}

		if (r[i].score > time)
		{
			seat = i;
			break;
		}
	}

	//점수가 랭킹에 들 점수가 아닐경우
	if (seat == -1)
	{
		printf_s("Your score is not good enough to rank. Play the game faster\n\n");
	}
	//점수가 랭킹에 들어가기에 충분할 경우 점수를 보여주고 아이디를 입력받음
	else
	{

		printf_s("Your score is %.2f\n\n", time);
		printf_s("Scores can be ranked. Please enter your student ID\nID(To int) : ");
		scanf_s("%d", &id);
		printf_s("\n\n");

		for (int i = 4; i > seat; i--)
		{
			r[i].id = r[i - 1].id;
			r[i].score = r[i - 1].score;
			r[i].status = r[i - 1].status;
		}

		r[seat].score = time;
		r[seat].id = id;
		r[seat].status = status;

		fopen_s(&rankingFile, "rank.txt", "w");
		
		//랭킹 파일에 변경된 랭킹 삽입
		for (int i = 0; i < 5; i++)
		{
			if (r[i].score == -1) { break; }

			fprintf_s(rankingFile, "%.2f %d %d\n", r[i].score, r[i].status, r[i].id);

		}

		fclose(rankingFile);
	}

	printf_s("Well saved!\n\n");

	return 0;
}