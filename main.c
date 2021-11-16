#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y);          //입력 위치 설정 함수
void make_stage();                  //스테이지 구현 함수
int getCommand();                   //키보드 입력 함수

int main(void) {
	char input;
	make_stage();
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { x * 2, y };
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