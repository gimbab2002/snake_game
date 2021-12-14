#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<process.h>
#include<stdbool.h>
#include<string.h>
#define ESC 27
#define A3 220.0000
#define B3 246.9417
#define C4 261.6256
#define D4 293.6648
#define E4 329.6276
#define F4 349.2282
#define G4 391.9954
#define A4 440.0000
#define B4 493.8833
int soundcount = 0;
int difficulty;

CRITICAL_SECTION cr;


int height = 17, width = 17;  //dimensions of out field
typedef struct RECORD {
	char name[100];
	int score;
	int minute;
	int sec;
	struct RECORD* next;
}record; //이름, 점수, 시간을 저장할 구조체
typedef struct Coord {
	int x;
	int y;
}Coord;
int score;
int fruitx, fruity;
int fruitx1, fruity1;
int fruitx2, fruity2;// Global variables 선언// Global variables 선언
record nowrec;

int over = 0;
const Coord WALLS[] = {
	{.x = 3, .y = 3},
	{.x = 4, .y = 3},
	{.x = 5, .y = 3},
	{.x = 5, .y = 4},
	{.x = 5, .y = 4},
	{.x = 5, .y = 5},
	{.x = 4, .y = 8},
	{.x = 4, .y = 9},
	{.x = 4, .y = 10},
	{.x = 4, .y = 11},
	{.x = 5, .y = 10},
	{.x = 6, .y = 10},
	{.x = 7, .y = 10},
	{.x = 8, .y = 4},
	{.x = 8, .y = 5},
	{.x = 8, .y = 6},
	{.x = 8, .y = 7},
	{.x = 9, .y = 4},
	{.x = 10, .y = 4},
	{.x = 11, .y = 4},
	{.x = 12, .y = 4},
	{.x = 7, .y = 14},
	{.x = 8, .y = 14},
	{.x = 9, .y = 14},
	{.x = 10, .y = 14},
	{.x = 11, .y = 14},
	{.x = 12, .y = 14},
	{.x = 11, .y = 13},
	{.x = 11, .y = 12},
	{.x = 11, .y = 11},
	{.x = 11, .y = 10},
	{.x = 11, .y = 9},
	{.x = 14, .y = 6},
	{.x = 14, .y = 7},
	{.x = 14, .y = 8},
	{.x = 14, .y = 9},
	{.x = 14, .y = 10}
};
const Coord WALLS1[] = {    //60개
	{.x = 3, .y = 3},
	{.x = 4, .y = 3},
	{.x = 3, .y = 4},
	{.x = 2, .y = 6},
	{.x = 7, .y = 2},
	{.x = 8, .y = 2},
	{.x = 9, .y = 2},
	{.x = 10, .y = 2},
	{.x = 11, .y = 2},
	{.x = 12, .y = 2},
	{.x = 8, .y = 3},
	{.x = 5, .y = 5},
	{.x = 4, .y = 6},
	{.x = 5, .y = 6},
	{.x = 4, .y = 7},
	{.x = 8, .y = 6},
	{.x = 9, .y = 6},
	{.x = 10, .y = 6},
	{.x = 11, .y = 6},
	{.x = 11, .y = 5},
	{.x = 11, .y = 7},
	{.x = 14, .y = 4},
	{.x = 14, .y = 5},
	{.x = 14, .y = 6},
	{.x = 15, .y = 6},
	{.x = 3, .y = 9},
	{.x = 3, .y = 10},
	{.x = 6, .y = 9},
	{.x = 7, .y = 9},
	{.x = 8, .y = 9},
	{.x = 9, .y = 9},
	{.x = 3, .y = 12},
	{.x = 4, .y = 12},
	{.x = 5, .y = 12},
	{.x = 6, .y = 12},
	{.x = 4, .y = 13},
	{.x = 4, .y = 14},
	{.x = 9, .y = 11},
	{.x = 10, .y = 11},
	{.x = 11, .y = 11},
	{.x = 12, .y = 11},
	{.x = 13, .y = 11},
	{.x = 12, .y = 10},
	{.x = 15, .y = 9},
	{.x = 15, .y = 10},
	{.x = 15, .y = 11},
	{.x = 15, .y = 12},
	{.x = 9, .y = 13},
	{.x = 2, .y = 15},
	{.x = 2, .y = 16},
	{.x = 7, .y = 15},
	{.x = 8, .y = 15},
	{.x = 9, .y = 15},
	{.x = 12, .y = 13},
	{.x = 12, .y = 14},
	{.x = 12, .y = 15},
	{.x = 14, .y = 14},
	{.x = 15, .y = 14},
	{.x = 16, .y = 14},
	{.x = 5, .y = 16},
};
const Coord WALLS2[] = {
   {.x = 4, .y = 4},
   {.x = 5, .y = 4},
   {.x = 4, .y = 5},
   {.x = 5, .y = 5},
   {.x = 9, .y = 5},
   {.x = 10, .y = 5},
   {.x = 11, .y = 5},
   {.x = 9, .y = 6},
   {.x = 10, .y = 6},
   {.x = 11, .y = 6},
   {.x = 5, .y = 10},
   {.x = 6, .y = 10},
   {.x = 5, .y = 11},
   {.x = 6, .y = 11},
   {.x = 5, .y = 12},
   {.x = 6, .y = 12},
   {.x = 11, .y = 13},
   {.x = 12, .y = 13},
   {.x = 13, .y = 13},
   {.x = 11, .y = 14},
   {.x = 12, .y = 14},
   {.x = 13, .y = 14}
};

void gotoxy(int x, int y);          //입력 위치 설정
void make_stage_low();                  //스테이지하 구현
void make_stage_mid();                  //스테이지중 구현
void make_stage_high();                 //스테이지상 구현
void gameover();            //게임오버 화면
void startscr();                    //시작 화면
void snake_move_low();                  //뱀의 움직임
void snake_move_mid();                  //뱀의 움직임
void snake_move_high();                 //뱀의 움직임
int rank_call();					//랭킹 표시
void rankrecord();                  //랭킹 기록
void cursor(int i);             //커서 상태 변경
void stopwatch();               //스톱워치 보여주기
void wall(int x, int y);                //장애물
Coord fruit();
bool isWall(Coord coord);
void fruitsound();			//fruit을 빨리 먹으면 소리 출력
void FruitColorOutput();
void ScoreColorOutput();
void ordinalnum(int num);
int main(void) {
	startscr();
	return 0;
}

bool isWall(Coord coord)
{
	for (int i = 0; i < sizeof(WALLS) / sizeof(Coord); i++)
	{
		if (coord.x == WALLS[i].x && coord.y == WALLS[i].y)
		{
			return 1;
		}
	}
	for (int i = 0; i < sizeof(WALLS1) / sizeof(Coord); i++)
	{
		if (coord.x == WALLS1[i].x && coord.y == WALLS1[i].y)
		{
			return 1;
		}
	}
	for (int i = 0; i < sizeof(WALLS2) / sizeof(Coord); i++)
	{
		if (coord.x == WALLS2[i].x && coord.y == WALLS2[i].y)
		{
			return 1;
		}
	}

	return 0;
}
Coord fruit() {
	// generates a fruit coordinates that are not on the walls
	srand(time(NULL));
	while (1)
	{
		Coord fruitXY = { 2 + rand() % 15, 2 + rand() % 15 };
		if (!isWall(fruitXY))
		{
			return fruitXY;

		}
	}
}

void gotoxy(int x, int y) {
	COORD pos = { 30 + x * 2, 10 + y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void wall(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	gotoxy(x, y);
	printf("#");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void make_stage_low() {
	Beep(C4, 500);
	//Drawing the snake in this function
	int x = 9, y = 9;
	int x1 = 8, y1 = 9;
	int x2 = 7, y2 = 9;
	int x3 = 6, y3 = 9;
	int x4 = 5, y4 = 9;
	gotoxy(x, y);
	printf("a");
	gotoxy(x1, y1);
	printf("*");
	gotoxy(x2, y2);
	printf("*");
	gotoxy(x3, y3);
	printf("*");
	gotoxy(x4, y4);
	printf("*");
	for (int i = 1; i <= 17; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(i, 1);
		printf("#");
		gotoxy(1, i);
		printf("#");
		gotoxy(17, i);
		printf("#");
		gotoxy(i, 17);
		printf("#");
	}
	gotoxy(4, 4);
	printf("# #");
	gotoxy(4, 5);
	printf("# #");
	gotoxy(5, 10);
	printf("# #");
	gotoxy(5, 11);
	printf("# #");
	gotoxy(5, 12);
	printf("# #");
	gotoxy(9, 5);
	printf("# # #");
	gotoxy(9, 6);
	printf("# # #");
	gotoxy(11, 13);
	printf("# # #");
	gotoxy(11, 14);
	printf("# # #");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	Coord fruit2xy = fruit();
	fruity2 = fruit2xy.y;
	fruitx2 = fruit2xy.x;
	gotoxy(fruitx2, fruity2);   // Feeding 2+rand()%15 into gotoxy
	FruitColorOutput();
}

void make_stage_mid() {
	Beep(C4, 500);
	int x = 9, y = 9;
	int x1 = 8, y1 = 9;
	int x2 = 7, y2 = 9;
	int x3 = 6, y3 = 9;
	int x4 = 5, y4 = 9;
	gotoxy(x, y);
	printf("a");
	gotoxy(x1, y1);
	printf("*");
	gotoxy(x2, y2);
	printf("*");
	gotoxy(x3, y3);
	printf("*");
	gotoxy(x4, y4);
	printf("*");
	for (int i = 1; i <= 17; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(i, 1);
		printf("#");
		gotoxy(1, i);
		printf("#");
		gotoxy(17, i);
		printf("#");
		gotoxy(i, 17);
		printf("#");
	}
	for (int i = 0; i < 37; i++)
	{
		Coord awall = WALLS[i];
		wall(awall.x, awall.y);
	}
	Coord fruitxy = fruit();
	fruity = fruitxy.y;
	fruitx = fruitxy.x;
	gotoxy(fruitx, fruity);   // Feeding 2+rand()%15 into gotoxy
	FruitColorOutput();
}

void make_stage_high() {
	Beep(C4, 500);
	int x = 11, y = 8;
	int x1 = 10, y1 = 8;
	int x2 = 9, y2 = 8;
	int x3 = 8, y3 = 8;
	int x4 = 7, y4 = 8;
	gotoxy(x, y);
	printf("a");
	gotoxy(x1, y1);
	printf("*");
	gotoxy(x2, y2);
	printf("*");
	gotoxy(x3, y3);
	printf("*");
	gotoxy(x4, y4);
	printf("*");
	for (int i = 1; i <= 17; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(i, 1);
		printf("#");
		gotoxy(1, i);
		printf("#");
		gotoxy(17, i);
		printf("#");
		gotoxy(i, 17);
		printf("#");
	}
	wall(3, 3); wall(4, 3); wall(3, 4); wall(7, 2); wall(8, 2); wall(9, 2); wall(10, 2); wall(11, 2); wall(12, 2); wall(8, 3); wall(2, 6);
	wall(4, 6); wall(4, 7); wall(5, 6); wall(5, 5); wall(8, 6); wall(9, 6); wall(10, 6); wall(11, 6); wall(11, 5); wall(11, 7); wall(14, 4);
	wall(14, 5); wall(14, 6); wall(15, 6); wall(3, 9); wall(3, 10); wall(6, 9); wall(7, 9); wall(8, 9); wall(9, 9); wall(9, 11); wall(10, 11);
	wall(11, 11); wall(12, 11); wall(13, 11); wall(12, 10);  wall(15, 9); wall(15, 10); wall(15, 11); wall(15, 12); wall(3, 12);  wall(4, 12);
	wall(5, 12); wall(6, 12); wall(4, 13); wall(4, 14); wall(9, 13); wall(2, 15); wall(2, 16); wall(7, 15); wall(8, 15); wall(9, 15);
	wall(12, 13); wall(12, 14); wall(12, 15); wall(14, 14); wall(15, 14); wall(16, 14); wall(5, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	Coord fruit1xy = fruit();
	fruity1 = fruit1xy.y;
	fruitx1 = fruit1xy.x;
	gotoxy(fruitx1, fruity1);   // Feeding 2+rand()%15 into gotoxy
	FruitColorOutput();
}

void cursor(int i) {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int rank_call() {
	record reading;

select:
	system("cls");
	printf("   ******   **    *       *      *    *  ******           ******      *        **    **    ******   \n");
	printf("   *        * *   *      * *     *   *   *                *          * *      *  *  *  *   *        \n");
	printf("   ******   *  *  *     *****    ****    ******           *  ***    *****     *  *  *  *   ******   \n");
	printf("        *   *   * *    *     *   *   *   *                *    *   *     *   *    **    *  *        \n");
	printf("   ******   *    **   *       *  *    *  ******           ******  *       *  *    **    *  ******   \n");
	printf("\nselect the level\n\nhigh->press h\n\nmiddle->press m\n\nlow->press l\n");
	char lev = _getch();
	if (lev == 'h') {
		FILE* rankH;
		if (fopen_s(&rankH, "rankH.txt", "r") != 0) printf("no record\n");
		else {
			printf("\n");

			int num = 1;
			while (fscanf(rankH, "%s %d %d : %d\n", reading.name, &reading.score, &reading.minute, &reading.sec) != EOF) {
				ordinalnum(num);
				printf(">>%s\nscore>> %d\ntime>> %d : %d\n\n", reading.name, reading.score, reading.minute, reading.sec);
				Sleep(1000);
				num++;
			}
			fclose(rankH);
			printf("\n");
		}
		return 1;
	}
	else if (lev == 'm') {
		FILE* rankM;
		if (fopen_s(&rankM, "rankM.txt", "r") != 0) printf("no record\n");
		else {
			printf("\n");

			int num = 1;
			while (fscanf(rankM, "%s %d %d : %d\n", reading.name, &reading.score, &reading.minute, &reading.sec) != EOF) {
				ordinalnum(num);
				printf(">>%s\nscore>> %d\ntime>> %d : %d\n\n", reading.name, reading.score, reading.minute, reading.sec);
				Sleep(1000);
				num++;
			}
			fclose(rankM);
			printf("\n");
		}
		return 1;
	}
	else if (lev == 'l') {
		FILE* rankL;
		if (fopen_s(&rankL, "rankL.txt", "r") != 0) printf("no record\n");
		else {
			printf("\n");

			int num = 1;
			while (fscanf(rankL, "%s %d %d : %d\n", reading.name, &reading.score, &reading.minute, &reading.sec) != EOF) {
				ordinalnum(num);
				printf(">>%s\nscore>> %d\ntime>> %d : %d\n\n", reading.name, reading.score, reading.minute, reading.sec);
				Sleep(1000);
				num++;
			}
			fclose(rankL);
			printf("\n");
		}
		return 1;
	}
	else if (lev == ESC) {
		return 0;
	}
	else {
		printf("wrong selection\n");
		printf("press enter to continue...");
		while (getchar() != '\n');
		goto select;
	}

}

void rankrecord() {
	FILE* rank = NULL;
	if (difficulty == 3) {
		if ((rank = fopen("rankH.txt", "r")) == NULL)		//if there's not rank.txt file, it will create the file.
		{
			rank = fopen("rankH.txt", "w+");
		}
	}
	else if (difficulty == 2) {
		if ((rank = fopen("rankM.txt", "r")) == NULL)
		{
			rank = fopen("rankM.txt", "w+");
		}
	}
	else if (difficulty == 1) {
		if ((rank = fopen("rankL.txt", "r")) == NULL)
		{
			rank = fopen("rankL.txt", "w+");
		}
	}
	printf("\npress enter to proceed...\n");
	while (getchar() != '\n');
	record* rec;
	record* cur;
	record* pre;
	record* first;
	record* temp;
	first = (record*)malloc(sizeof(record));
	first->score = -1;
	first->next = NULL;
	temp = (record*)malloc(sizeof(record));
	while (fscanf(rank, "%s %d %d : %d\n", temp->name, &temp->score, &temp->minute, &temp->sec) != EOF) {			//read the rank and sort.
		if (first->next == NULL) {
			rec = (record*)malloc(sizeof(record));
			strcpy(rec->name, temp->name);
			rec->score = temp->score;
			rec->minute = temp->minute;
			rec->sec = temp->sec;
			rec->next = NULL;

			first->next = rec;
		}
		else {
			rec = (record*)malloc(sizeof(record));
			strcpy(rec->name, temp->name);
			rec->score = temp->score;
			rec->minute = temp->minute;
			rec->sec = temp->sec;
			rec->next = NULL;

			pre = first;
			cur = first->next;
			while (cur != NULL) {
				if (rec->score < cur->score) {
					pre = cur;
					cur = cur->next;
				}
				else break;
			}
			pre->next = rec;
			rec->next = cur;
		}
	}
	pre = first;
	cur = first->next;
	int i = 0;
	while (cur != NULL) {
		pre = cur;
		cur = cur->next;
		i++;
	}
	if (i < 10 || pre->score <= nowrec.score) {				//recognizing whether newrec is in top ten or not by comparing with the smallest score.
		char input;
	re:
		gotoxy(-15, 8);
		printf("you are in top 10. Do you wanna record your record? if so, press 'y'. if not press 'n'\n");		//from here, TUI strating.
		input = _getch();
		if (input == 'y') {
		rerun:
			gotoxy(-15, 10);
			printf("\r                                                                                   \r");
			printf("enter your name: ");
			gets_s(nowrec.name, sizeof(nowrec.name));
			if (strlen(nowrec.name) < 3) {
				printf("name must be at least 3 words...");
				Sleep(1000);
				printf("\r                                  \r");
				goto rerun;
			}
			while (1) {
				printf("\n\nyour name is %s.\nyour score is %d.\nyour clear time is %d : %d.\n\n", nowrec.name, nowrec.score, nowrec.minute, nowrec.sec);
				printf("if your name is incorrect, press n to correct\nif not, press y to continue...\n\n");
			in:
				input = _getch();
				if (input == 'n') goto rerun;
				else if (input == 'y') break;
				else {
					printf("wrong input");
					Sleep(1000);
					printf("\r              \r");
					goto in;
				}
			}
		}
		else if (input == 'n') {
			return;
		}
		else {
			printf("Wrong input. Try again");
			Sleep(1000);
			printf("\r                                       \r");
			goto re;
		}
		fclose(rank);
		if (difficulty == 3) rank = fopen("rankH.txt", "w");
		else if (difficulty == 2) rank = fopen("rankM.txt", "w");
		else rank = fopen("rankL.txt", "w");

		rec = (record*)malloc(sizeof(record));				//rank record start
		strcpy(rec->name, nowrec.name);
		rec->score = nowrec.score;
		rec->minute = nowrec.minute;
		rec->sec = nowrec.sec;
		pre = first;
		cur = first->next;
		while (cur != NULL) {
			if (rec->score <= cur->score) {
				pre = cur;
				cur = cur->next;
			}
			else break;
		}
		pre->next = rec;
		rec->next = cur;
		pre = first;
		cur = first->next;
		int i = 0;
		while (cur != NULL) {

			fprintf(rank, "%s %d %d : %d\n", cur->name, cur->score, cur->minute, cur->sec);
			pre = cur;
			cur = cur->next;
			i++;
			if (i > 9)break;
		}
		printf("saved!\n");
		free(temp);											//free the linked lists.
		cur = first->next;
		while (cur != NULL) {
			record* next = cur->next;
			free(cur);
			cur = next;
		}
		free(first);
		fclose(rank);

	}
}


void startscr()
{

	system("mode con cols=100 lines=40");
start:

	over = 0;
	soundcount = 0;
	system("cls");
	printf("   ******   **    *       *      *    *  ******           ******      *        **    **    ******   \n");
	printf("   *        * *   *      * *     *   *   *                *          * *      *  *  *  *   *        \n");
	printf("   ******   *  *  *     *****    ****    ******           *  ***    *****     *  *  *  *   ******   \n");
	printf("        *   *   * *    *     *   *   *   *                *    *   *     *   *    **    *  *        \n");
	printf("   ******   *    **   *       *  *    *  ******           ******  *       *  *    **    *  ******   \n");
	printf("\npress s to start game\n");
	printf("press r to see ranking\n");
	printf("press x to exit\n:");
	char input = _getch();
	if (input == 's') {
	select:
		system("cls");
		printf("   ******   **    *       *      *    *  ******           ******      *        **    **    ******   \n");
		printf("   *        * *   *      * *     *   *   *                *          * *      *  *  *  *   *        \n");
		printf("   ******   *  *  *     *****    ****    ******           *  ***    *****     *  *  *  *   ******   \n");
		printf("        *   *   * *    *     *   *   *   *                *    *   *     *   *    **    *  *        \n");
		printf("   ******   *    **   *       *  *    *  ******           ******  *       *  *    **    *  ******   \n");
		printf("\nselect the level\n\nhigh->press h\n\nmiddle->press m\n\nlow->press l\n");
		char lev = _getch();
		if (lev == 'h') {
			difficulty = 3;
			system("cls");
			cursor(0);
			make_stage_high();
			InitializeCriticalSection(&cr);
			HANDLE thread1 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(100);
			HANDLE thread2 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_high, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
			DeleteCriticalSection(&cr);
		}
		if (lev == 'm') {
			difficulty = 2;
			system("cls");
			cursor(0);
			make_stage_mid();
			InitializeCriticalSection(&cr);
			HANDLE thread1 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(100);
			HANDLE thread2 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_mid, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
			DeleteCriticalSection(&cr);
		}
		if (lev == 'l') {
			difficulty = 1;
			system("cls");
			cursor(0);
			make_stage_low();
			InitializeCriticalSection(&cr);
			HANDLE thread1 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(100);
			HANDLE thread2 = (uintptr_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_low, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
			DeleteCriticalSection(&cr);
		}
		if (lev == ESC) {
			goto start;
		}
		else {
			printf("wrong selection\n");
			printf("press enter to continue...");
			while (getchar() != '\n');
			goto select;
		}
	}
	else if (input == 'r') {
		if (rank_call() == 0)goto start;
		printf("press enter to continue...");
		while (getchar() != '\n');
		goto start;
	}
	else if (input == 'x') exit(0);
	else {
		printf("wrong input\n");
		printf("press enter to continue...");
		while (getchar() != '\n');
		goto start;
	}
}

void gameover() {
	Beep(A3, 500);
	over = 1;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("        ******      *        **    **    ******            ****   *       *  ******   *****         \n");
	printf("        *          * *      *  *  *  *   *                *    *   *     *   *        *    *        \n");
	printf("        *  ***    *****     *  *  *  *   ******           *    *    *   *    ******   *****         \n");
	printf("        *    *   *     *   *    **    *  *                *    *     * *     *        *    *        \n");
	printf("        ******  *       *  *    **    *  ******            ****       *      ******   *     *      \n");
	cursor(0);
	nowrec.score = score;
	rankrecord();
	difficulty = 0;
	printf("press any key to back to title...");
	_getch();
	startscr();
}


void snake_move_low() {
	score = 0;
	int last = time(NULL);
	int i = 4;
	int x[100];
	int y[100];
	x[0] = 9;
	y[0] = 9;
	x[1] = 8;
	y[1] = 9;
	x[2] = 7;
	y[2] = 9;
	x[3] = 6;
	y[3] = 9;
	x[4] = 5;
	y[4] = 9;
	char dir = 'd';
	char input = 'e';
	EnterCriticalSection(&cr);
	gotoxy(-1, -1);
	ScoreColorOutput();
	LeaveCriticalSection(&cr);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
		srand(time(NULL));
		if (x[0] == fruitx2 && y[0] == fruity2) {
			if (i <= 100) {
				i++;
			}
			int cur = time(NULL);
			if (cur - last <= 1) {
				score *= 2;
				fruitsound();
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 2) {
				score += 20;
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 3) {
				score += 15;
				fruitsound();
			}
			else {
				score += 10;
				soundcount = 0;
				fruitsound();
			}
			time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			EnterCriticalSection(&cr);
			Coord fruit2xy = fruit();
			fruity2 = fruit2xy.y;
			fruitx2 = fruit2xy.x;
			gotoxy(fruit2xy.x, fruit2xy.y);
			FruitColorOutput();
			gotoxy(-1, -1);
			ScoreColorOutput();
			LeaveCriticalSection(&cr);
		}
		for (int j = 1; j <= i; j++) {
			if (x[j] == fruitx2 && y[j] == fruity2) {
				EnterCriticalSection(&cr);
				Coord fruit2xy = fruit();
				fruity2 = fruit2xy.y;
				fruitx2 = fruit2xy.x;
				gotoxy(fruit2xy.x, fruit2xy.y);
				FruitColorOutput();
				LeaveCriticalSection(&cr);
			}
		}
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] - 1;
				if (y[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 4 && y[0] == 5) || (x[0] == 5 && y[0] == 5) || (x[0] == 5 && y[0] == 12) || (x[0] == 6 && y[0] == 12) || (x[0] == 9 && y[0] == 6) ||
					(x[0] == 10 && y[0] == 6) || (x[0] == 11 && y[0] == 14) || (x[0] == 12 && y[0] == 14) || (x[0] == 13 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'w';
			}
			if (input == 'a') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] - 1;
				if (x[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 5 && y[0] == 4) || (x[0] == 5 && y[0] == 5) || (x[0] == 6 && y[0] == 10) || (x[0] == 6 && y[0] == 11) || (x[0] == 6 && y[0] == 12) ||
					(x[0] == 10 && y[0] == 5) || (x[0] == 10 && y[0] == 6) || (x[0] == 13 && y[0] == 13) || (x[0] == 13 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'a';
			}
			if (input == 's') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] + 1;
				if (y[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 4 && y[0] == 4) || (x[0] == 5 && y[0] == 4) || (x[0] == 5 && y[0] == 10) || (x[0] == 6 && y[0] == 10) || (x[0] == 9 && y[0] == 5) ||
					(x[0] == 10 && y[0] == 5) || (x[0] == 11 && y[0] == 13) || (x[0] == 12 && y[0] == 13) || (x[0] == 13 && y[0] == 13)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 's';
			}
			if (input == 'd') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);

				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] + 1;
				if (x[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 4 && y[0] == 4) || (x[0] == 4 && y[0] == 5) || (x[0] == 5 && y[0] == 10) || (x[0] == 5 && y[0] == 11) || (x[0] == 5 && y[0] == 12) ||
					(x[0] == 9 && y[0] == 5) || (x[0] == 9 && y[0] == 6) || (x[0] == 11 && y[0] == 13) || (x[0] == 11 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'd';
			}
		}
	}
}

void snake_move_mid() {
	score = 0;
	int last = time(NULL);
	int i = 4;
	int x[100];
	int y[100];
	x[0] = 9;
	y[0] = 9;
	x[1] = 8;
	y[1] = 9;
	x[2] = 7;
	y[2] = 9;
	x[3] = 6;
	y[3] = 9;
	x[4] = 5;
	y[4] = 9;
	char dir = 'd';
	char input = 'e';
	EnterCriticalSection(&cr);
	gotoxy(-1, -1);
	ScoreColorOutput();
	LeaveCriticalSection(&cr);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
		srand(time(NULL));
		if (x[0] == fruitx && y[0] == fruity) {
			if (i <= 100) {
				i++;
			}
			int cur = time(NULL);
			if (cur - last <= 1) {
				score *= 2;
				fruitsound();
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 2) {
				score += 20;
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 3) {
				score += 15;
				fruitsound();
			}
			else {
				score += 10;
				soundcount = 0;
				fruitsound();
			}
			time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			EnterCriticalSection(&cr);
			Coord fruitxy = fruit();
			fruity = fruitxy.y;
			fruitx = fruitxy.x;
			gotoxy(fruitxy.x, fruitxy.y);
			FruitColorOutput();
			gotoxy(-1, -1);
			ScoreColorOutput();
			LeaveCriticalSection(&cr);

		}
		for (int j = 1; j <= i; j++) {
			if (x[j] == fruitx && y[j] == fruity) {
				EnterCriticalSection(&cr);
				Coord fruitxy = fruit();
				fruitx = fruitxy.x;
				fruity = fruitxy.y;
				gotoxy(fruitx, fruity);
				FruitColorOutput();
				LeaveCriticalSection(&cr);
			}
		}
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] - 1;
				if (y[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 3) || (x[0] == 4 && y[0] == 3) || (x[0] == 5 && y[0] == 5) || (x[0] == 8 && y[0] == 7) || (x[0] == 9 && y[0] == 4) ||
					(x[0] == 10 && y[0] == 4) || (x[0] == 11 && y[0] == 4) || (x[0] == 12 && y[0] == 4) || (x[0] == 4 && y[0] == 11) || (x[0] == 5 && y[0] == 10) ||
					(x[0] == 6 && y[0] == 10) || (x[0] == 7 && y[0] == 10) || (x[0] == 7 && y[0] == 14) || (x[0] == 8 && y[0] == 14) || (x[0] == 9 && y[0] == 14) ||
					(x[0] == 10 && y[0] == 14) || (x[0] == 11 && y[0] == 14) || (x[0] == 12 && y[0] == 14) || (x[0] == 14 && y[0] == 10)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'w';
			}
			if (input == 'a') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] - 1;
				if (x[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 5 && y[0] == 3) || (x[0] == 5 && y[0] == 4) || (x[0] == 5 && y[0] == 5) || (x[0] == 12 && y[0] == 4) || (x[0] == 8 && y[0] == 5) ||
					(x[0] == 8 && y[0] == 6) || (x[0] == 8 && y[0] == 7) || (x[0] == 14 && y[0] == 6) || (x[0] == 14 && y[0] == 7) || (x[0] == 14 && y[0] == 8) ||
					(x[0] == 14 && y[0] == 9) || (x[0] == 14 && y[0] == 10) || (x[0] == 4 && y[0] == 8) || (x[0] == 4 && y[0] == 9) || (x[0] == 7 && y[0] == 10) ||
					(x[0] == 4 && y[0] == 11) || (x[0] == 11 && y[0] == 9) || (x[0] == 11 && y[0] == 10) || (x[0] == 11 && y[0] == 11) || (x[0] == 11 && y[0] == 12) ||
					(x[0] == 11 && y[0] == 13) || (x[0] == 12 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'a';
			}
			if (input == 's') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] + 1;
				if (y[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 3) || (x[0] == 4 && y[0] == 3) || (x[0] == 5 && y[0] == 3) || (x[0] == 8 && y[0] == 4) || (x[0] == 9 && y[0] == 4) ||
					(x[0] == 10 && y[0] == 4) || (x[0] == 11 && y[0] == 4) || (x[0] == 12 && y[0] == 4) || (x[0] == 4 && y[0] == 8) || (x[0] == 5 && y[0] == 10) ||
					(x[0] == 6 && y[0] == 10) || (x[0] == 7 && y[0] == 10) || (x[0] == 14 && y[0] == 6) || (x[0] == 7 && y[0] == 14) || (x[0] == 8 && y[0] == 14) ||
					(x[0] == 9 && y[0] == 14) || (x[0] == 10 && y[0] == 14) || (x[0] == 11 && y[0] == 9) || (x[0] == 12 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 's';
			}
			if (input == 'd') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] + 1;
				if (x[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 3) || (x[0] == 5 && y[0] == 4) || (x[0] == 5 && y[0] == 5) || (x[0] == 8 && y[0] == 4) || (x[0] == 8 && y[0] == 5) ||
					(x[0] == 8 && y[0] == 6) || (x[0] == 8 && y[0] == 7) || (x[0] == 14 && y[0] == 6) || (x[0] == 14 && y[0] == 7) || (x[0] == 14 && y[0] == 8) ||
					(x[0] == 14 && y[0] == 9) || (x[0] == 14 && y[0] == 10) || (x[0] == 4 && y[0] == 8) || (x[0] == 4 && y[0] == 9) || (x[0] == 4 && y[0] == 10) ||
					(x[0] == 4 && y[0] == 11) || (x[0] == 11 && y[0] == 9) || (x[0] == 11 && y[0] == 10) || (x[0] == 11 && y[0] == 11) || (x[0] == 11 && y[0] == 12) ||
					(x[0] == 11 && y[0] == 13) || (x[0] == 7 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'd';
			}
		}
	}
}

void snake_move_high() {
	score = 0;
	int last = time(NULL);
	int i = 4;
	int x[100];
	int y[100];
	x[0] = 11;
	y[0] = 8;
	x[1] = 10;
	y[1] = 8;
	x[2] = 9;
	y[2] = 8;
	x[3] = 8;
	y[3] = 8;
	x[4] = 7;
	y[4] = 8;
	char dir = 'd';
	char input = 'e';
	EnterCriticalSection(&cr);
	gotoxy(-1, -1);
	ScoreColorOutput();
	LeaveCriticalSection(&cr);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
		srand(time(NULL));
		if (x[0] == fruitx1 && y[0] == fruity1) {
			if (i <= 100) {
				i++;
			}
			int cur = time(NULL);
			if (cur - last <= 1) {
				score *= 2;
				fruitsound();
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 2) {
				score += 20;
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 3) {
				score += 15;
				fruitsound();
			}
			else {
				score += 10;
				soundcount = 0;
				fruitsound();
			}
			time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			EnterCriticalSection(&cr);
			Coord fruit1xy = fruit();
			fruity1 = fruit1xy.y;
			fruitx1 = fruit1xy.x;
			gotoxy(fruit1xy.x, fruit1xy.y);
			FruitColorOutput();
			gotoxy(-1, -1);
			ScoreColorOutput();
			LeaveCriticalSection(&cr);
		}
		for (int j = 1; j <= i; j++) {
			if (x[j] == fruitx1 && y[j] == fruity1) {
				EnterCriticalSection(&cr);
				Coord fruitxy = fruit();
				fruitx1 = fruitxy.x;
				fruity1 = fruitxy.y;
				gotoxy(fruitx1, fruity1);
				FruitColorOutput();
				LeaveCriticalSection(&cr);
			}
		}
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] - 1;
				if (y[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 4) || (x[0] == 4 && y[0] == 3) || (x[0] == 7 && y[0] == 2) || (x[0] == 8 && y[0] == 3) || (x[0] == 9 && y[0] == 2) ||
					(x[0] == 10 && y[0] == 2) || (x[0] == 11 && y[0] == 2) || (x[0] == 12 && y[0] == 2) || (x[0] == 2 && y[0] == 6) || (x[0] == 4 && y[0] == 7) ||
					(x[0] == 5 && y[0] == 6) || (x[0] == 8 && y[0] == 6) || (x[0] == 9 && y[0] == 6) || (x[0] == 10 && y[0] == 6) || (x[0] == 11 && y[0] == 7) ||
					(x[0] == 14 && y[0] == 6) || (x[0] == 15 && y[0] == 6) || (x[0] == 3 && y[0] == 10) || (x[0] == 6 && y[0] == 9) || (x[0] == 7 && y[0] == 9) ||
					(x[0] == 8 && y[0] == 9) || (x[0] == 9 && y[0] == 9) || (x[0] == 3 && y[0] == 12) || (x[0] == 4 && y[0] == 14) || (x[0] == 5 && y[0] == 12) ||
					(x[0] == 6 && y[0] == 12) || (x[0] == 9 && y[0] == 11) || (x[0] == 10 && y[0] == 11) || (x[0] == 11 && y[0] == 11) || (x[0] == 12 && y[0] == 11) ||
					(x[0] == 13 && y[0] == 11) || (x[0] == 15 && y[0] == 12) || (x[0] == 9 && y[0] == 13) || (x[0] == 7 && y[0] == 15) || (x[0] == 8 && y[0] == 15) ||
					(x[0] == 9 && y[0] == 15) || (x[0] == 12 && y[0] == 15) || (x[0] == 14 && y[0] == 14) || (x[0] == 15 && y[0] == 14) || (x[0] == 16 && y[0] == 14)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'w';
			}
			if (input == 'a') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);
				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] - 1;
				if (x[0] == 1) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 4) || (x[0] == 4 && y[0] == 3) || (x[0] == 2 && y[0] == 6) || (x[0] == 4 && y[0] == 7) || (x[0] == 5 && y[0] == 5) ||
					(x[0] == 5 && y[0] == 6) || (x[0] == 11 && y[0] == 6) || (x[0] == 11 && y[0] == 5) || (x[0] == 11 && y[0] == 7) || (x[0] == 14 && y[0] == 4) ||
					(x[0] == 14 && y[0] == 5) || (x[0] == 15 && y[0] == 6) || (x[0] == 12 && y[0] == 2) || (x[0] == 8 && y[0] == 3) || (x[0] == 3 && y[0] == 9) ||
					(x[0] == 9 && y[0] == 9) || (x[0] == 3 && y[0] == 10) || (x[0] == 6 && y[0] == 12) || (x[0] == 4 && y[0] == 13) || (x[0] == 4 && y[0] == 14) ||
					(x[0] == 12 && y[0] == 10) || (x[0] == 13 && y[0] == 11) || (x[0] == 15 && y[0] == 9) || (x[0] == 15 && y[0] == 10) || (x[0] == 15 && y[0] == 11) ||
					(x[0] == 15 && y[0] == 12) || (x[0] == 9 && y[0] == 13) || (x[0] == 9 && y[0] == 15) || (x[0] == 2 && y[0] == 15) || (x[0] == 2 && y[0] == 16) ||
					(x[0] == 12 && y[0] == 13) || (x[0] == 12 && y[0] == 14) || (x[0] == 12 && y[0] == 15) || (x[0] == 5 && y[0] == 16)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'a';
			}
			if (input == 's') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);

				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				y[0] = y[0] + 1;
				if (y[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 3) || (x[0] == 4 && y[0] == 3) || (x[0] == 2 && y[0] == 6) || (x[0] == 4 && y[0] == 6) || (x[0] == 5 && y[0] == 5) ||
					(x[0] == 8 && y[0] == 6) || (x[0] == 9 && y[0] == 6) || (x[0] == 10 && y[0] == 6) || (x[0] == 11 && y[0] == 5) || (x[0] == 14 && y[0] == 4) ||
					(x[0] == 15 && y[0] == 6) || (x[0] == 3 && y[0] == 9) || (x[0] == 6 && y[0] == 9) || (x[0] == 7 && y[0] == 9) || (x[0] == 8 && y[0] == 9) ||
					(x[0] == 9 && y[0] == 9) || (x[0] == 3 && y[0] == 12) || (x[0] == 4 && y[0] == 12) || (x[0] == 5 && y[0] == 12) || (x[0] == 6 && y[0] == 12) ||
					(x[0] == 9 && y[0] == 11) || (x[0] == 10 && y[0] == 11) || (x[0] == 11 && y[0] == 11) || (x[0] == 12 && y[0] == 10) || (x[0] == 13 && y[0] == 11) ||
					(x[0] == 15 && y[0] == 9) || (x[0] == 9 && y[0] == 13) || (x[0] == 7 && y[0] == 15) || (x[0] == 8 && y[0] == 15) || (x[0] == 9 && y[0] == 15) ||
					(x[0] == 12 && y[0] == 13) || (x[0] == 14 && y[0] == 14) || (x[0] == 15 && y[0] == 14) || (x[0] == 16 && y[0] == 14) || (x[0] == 5 && y[0] == 16) ||
					(x[0] == 2 && y[0] == 15)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);

				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 's';
			}
			if (input == 'd') {
				EnterCriticalSection(&cr);
				gotoxy(x[i], y[i]);
				printf(" ");
				LeaveCriticalSection(&cr);

				for (int j = i; j >= 1; j--) {
					x[j] = x[j - 1];
					y[j] = y[j - 1];
				}
				x[0] = x[0] + 1;
				if (x[0] == 17) {
					gameover();
					break;
				}
				for (int j = 4; j <= i; j++) {
					if (x[0] == x[j] && y[0] == y[j]) {
						gameover();
						break;
					}
				}
				if ((x[0] == 3 && y[0] == 3) || (x[0] == 3 && y[0] == 4) || (x[0] == 7 && y[0] == 2) || (x[0] == 4 && y[0] == 7) || (x[0] == 5 && y[0] == 5) ||
					(x[0] == 4 && y[0] == 6) || (x[0] == 8 && y[0] == 6) || (x[0] == 11 && y[0] == 5) || (x[0] == 11 && y[0] == 7) || (x[0] == 14 && y[0] == 4) ||
					(x[0] == 14 && y[0] == 5) || (x[0] == 14 && y[0] == 6) || (x[0] == 8 && y[0] == 3) || (x[0] == 3 && y[0] == 9) || (x[0] == 6 && y[0] == 9) ||
					(x[0] == 3 && y[0] == 10) || (x[0] == 3 && y[0] == 12) || (x[0] == 4 && y[0] == 13) || (x[0] == 4 && y[0] == 14) || (x[0] == 12 && y[0] == 10) ||
					(x[0] == 9 && y[0] == 11) || (x[0] == 15 && y[0] == 9) || (x[0] == 15 && y[0] == 10) || (x[0] == 15 && y[0] == 11) || (x[0] == 15 && y[0] == 12) ||
					(x[0] == 9 && y[0] == 13) || (x[0] == 7 && y[0] == 15) || (x[0] == 12 && y[0] == 14) || (x[0] == 12 && y[0] == 13) || (x[0] == 12 && y[0] == 15) ||
					(x[0] == 14 && y[0] == 14) || (x[0] == 5 && y[0] == 16)) {
					gameover();
					break;
				}
				EnterCriticalSection(&cr);
				gotoxy(x[0], y[0]);
				printf("a");
				LeaveCriticalSection(&cr);
				for (int j = 1; j <= i; j++) {
					EnterCriticalSection(&cr);
					gotoxy(x[j], y[j]);
					printf("*");
					LeaveCriticalSection(&cr);
				}
				dir = 'd';
			}
		}
	}
}

void stopwatch() {
	clock_t s, n;
	s = clock();

	while (over != 1) {
		EnterCriticalSection(&cr);
		n = clock();
		cursor(0);
		gotoxy(14, 0);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		printf(" %d : %02d", ((n - s) / 1000) / 60, ((n - s) / 1000) % 60);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		LeaveCriticalSection(&cr);
		Sleep(1000);
	}
	nowrec.minute = ((n - s) / 1000) / 60;
	nowrec.sec = ((n - s) / 1000) % 60;
	return;
}

void fruitsound()
{
	switch (soundcount % 7) {
	case 0: Beep(C4, 250); break;
	case 1: Beep(D4, 250); break;
	case 2: Beep(E4, 250); break;
	case 3: Beep(F4, 250); break;
	case 4: Beep(G4, 250); break;
	case 5: Beep(A4, 250); break;
	default: Beep(B4, 250); break;
	}
}

void FruitColorOutput() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("@");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void ScoreColorOutput()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("score = %d", score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void ordinalnum(int num)
{
	switch (num) {
	case 1: printf("%dst\n", num); break;
	case 2: printf("%dnd\n", num); break;
	case 3: printf("%drd\n", num); break;
	default: printf("%dth\n", num); break;
	}
}
