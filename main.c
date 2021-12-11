#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<process.h>
#include<stdbool.h>
#include<string.h>
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
int getCommand();                   //키보드 입력
void gameover();            //게임오버 화면
void startscr();                    //시작 화면
void snake_move_low();                  //뱀의 움직임
void snake_move_mid();                  //뱀의 움직임
void snake_move_high();                 //뱀의 움직임
void rank_call();					//랭킹 표시
void rankrecord();                  //랭킹 기록
void cursor(int i);             //커서 상태 변경
void stopwatch();               //스톱워치 보여주기
void wall();                //장애물
Coord fruit();
bool isWall(Coord coord);
void fruitsound();			//fruit을 빨리 먹으면 소리 출력
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
	gotoxy(x, y);
	printf("#");
}

void make_stage_low() {
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
    Coord fruit2xy = fruit();
    fruity2 = fruit2xy.y;
    fruitx2 = fruit2xy.x;
    gotoxy(fruitx2, fruity2);   // Feeding 2+rand()%15 into gotoxy
    printf("@");
 }

void make_stage_mid() {
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
	printf("@");
}

void make_stage_high() {
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
    Coord fruit1xy = fruit();
    fruity1 = fruit1xy.y;
    fruitx1 = fruit1xy.x;
    gotoxy(fruitx1, fruity1);   // Feeding 2+rand()%15 into gotoxy
    printf("@");
}

int getCommand() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}

void cursor(int i) {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void rank_call() {
	FILE* rank;
	record reading;
	if (fopen_s(&rank, "rank.txt", "r") != 0) printf("no record\n");
	else {
		printf("\n");

		while (fscanf(rank, "%s %d %d : %d\n", reading.name, &reading.score, &reading.minute, &reading.sec) != EOF) {
			printf("%s\nscore>> %d\ntime>> %d : %d\n\n", reading.name, reading.score, reading.minute, reading.sec);
			Sleep(1000);
		}
		fclose(rank);
		printf("\n");
	}
}

void rankrecord() {
	FILE* rank;
	if ((rank = fopen("rank.txt", "r")) == NULL)		//if there's not rank.txt file, it will create the file.
	{
		rank = fopen("rank.txt", "w+");
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
	while (cur != NULL) {
		pre = cur;
		cur = cur->next;
	}
	if (pre->score <= nowrec.score) {				//recognizing whether newrec is in top ten or not by comparing with the smallest score.
		char input;
	re:
		printf("you are in top 10. Do you wanna record your record? if so, press 'y'. if not press 'n'\n");		//from here, TUI strating.
		input = _getch();
		if (input == 'y') {
		rerun:
			printf("enter your name: ");
			gets_s(nowrec.name, sizeof(nowrec.name));
			if (strlen(nowrec.name) < 3) {
				printf("name must be at least 3 words...\n\n");
				goto rerun;
			}
			while (1) {
				printf("your name is %s.\nyour score is %d.\nyour clear time is %d : %d.\n\n", nowrec.name, nowrec.score, nowrec.minute, nowrec.sec);
				printf("if your name is incorrect, press n to correct\nif not, press y to continue...\n\n");
				input = _getch();
				if (input == 'n') goto rerun;
				else if (input == 'y') break;
				else printf("wrong input\n\n");
			}
		}
		else if (input == 'n') {
			return;
		}
		else {
			printf("Wrong input. Press any key to try again\n\n");
			_kbhit();
			goto re;
		}
		fclose(rank);
		rank = fopen("rank.txt", "w");
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
			system("cls");
			cursor(0);
			make_stage_high();
			HANDLE thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(1);
			HANDLE thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_high, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
		}
		if (lev == 'm') {
			system("cls");
			cursor(0);
			make_stage_mid();
			HANDLE thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(1);
			HANDLE thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_mid, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
		}
		if (lev == 'l') {
			system("cls");
			cursor(0);
			make_stage_low();
			HANDLE thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)stopwatch, NULL, 0, NULL);
			Sleep(1);
			HANDLE thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_low, NULL, 0, NULL);
			WaitForSingleObject(thread2, INFINITE);
		}
		else {
			printf("wrong selection\n");
			printf("press enter to continue...");
			while (getchar() != '\n');
			goto select;
		}
	}
	else if (input == 'r') {
		rank_call();
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
	cursor(1);
	nowrec.score = score;
	rankrecord();
	printf("press any key to back to title...");
	_getch();
	startscr();
}

void snake_move_low() {
	score = 0;
	int last = time(NULL);
	int x = 9, y = 9;
	int x1 = 8, y1 = 9;
	int x2 = 7, y2 = 9;
	int x3 = 6, y3 = 9;
	int x4 = 5, y4 = 9;
	char dir = 'd';
	char input = 'e';
	gotoxy(-1, -1);
	printf("score = %d", score);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {

		srand(time(NULL));
		if (x == fruitx2 && y == fruity2) {
			int cur = time(NULL);
			if (cur - last <= 0.9) {
				score *= 2;
				fruitsound();
				soundcount++;
			}
			else if (cur - last <= 1.5) {
				score += 20;
				soundcount = 0;
				fruitsound();
			}
			else if (cur - last <= 1.9) {
				score += 15;
				soundcount = 0;
				fruitsound();
			}
			else {
				score += 10;
				soundcount = 0;
				fruitsound();
			}
			time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
            Coord fruit2xy = fruit();
            fruity2 = fruit2xy.y;
            fruitx2 = fruit2xy.x;
            gotoxy(fruit2xy.x, fruit2xy.y);
            printf("@");
            gotoxy(-1, -1);
            printf("score = %d", score);

		}
		if ((x1 == fruitx2 && y1 == fruity2) || (x2 == fruitx2 && y2 == fruity2) || (x3 == fruitx2 && y3 == fruity2) || (x4 == fruitx2 && y4 == fruity2)) {
            Coord fruit2xy = fruit();
            fruity2 = fruit2xy.y;
            fruitx2 = fruit2xy.x;
            gotoxy(fruit2xy.x, fruit2xy.y);
            printf("@");
		}
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y - 1;
				if (y == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 4 && y == 5) || (x == 5 && y == 5) || (x == 5 && y == 12) || (x == 6 && y == 12) || (x == 9 && y == 6) ||
					(x == 10 && y == 6) || (x == 11 && y == 14) || (x == 12 && y == 14) || (x == 13 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'w';
			}
			if (input == 'a') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x - 1;
				if (x == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 5 && y == 4) || (x == 5 && y == 5) || (x == 6 && y == 10) || (x == 6 && y == 11) || (x == 6 && y == 12) ||
					(x == 10 && y == 5) || (x == 10 && y == 6) || (x == 13 && y == 13) || (x == 13 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'a';
			}
			if (input == 's') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y + 1;
				if (y == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 4 && y == 4) || (x == 5 && y == 4) || (x == 5 && y == 10) || (x == 6 && y == 11) || (x == 9 && y == 5) ||
					(x == 10 && y == 5) || (x == 11 && y == 13) || (x == 12 && y == 13) || (x == 13 && y == 13)) {
					gameover();
					break;
				}
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
				dir = 's';
			}
			if (input == 'd') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x + 1;
				if (x == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 4 && y == 4) || (x == 4 && y == 5) || (x == 5 && y == 10) || (x == 5 && y == 11) || (x == 5 && y == 12) ||
					(x == 9 && y == 5) || (x == 9 && y == 6) || (x == 11 && y == 13) || (x == 11 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'd';
			}
		}
	}
}

void snake_move_mid() {
	score = 0;
	int last = time(NULL);
	int x = 9, y = 9;
	int x1 = 8, y1 = 9;
	int x2 = 7, y2 = 9;
	int x3 = 6, y3 = 9;
	int x4 = 5, y4 = 9;
	char dir = 'd';
	char input = 'e';
	gotoxy(-1, -1);
	printf("score = %d", score);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
		srand(time(NULL));
		if (x == fruitx && y == fruity) {
			int cur = time(NULL);
			if (cur - last <= 0.9) {
				fruitsound();
				soundcount++;
				score *= 2;
			}
			else if (cur - last <= 1.5) {
				score += 20;
				soundcount = 0;
				fruitsound();
			}
			else if (cur - last <= 1.9) {
				score += 15;
				soundcount = 0;
				fruitsound();
			}
			else {
				score += 10;
				soundcount = 0;
				fruitsound();
			}
			time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			Coord fruitxy = fruit();
			fruity = fruitxy.y;
			fruitx = fruitxy.x;
			gotoxy(fruitxy.x, fruitxy.y);
			printf("@");
			gotoxy(-1, -1);
			printf("score = %d", score);

		}
		if ((x1 == fruitx && y1 == fruity) || (x2 == fruitx && y2 == fruity) || (x3 == fruitx && y3 == fruity) || (x4 == fruitx && y4 == fruity)) {
			Coord fruitxy = fruit();
			fruitx = fruitxy.x;
			fruity = fruitxy.y;
			gotoxy(fruitx, fruity);
			printf("@");
		}
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y - 1;
				if (y == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 3) || (x == 4 && y == 3) || (x == 5 && y == 5) || (x == 8 && y == 7) || (x == 9 && y == 4) ||
					(x == 10 && y == 4) || (x == 11 && y == 4) || (x == 12 && y == 4) || (x == 4 && y == 11) || (x == 5 && y == 10) ||
					(x == 6 && y == 10) || (x == 7 && y == 10) || (x == 7 && y == 14) || (x == 8 && y == 14) || (x == 9 && y == 14) ||
					(x == 10 && y == 14) || (x == 11 && y == 14) || (x == 12 && y == 14) || (x == 14 && y == 10)) {
					gameover();
					break;
				}
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
				dir = 'w';
			}
			if (input == 'a') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x - 1;
				if (x == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 5 && y == 3) || (x == 5 && y == 4) || (x == 5 && y == 5) || (x == 12 && y == 4) || (x == 8 && y == 5) ||
					(x == 8 && y == 6) || (x == 8 && y == 7) || (x == 14 && y == 6) || (x == 14 && y == 7) || (x == 14 && y == 8) ||
					(x == 14 && y == 9) || (x == 14 && y == 10) || (x == 4 && y == 8) || (x == 4 && y == 9) || (x == 7 && y == 10) ||
					(x == 4 && y == 11) || (x == 11 && y == 9) || (x == 11 && y == 10) || (x == 11 && y == 11) || (x == 11 && y == 12) ||
					(x == 11 && y == 13) || (x == 12 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'a';
			}
			if (input == 's') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y + 1;
				if (y == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 3) || (x == 4 && y == 3) || (x == 5 && y == 3) || (x == 8 && y == 4) || (x == 9 && y == 4) ||
					(x == 10 && y == 4) || (x == 11 && y == 4) || (x == 12 && y == 4) || (x == 4 && y == 8) || (x == 5 && y == 10) ||
					(x == 6 && y == 10) || (x == 7 && y == 10) || (x == 14 && y == 6) || (x == 7 && y == 14) || (x == 8 && y == 14) ||
					(x == 9 && y == 14) || (x == 10 && y == 14) || (x == 11 && y == 9) || (x == 12 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 's';
			}
			if (input == 'd') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x + 1;
				if (x == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 3) || (x == 5 && y == 4) || (x == 5 && y == 5) || (x == 8 && y == 4) || (x == 8 && y == 5) ||
					(x == 8 && y == 6) || (x == 8 && y == 7) || (x == 14 && y == 6) || (x == 14 && y == 7) || (x == 14 && y == 8) ||
					(x == 14 && y == 9) || (x == 14 && y == 10) || (x == 4 && y == 8) || (x == 4 && y == 9) || (x == 4 && y == 10) ||
					(x == 4 && y == 11) || (x == 11 && y == 9) || (x == 11 && y == 10) || (x == 11 && y == 11) || (x == 11 && y == 12) ||
					(x == 11 && y == 13) || (x == 7 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'd';
			}
		}
	}
}

void snake_move_high() {
    score = 0;
    int last = time(NULL);
	int x = 11, y = 8;
	int x1 = 10, y1 = 8;
	int x2 = 9, y2 = 8;
	int x3 = 8, y3 = 8;
	int x4 = 7, y4 = 8;
	char dir = 'd';
	char input = 'e';
    gotoxy(-1, -1);
    printf("score = %d", score);
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
        srand(time(NULL));
           if (x == fruitx1 && y == fruity1) {
              int cur = time(NULL);
              if (cur - last <= 1.2) {
                 fruitsound();
                 soundcount++;
                 score *= 2;
              }
              else if (cur - last <= 1.7) {
                 score += 20;
                 soundcount = 0;
                 fruitsound();
              }
              else if (cur - last <= 2) {
                 score += 15;
                 soundcount = 0;
                 fruitsound();
              }
              else {
                 score += 10;
                 soundcount = 0;
                 fruitsound();
              }
              time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
              Coord fruit1xy = fruit();
              fruity1 = fruit1xy.y;
              fruitx1 = fruit1xy.x;
              gotoxy(fruit1xy.x, fruit1xy.y);
              printf("@");
              gotoxy(-1, -1);
              printf("score = %d", score);

           }
           if ((x1 == fruitx1 && y1 == fruity1) || (x2 == fruitx1 && y2 == fruity1) || (x3 == fruitx1 && y3 == fruity1) || (x4 == fruitx1 && y4 == fruity1)) {
              Coord fruit1xy = fruit();
              fruitx1 = fruit1xy.x;
              fruity1 = fruit1xy.y;
              gotoxy(fruitx1, fruity1);
              printf("@");
           }
		input = _getch();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y - 1;
				if (y == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 4) || (x == 4 && y == 3) || (x == 7 && y == 2) || (x == 8 && y == 3) || (x == 9 && y == 2) ||
					(x == 10 && y == 2) || (x == 11 && y == 2) || (x == 12 && y == 2) || (x == 2 && y == 6) || (x == 4 && y == 7) ||
					(x == 5 && y == 6) || (x == 8 && y == 6) || (x == 9 && y == 6) || (x == 10 && y == 6) || (x == 11 && y == 7) ||
					(x == 14 && y == 6) || (x == 15 && y == 6) || (x == 3 && y == 10) || (x == 6 && y == 9) || (x == 7 && y == 9) ||
					(x == 8 && y == 9) || (x == 9 && y == 9) || (x == 3 && y == 12) || (x == 4 && y == 14) || (x == 5 && y == 12) ||
					(x == 6 && y == 12) || (x == 9 && y == 11) || (x == 10 && y == 11) || (x == 11 && y == 11) || (x == 12 && y == 11) ||
					(x == 13 && y == 11) || (x == 15 && y == 12) || (x == 9 && y == 13) || (x == 7 && y == 15) || (x == 8 && y == 15) ||
					(x == 9 && y == 15) || (x == 12 && y == 15) || (x == 14 && y == 14) || (x == 15 && y == 14) || (x == 16 && y == 14)) {
					gameover();
					break;
				}
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
				dir = 'w';
			}
			if (input == 'a') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x - 1;
				if (x == 1) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 4) || (x == 4 && y == 3) || (x == 2 && y == 6) || (x == 4 && y == 7) || (x == 5 && y == 5) ||
					(x == 5 && y == 6) || (x == 11 && y == 6) || (x == 11 && y == 5) || (x == 11 && y == 7) || (x == 14 && y == 4) ||
					(x == 14 && y == 5) || (x == 15 && y == 6) || (x == 12 && y == 2) || (x == 8 && y == 3) || (x == 3 && y == 9) ||
					(x == 9 && y == 9) || (x == 3 && y == 10) || (x == 6 && y == 12) || (x == 4 && y == 13) || (x == 4 && y == 14) ||
					(x == 12 && y == 10) || (x == 13 && y == 11) || (x == 15 && y == 9) || (x == 15 && y == 10) || (x == 15 && y == 11) ||
					(x == 15 && y == 12) || (x == 9 && y == 13) || (x == 9 && y == 15) || (x == 2 && y == 15) || (x == 2 && y == 16) ||
					(x == 12 && y == 13) || (x == 12 && y == 14) || (x == 12 && y == 15) || (x == 5 && y == 16)) {
					gameover();
					break;
				}
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
				dir = 'a';
			}
			if (input == 's') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				y = y + 1;
				if (y == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 3) || (x == 4 && y == 3) || (x == 2 && y == 6) || (x == 4 && y == 6) || (x == 5 && y == 5) ||
					(x == 8 && y == 6) || (x == 9 && y == 6) || (x == 10 && y == 6) || (x == 11 && y == 5) || (x == 14 && y == 4) ||
					(x == 15 && y == 6) || (x == 3 && y == 9) || (x == 6 && y == 9) || (x == 7 && y == 9) || (x == 8 && y == 9) ||
					(x == 9 && y == 9) || (x == 3 && y == 12) || (x == 4 && y == 12) || (x == 5 && y == 12) || (x == 6 && y == 12) ||
					(x == 9 && y == 11) || (x == 10 && y == 11) || (x == 11 && y == 11) || (x == 12 && y == 10) || (x == 13 && y == 11) ||
					(x == 15 && y == 9) || (x == 9 && y == 13) || (x == 7 && y == 15) || (x == 8 && y == 15) || (x == 9 && y == 15) ||
					(x == 12 && y == 13) || (x == 14 && y == 14) || (x == 15 && y == 14) || (x == 16 && y == 14) || (x == 5 && y == 16) ||
					(x == 2 && y == 15)) {
					gameover();
					break;
				}
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
				dir = 's';
			}
			if (input == 'd') {
				gotoxy(x4, y4);
				printf(" ");
				x4 = x3; x3 = x2; x2 = x1; x1 = x;
				y4 = y3; y3 = y2; y2 = y1; y1 = y;
				x = x + 1;
				if (x == 17) {
					gameover();
					break;
				}
				if (x == x4 && y == y4) {
					gameover();
					break;
				}
				if ((x == 3 && y == 3) || (x == 3 && y == 4) || (x == 7 && y == 2) || (x == 4 && y == 7) || (x == 5 && y == 5) ||
					(x == 4 && y == 6) || (x == 8 && y == 6) || (x == 11 && y == 5) || (x == 11 && y == 7) || (x == 14 && y == 4) ||
					(x == 14 && y == 5) || (x == 14 && y == 6) || (x == 8 && y == 3) || (x == 3 && y == 9) || (x == 6 && y == 9) ||
					(x == 3 && y == 10) || (x == 3 && y == 12) || (x == 4 && y == 13) || (x == 4 && y == 14) || (x == 12 && y == 10) ||
					(x == 9 && y == 11) || (x == 15 && y == 9) || (x == 15 && y == 10) || (x == 15 && y == 11) || (x == 15 && y == 12) ||
					(x == 9 && y == 13) || (x == 7 && y == 15) || (x == 12 && y == 14) || (x == 12 && y == 13) || (x == 12 && y == 15) ||
					(x == 14 && y == 14) || (x == 5 && y == 16)) {
					gameover();
					break;
				}
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
				dir = 'd';
			}
		}
	}
}

void stopwatch() {
	clock_t s, n;
	s = clock();
	while (1) {
		n = clock();
		cursor(0);
		gotoxy(14, 0);
		printf(" %d : %d", ((n - s) / 1000) / 60, ((n - s) / 1000) % 60);
		if (over == 1) {
			break;
		}
		Sleep(1000);
	}
	gotoxy(14, 0);
	printf(" **** ");
	nowrec.minute = ((n - s) / 1000) / 60;
	nowrec.sec = ((n - s) / 1000) % 60;
	return;
}

void fruitsound()
{
	switch (soundcount) {
	case 0: Beep(C4, 250); break;
	case 1: Beep(D4, 250); break;
	case 2: Beep(E4, 250); break;
	case 3: Beep(F4, 250); break;
	case 4: Beep(G4, 250); break;
	case 5: Beep(A4, 250); break;
	default: Beep(B4, 250); break;
	}
}
