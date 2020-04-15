#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

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
	struct snake* previous;
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

void DrowHead(SNAKE* head)
{
	gotoxy(head->coord.X, head->coord.Y);
	printf("*");
	gotoxy(0, size_ + 1);
}

void DelLast(COORD* end)
{
	gotoxy(end->X, end->Y);
	printf(" ");
	gotoxy(0, size_ + 1);
}

void addApple(COORD* apple,SNAKE* head)
{
	apple->X = rand() % (size_-1) + 1;
	apple->Y = rand() % (size_-1) + 1;
	gotoxy(apple->X, apple->Y);
	AppleChek(apple, head);
	
	printf("@");
	gotoxy(0, size_ + 1);
	

}

void addTail(SNAKE* head, COORD end)
{
	while (head->next != 0)
	{
		head = head->next;
		
	}
	SNAKE* tmp = (SNAKE*)malloc(sizeof(SNAKE));
	head->next = tmp;
	head->next->next = 0;
	head->next->coord.X = end.X;
	head->next->coord.Y = end.Y;
	
	
	
}

void FindEnd(COORD* end, SNAKE* head)
{
	while (head->next != 0)
	{
		head = head->next;
		
	}		

	end->X = head->coord.X;
	end->Y = head->coord.Y;
	
	
}
 
void ResCord(SNAKE* head)
{
	COORD cop;
	cop.X = head->coord.X;
	cop.Y = head->coord.Y;
	while (head)
	{
		
		if (head->next == 0) { break; }
		else
		{
			COORD tmp;
			tmp.X = head->next->coord.X;
			tmp.Y = head->next->coord.Y;
			head->next->coord.X = cop.X;
			head->next->coord.Y = cop.Y;
			cop.X = tmp.X;
			cop.Y = tmp.Y;


		}
		head = head->next;		
	}
}

void GameOver(SNAKE* head)
{
	if (head->coord.X == 0 || head->coord.X == size_ + 1)
	{
		system("cls");
		printf("Game Over");
		exit(1);
	}
		
	if (head->coord.Y == 0 || head->coord.Y == size_ + 1)
	{
		system("cls");
		printf("Game Over");
		exit(1);
	}

	COORD cop;
	cop.X = head->coord.X;
	cop.Y = head->coord.Y;
	while (head->next != 0)
	{
		if (cop.X == head->next->coord.X && cop.Y == head->next->coord.Y)
		{
			system("cls");
			printf("Game Over");
			exit(1);
		}
		head = head->next;
	}
	
	
		
}

int AppleChek(COORD* apple, SNAKE* head)
{
	int flag = 1;
	while (1)
	{
		flag = 1;
		SNAKE* COP = head;
		while (COP->next != 0)
		{
			if (apple->X == COP->next->coord.X && apple->Y == COP->next->coord.Y)
			{
				apple->X = rand() % (size_ - 1) + 1;
				apple->Y = rand() % (size_ - 1) + 1;
				flag = 0;
				break;
			}
			COP = COP->next;
		}
		if (flag == 1) break;		
	}
	
}

int main()
{
	srand(time(NULL));
	size_ = 20;
	//int n = 20;
	
	field(size_);
	


	SNAKE* head = (SNAKE*)malloc(sizeof(SNAKE));
	head->next = 0;
	head->previous = 0;
	head->coord.X = rand() % (size_ - 1) + 1;
	head->coord.Y = rand() % (size_ - 1) + 1;

	COORD apple;
	addApple(&apple,head);

	COORD end;

//	FindEnd(&end, head);
//	gotoxy(0, size_ + 2);
//	printf("%d %d", end.X, end.Y);
	DrowHead(head);
	//DelLast(head);
	
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

	char key;
	int k = 0;
	while (1)
	{
		GameOver(head);
				
		if (head->coord.X == apple.X && head->coord.Y == apple.Y)
		{
			
			addTail(head, end);
			addApple(&apple,head);	
			
		}
		FindEnd(&end, head);
		
		
		//gotoxy(0, size_ + 2);
		//printf("%d %d\n", head->coord.X, head->coord.Y);
		//printf("%d %d", end.X, end.Y);
		//printf("%d %d\n", apple.X, apple.Y);		
		
		if (_kbhit)
		{
			key = _getch();
		}
		switch (key)
		{

		case 'w':
			ResCord(head);
			head->coord.X += 0;
			head->coord.Y -= 1;			
			DrowHead(head);
			DelLast(&end);

			break;
		case 'a':
			ResCord(head);
			head->coord.X -= 1;
			head->coord.Y += 0;
			DrowHead(head);
			DelLast(&end);

			break;

		case 's':
			ResCord(head);
			head->coord.X += 0;
			head->coord.Y += 1;
			DrowHead(head);
			DelLast(&end);
			break;

		case 'd':
			ResCord(head);
			head->coord.X += 1;
			head->coord.Y += 0;
			DrowHead(head);
			DelLast(&end);
			break;
		}
	}
		
}
