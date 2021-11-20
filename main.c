#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y);          //입력 위치 설정
void make_stage();                  //스테이지 구현
int getCommand();                   //키보드 입력
void gameover();                    //게임오버 화면
void startscr();                    //시작 화면
void snake_move();                  //뱀의 움직임
void rank_call();					//랭킹 표시
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

void startscr()
{
	system("mode con cols=100 lines=40");
	printf("   ******   **    *       *      *    *  ******           ******      *        **    **    ******   \n");
	printf("   *        * *   *      * *     *   *   *                *          * *      *  *  *  *   *        \n");
	printf("   ******   *  *  *     *****    ****    ******           *  ***    *****     *  *  *  *   ******   \n");
	printf("        *   *   * *    *     *   *   *   *                *    *   *     *   *     *    *  *        \n");
	printf("   ******   *    **   *       *  *    *  ******           ******  *       *  *     *    *  ******  \n");
start:
	printf("\npress s to start game\n");
	printf("press r to see ranking\n");
	printf("press x to exit\n:");
	char input = getchar();
	if (input == 's') {
		make_stage();
		snake_move();
	}
	else if (input == 'r') {
		rank_call();
		getchar();
		goto start;
	}
	else if (input == 'x') exit(0);
	else {
		printf("wrong input");
		getchar();
		goto start;
	}
}

void gameover() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("        ******      *        **    **    ******            ****   *       *  ******   *****         \n");
	printf("        *          * *      *  *  *  *   *                *    *   *     *   *        *    *        \n");
	printf("        *  ***    *****     *  *  *  *   ******           *    *    *   *    ******   *****         \n");
	printf("        *    *   *     *   *     *    *  *                *    *     * *     *        *    *        \n");
	printf("        ******  *       *  *     *    *  ******            ****       *      ******   *     *      \n");
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
		getCommand();
		input = getCommand();
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
