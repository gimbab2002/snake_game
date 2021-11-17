#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y);          //입력 위치 설정
void make_stage();                  //스테이지 구현
int getCommand();                   //키보드 입력
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
}

int getCommand() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}

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
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("        ******      *        **    **    ******            ****   *       *  ******   *****         ");
	printf("        *          * *      *  *  *  *   *                *    *   *     *   *        *    *        ");
	printf("        *  ***    *****     *  *  *  *   ******           *    *    *   *    ******   *****         ");
	printf("        *    *   *     *   *     *    *  *                *    *     * *     *        *    *        ");
	printf("        ******  *       *  *     *    *  ******            ****       *      ******   *     *      \n");
}

void snake_move() {
	int x = 9, y = 9;
	char dir = 'd';
	char input = 'e';
	gotoxy(x, y);
	printf("*");
	while (1) {
		getCommand();
		input = getCommand();
		if ((dir == 'w' && input != 's') || (dir == 'a' && input != 'd') || (dir == 's' && input != 'w') || (dir == 'd' && input != 'a')) {
			if (input == 'w') {
				y = y - 1;
				if (y == 1) {
					gameover();
					break;
				}
				gotoxy(x, y);
				printf("*");
				dir = 'w';
			}
			if (input == 'a') {
				x = x - 1;
				if (x == 1) {
					gameover();
					break;
				}
				gotoxy(x, y);
				printf("*");
				dir = 'a';
			}
			if (input == 's') {
				y = y + 1;
				if (y == 17) {
					gameover();
					break;
				}
				gotoxy(x, y);
				printf("*");
				dir = 's';
			}
			if (input == 'd') {
				x = x + 1;
				if (x == 17) {
					gameover();
					break;
				}
				gotoxy(x, y);
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
