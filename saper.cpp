#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

int arr[9][9] = { 0 };
int table[9][9] = { -1 };

int colors[8] = { 34, 33, 31, 35, 91, 36, 32, 37 };

void SetCursorPos(int XPos, int YPos)
{
 	printf("\033[%d;%dH", YPos+1, XPos+1);
}

void ClearConsole()
{
	printf("\033[2J\033[1;1H");
}

void reveal(int x, int y)
{
	if (table[x][y] != -1)
		return;

	int c = 0;

	if (x != 0 && y != 8 && arr[x-1][y+1] == 1)		// Top Left
		c++;
	if (y != 8 && arr[x][y+1] == 1)		// Top Center
		c++;
	if (x != 8 && y != 8 && arr[x+1][y+1] == 1)		// Top Right
		c++;
	if (x != 0 && arr[x-1][y] == 1)		// Center Left
		c++;
	if (x != 8 && arr[x+1][y] == 1)		// Center Right
		c++;
	if (x != 0 && y != 0 && arr[x-1][y-1] == 1)		// Bottom Left
		c++;
	if (y != 0 && arr[x][y-1] == 1)		// Bottom Center
		c++;
	if (x != 8 && y != 0 && arr[x+1][y-1] == 1)		// Bottom Right
		c++;

	if (c == 0)
	{
		table[x][y] = 0;

		if (x != 0 && y != 8)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x-1 << " " << y+1 << "; from " << x << " " << y << endl;
			reveal(x-1, y+1);
		}
		if (y != 8)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x << " " << y+1 << "; from " << x << " " << y << endl;
			reveal(x, y+1);
		}
		if (x != 8 && y != 8)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x+1 << " " << y+1 << "; from " << x << " " << y << endl;
			reveal(x+1, y+1);
		}
		
		if (x != 0)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x-1 << " " << y << "; from " << x << " " << y << endl;
			reveal(x-1, y);
		}
		if (x != 8)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x+1 << " " << y << "; from " << x << " " << y << endl;
			reveal(x+1, y);
		}

		if (x != 0 && y != 0)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x-1 << " " << y-1 << "; from " << x << " " << y << endl;
			reveal(x-1, y-1);
		}
		if (y != 0)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x << " " << y-1 << "; from " << x << " " << y << endl;
			reveal(x, y-1);
		}
		if (x != 8 && y != 0)
		{
			SetCursorPos(0, 12);
			cout << "Checking " << x+1 << " " << y-1 << "; from " << x << " " << y << endl;
			reveal(x+1, y-1);
		}
	}
	else
		table[x][y] = c;
}

void show_revealed()
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (arr[x][y] == 0)
			{
				int c = 0;

				if (x != 0 && y != 8 && arr[x-1][y+1] == 1)		// Top Left
					c++;
				if (y != 8 && arr[x][y+1] == 1)		// Top Center
					c++;
				if (x != 8 && y != 8 && arr[x+1][y+1] == 1)		// Top Right
					c++;
				if (x != 0 && arr[x-1][y] == 1)		// Center Left
					c++;
				if (x != 8 && arr[x+1][y] == 1)		// Center Right
					c++;
				if (x != 0 && y != 0 && arr[x-1][y-1] == 1)		// Bottom Left
					c++;
				if (y != 0 && arr[x][y-1] == 1)		// Bottom Center
					c++;
				if (x != 8 && y != 0 && arr[x+1][y-1] == 1)		// Bottom Right
					c++;

				if (c != 0)
				{
					SetCursorPos((x + 2) * 2, y + 2);
					cout << "\033[" << colors[c - 1] << "m" << c << "\033[0m";
				}
			}
			else
			{
				SetCursorPos((x + 2) * 2, y + 2);
				cout << '@';
			}
		}
	}
}

int main() {

	ClearConsole();
	srand(time(NULL));


	string cmd;
	int ix, iy;
	int bombCount = 0, b = 0;
	int flags;

	for (int i = 0; i < 10; i++)
		arr[rand() % 9][rand() % 9] = 1;

	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
		{
			table[x][y] = -1;
			if (arr[x][y] == 1)
				bombCount++;
		}
	
	while (true)
	{
		ClearConsole();
		cmd = "";

		flags = 0;
		for (int x = 0; x < 9; x++)
			for (int y = 0; y < 9; y++)
			{
				if (table[x][y] == 67)
					flags++;
			}

		SetCursorPos(25, 3);
		cout << "Bombs: " << bombCount;

		SetCursorPos(25, 4);
		cout << "Flags: " << flags;

		for (int x = 0; x < 9; x++) 
		{
			SetCursorPos((x + 2) * 2, 0);
			cout << x + 1;

			for (int y = 0; y < 9; y++)
			{
				SetCursorPos(0, y + 2);
				cout << y + 1;

				SetCursorPos((x + 2) * 2, y + 2);
				if (table[x][y] == -1)
					cout << "#";
				else if (table[x][y] == 67)
					cout << "*";
				else if (table[x][y] != 0)
				{
					if (table[x][y] > 0 && table[x][y] < 10)
						cout << "\033[" << colors[table[x][y] - 1] << "m" << table[x][y] << "\033[0m";
					else 
						cout << table[x][y];
				}
			}
		}

		b = 0;
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (table[x][y] == 67 && arr[x][y] == 1)
					b++;
			}
		}

		if (b == bombCount)
		{
			show_revealed();
			SetCursorPos(0, 11);

			break;
		}

		cout << endl << "Command: ";
		cin >> cmd;

		ix = cmd[0]-'0'-1;
		iy = cmd[1]-'0'-1;

		if (cmd[2] == '*' && table[ix][iy] == -1)
		{
			table[ix][iy] = 67;
		}
		else if (cmd[2] == '*' && table[ix][iy] == 67)
		{
			table[ix][iy] = -1;
		}
		else if (arr[ix][iy] == 1)
		{
			for (int x = 0; x < 9; x++) 
			{
				for (int y = 0; y < 9; y++)
				{
					SetCursorPos((x + 2) * 2, y + 2);
					if (table[x][y] != 67 && arr[x][y] == 1)
						cout << '!';
					else if (table[x][y] == 67 && arr[x][y] == 1)
						cout << '@';
					else if (table[x][y] == 67 && arr[x][y] == 0)
						cout << '/';
				}
			}

			break;
		}
		else
			reveal(ix, iy);
	}

	cout << endl;

	return 0;
}
