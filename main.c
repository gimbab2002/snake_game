#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<process.h>
#define A3 220.0000
#define B3 246.9417
#define C4 261.6256
#define D4 293.6648
#define E4 329.6276
#define F4 349.2282
#define G4 391.9954


int height = 17, width = 17;  //dimensions of out field
typedef struct RECORD {
	char name[100];
	int score;
	int minute;
	int sec;
}record; //이름, 점수, 시간을 저장할 구조체
int score;
int fruitx, fruity;  // Global variables 선언
record nowrec;

int over = 0;

void gotoxy(int x, int y);          //입력 위치 설정
void make_stage_low();                  //스테이지하 구현
void make_stage_mid();                  //스테이지중 구현
void make_stage_high();                 //스테이지상 구현
int getCommand();                   //키보드 입력
void gameover();            //게임오버 화면
void startscr();                    //시작 화면
void snake_move_low();                  //뱀의 움직임
void snake_move_high();                 //뱀의 움직임
void rank_call();					//랭킹 표시
void rankrecord();                  //랭킹 기록
void cursor(int i);             //커서 상태 변경
void stopwatch();               //스톱워치 보여주기

int main(void) {
	startscr();
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { 30 + x * 2, 10 + y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void make_stage_low() {
	score = 0;               //Drawing the snake in this function
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
	fruitx = 2 + rand() % 15;      // Drawing the fruit and make it appear in a random spot
	fruity = 2 + rand() % 15;
	gotoxy(fruitx, fruity);   // Feeding 2+rand()%15 into gotoxy
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
		gotoxy(i, 12);
		printf("#");
	}
	for (int i = 2, j = 11; i <= 9 && j >= 4; i++, j--) {
		gotoxy(i, j);
		printf("#");
	}
	for (int i = 16, j = 11; i >= 9 && j >= 4; i--, j--) {
		gotoxy(i, j);
		printf("#");
	}
}

void make_stage_high() {
	int x = 11, y = 9;
	int x1 = 10, y1 = 9;
	int x2 = 9, y2 = 9;
	int x3 = 8, y3 = 9;
	int x4 = 7, y4 = 9;
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
	for (int i = 6; i <= 12; i++) {
		gotoxy(i, 6);
		printf("#");
		gotoxy(6, i);
		printf("#");
		gotoxy(12, i);
		printf("#");
		gotoxy(i, 12);
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
	record reading;
	if (fopen_s(&rank, "rank.txt", "r") != 0) printf("no record\n");
	else {
		printf("\n");
		/* 정렬 하고 나서
			아직 미구현  */

		while (fscanf_s(rank, "%s %d %d : %d\n", reading.name, sizeof(reading.name), &reading.score, &reading.minute, &reading.sec) != EOF)
			printf("%s %d %d : %d\n", reading.name, reading.score, reading.minute, reading.sec);
		fclose(rank);
		printf("\n");
	}

}

void rankrecord() {
	printf("\npress enter to proceed...\n");
	while (getchar() != '\n');
	printf("\n\n\n\n\n\npress r to record your ranking...\n");
	char input = _getch();
	if (input == 'r') {
		FILE* rank;
		fopen_s(&rank, "rank.txt", "a");
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
		fprintf(rank, "%s %d %d : %d\n", nowrec.name, nowrec.score, nowrec.minute, nowrec.sec);
		fclose(rank);
		printf("saved!\n");
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
			HANDLE thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)snake_move_low, NULL, 0, NULL);
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
		if (x == fruitx && y == fruity) {
            int cur = time(NULL);
                        if (cur - last <= 0.5) {
                            score *= 2;
                        }
                        else if (cur - last <= 1) {
                            score += 20;
                        }
                        else if (cur - last <= 1.5) {
                            score += 15;
                        }
                        else {
                            score += 10;
                        }
                        time(&last);// If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			fruitx = 2 + rand() % 15;
			fruity = 2 + rand() % 15;
			gotoxy(fruitx, fruity);
			printf("@");
            gotoxy(-1, -1);
            printf("score = %d", score);

		}
        if ((x1 == fruitx && y1 == fruity) || (x2 == fruitx && y2 == fruity) || (x3 == fruitx && y3 == fruity) || (x4 == fruitx && y4 == fruity)) {
                 fruitx = 2 + rand() % 15;
                 fruity = 2 + rand() % 15;
                 gotoxy(fruitx, fruity);
                 printf("@");
                 gotoxy(-1, -1);
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
	}
}

void snake_move_high() {
	int x = 11, y = 9;
	int x1 = 10, y1 = 9;
	int x2 = 9, y2 = 9;
	int x3 = 8, y3 = 9;
	int x4 = 7, y4 = 9;
	char dir = 'd';
	char input = 'e';
	//Deleted the drawing since it's already drawn in the make_stage function
	while (1) {
		srand(time(NULL));
		if (x == fruitx && y == fruity) {  // If the snake's head reaches the coordinates of the fruit then make it appear in a random spot and increase the score by 1.
			fruitx = 2 + rand() % 15;
			fruity = 2 + rand() % 15;
			score += 1;
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
				if (y == 6) {
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
				if (x == 6) {
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
				if (y == 12) {
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
				if (x == 12) {
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
