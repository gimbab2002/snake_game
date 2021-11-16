#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y);
int getCommand();                  //키보드 입력

int main(void) {
	char input;
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
	while (1) {
		int getCommand();
		input = getCommand();
		if (input == 'p') {
			system("cls");
			printf("GAMEOVER");
			return 0;
		}
	}
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = {x*2, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int getCommand() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
};
