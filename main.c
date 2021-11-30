#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

typedef struct RECORD {
	char name[100];
	int score;
	int time;
}record; //이름, 점수, 시간을 저장할 구조체

record nowrec;

void gotoxy(int x, int y);          //입력 위치 설정
void make_stage();                  //스테이지 구현
int getCommand();                   //키보드 입력
void gameover();                    //게임오버 화면
void startscr();                    //시작 화면
void snake_move();                  //뱀의 움직임
void rank_call();					//랭킹 표시
void rankrecord();                  //랭킹 기록
void cursor(int i);             //커서 상태 변경
void time_show();

int main(void) {
	startscr();
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { 30 + x * 2, 10 + y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void make_stage() {
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
	char reading[100];
	if (fopen_s(&rank, "rank.txt", "r") != 0) printf("no record\n");
	else {
		printf("\n");
		while ((fgets(reading, 100, rank) != NULL)) printf("%s", reading);
		fclose(rank);
		printf("\n");
	}

}

void rankrecord() {
	printf("\npress enter to proceed...\n");
	while (getchar() != '\n');
	printf("press r to record your ranking...");
	char input = _getch();
	if (input == 'r') {
		FILE* rank;
		fopen_s(&rank, "rank.txt", "a");
		while (getchar() != '\n');
		printf("enter your name: ");
		gets_s(nowrec.name, sizeof(nowrec.name));
		fprintf(rank, "%s %d %d\n", nowrec.name, nowrec.score, nowrec.time);
		fclose(rank);
	}
}

void startscr()
{
	system("mode con cols=100 lines=40");
start:
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
		system("cls");
		cursor(0);
		make_stage();
		snake_move();
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
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("        ******      *        **    **    ******            ****   *       *  ******   *****         \n");
	printf("        *          * *      *  *  *  *   *                *    *   *     *   *        *    *        \n");
	printf("        *  ***    *****     *  *  *  *   ******           *    *    *   *    ******   *****         \n");
	printf("        *    *   *     *   *    **    *  *                *    *     * *     *        *    *        \n");
	printf("        ******  *       *  *    **    *  ******            ****       *      ******   *     *      \n");
	cursor(1);
	rankrecord();
}

void snake_move() {
	int x = 9, y = 9;
	int x1 = 8, y1 = 9;
	int x2 = 7, y2 = 9;
	int x3 = 6, y3 = 9;
	int x4 = 5, y4 = 9;
	char dir = 'd';
	char input = 'e';
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
	while (1) {
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
		if (input == 'p') {
			gameover();
			break;
		}
	}
}
void time_show() {   //아직 미완성(not completed) 
	clock_t s, n;
	s = clock();

	while (1) {
		while (1) {
			n = clock();
			printf("\r");               //커서 왼쪽 끝으로 이동(스테이지의 위치에 따라 수정할 예정)
			printf("Time-\t %d : %d : %d ", ((n - s) / 1000) / 60, ((n - s) / 1000) % 60, (n - s) % 1000);
			if (_kbhit()) break; //키보드 입력이 들어오면 break;
		}

		if (_getch() == 'p') {          //만약 그것이 p이면
			printf("\rTime-\t %d : %d : %d ", ((n - s) / 1000) / 60, ((n - s) / 1000) % 60, (n - s) % 1000);
			_getch();
		}
		else break;

		s = s + (clock() - n);

	}

	printf("\rTime-\t %d : %d : %d ", ((n - s) / 1000) / 60, ((n - s) / 1000) % 60, (n - s) % 1000);

	_getch(); _getch();
	printf("\n\n\n");

	return;
}