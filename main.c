#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y);          //입력 위치 설정 함수
void make_stage();                  //스테이지 구현 함수
int getCommand();                   //키보드 입력 함수
void gameover();                    //게임오버 화면
void startscr();                    //시작 화면
void snake_move();                  //뱀의 움직임

int main(void) {
	startscr();
	make_stage();
	snake_move();
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
};

int getCommand() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
};

void startscr()
{
	system("mode con cols=100 lines=40");
	printf("   ******   **    *       *      *    *  ******           ******      *        **    **    ******   ");
	printf("   *        * *   *      * *     *   *   *                *          * *      *  *  *  *   *        ");
	printf("   ******   *  *  *     *****    ****    ******           *  ***    *****     *  *  *  *   ******   ");
	printf("        *   *   * *    *     *   *   *   *                *    *   *     *   *     *    *  *        ");
	printf("   ******   *    **   *       *  *    *  ******           ******  *       *  *     *    *  ******  \n");
}

void gameover() {
	system("cls");
	printf("        ******      *        **    **    ******            ****   *       *  ******   *****         ");
	printf("        *          * *      *  *  *  *   *                *    *   *     *   *        *    *        ");
	printf("        *  ***    *****     *  *  *  *   ******           *    *    *   *    ******   *****         ");
	printf("        *    *   *     *   *     *    *  *                *    *     * *     *        *    *        ");
	printf("        ******  *       *  *     *    *  ******            ****       *      ******   *     *      \n");
}

void snake_move() {
	int x = 9, y = 9;
	char dir = 'a';
	char input;
	gotoxy(x, y);
	printf("*");
	while (1) {
		getCommand();
		input = getCommand();
		if (input == 'w') {
			if (dir != 's') {
				y = y - 1;
				gotoxy(x, y);
				printf("*");
				dir = 'w';
			}
			else
				continue;
		}
		if (input == 'a') {
			if (dir != 'd') {
				x = x - 1;
				gotoxy(x, y);
				printf("*");
				dir = 'a';
			}
			else
				continue;
		}
		if (input == 's') {
			if (dir != 'w') {
				y = y + 1;
				gotoxy(x, y);
				printf("*");
				dir = 's';
			}
			else
				continue;
		}
		if (input == 'd') {
			if (dir != 'a') {
				x = x + 1;
				gotoxy(x, y);
				printf("*");
				dir = 'd';
			}
			else
				continue;
		}
		if (input == 'p') {
			gameover();
			break;
		}
	}
}
