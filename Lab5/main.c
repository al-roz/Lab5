#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

int size_; 

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct snake
{
	COORD coord;
	struct snake* next;
};
typedef struct snake SNAKE;

void field(int size)
{
	printf(" ");
	for (int i = 0; i < size; i++)
		printf("-");
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("|");
		for (int j = 0; j <= size - 1; j++)
			printf(" ");
		printf("|\n");


	}
	printf(" ");
	for (int i = 0; i < size; i++)
		printf("-");
	printf("\n");
}

void addApple(COORD* apple)
{
	apple->X = rand() % (size_-1) + 1;
	apple->Y = rand() % (size_-1) + 1;
	gotoxy(apple->X, apple->Y);
	printf("@");
	gotoxy(0, size_ + 1);
}


int main()
{
	srand(time(NULL));
	size_ = 20;
	//int n = 20;
	COORD apple;
	field(size_);
	addApple(&apple);

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

	char key;
	if (_kbhit)
	{
		key = _getch();
	}
		
}
