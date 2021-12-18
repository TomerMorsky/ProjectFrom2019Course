#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int const VERSI_SIZE = 8;
int const WALL_SIZE = 1;
int const ROW_SIZE = VERSI_SIZE;
int const COLUMN_SIZE = VERSI_SIZE;
int const MAT_SIZE = (ROW_SIZE + WALL_SIZE * 2) * (COLUMN_SIZE + WALL_SIZE * 2);
int const WHITE = 0;
int const BLACK = 1;
int const BLANK = 2;
int const WALL = -1;
int const diractionSize = 8;

void print_matWalls (int mat[][VERSI_SIZE + WALL_SIZE * 2]);
void print_mat (int mat[][VERSI_SIZE + WALL_SIZE * 2]);
void createFirstMat(int mat[][VERSI_SIZE + WALL_SIZE * 2]);
void makeTurn(int mat[][VERSI_SIZE + WALL_SIZE * 2],int player); 
void createDiractionVector();
void seriaFound(int mat[][VERSI_SIZE + WALL_SIZE * 2],int row, int column, int diraction);
void checkIfSeria(int mat[][VERSI_SIZE + WALL_SIZE * 2],int row, int column);
void exitToNewFile(int mat[][VERSI_SIZE + WALL_SIZE * 2]);
void exitToExistFile(int mat[][VERSI_SIZE + WALL_SIZE * 2], string path);
string importFromFile(int mat[][VERSI_SIZE + WALL_SIZE * 2]);

struct Diraction
{
	 int row;
	 int column;
 };

struct square
{
	 int row;
	 int column;
	 int color;// 0 for white and 1 for black
 };

// global diraction vector
Diraction diractions[8] = {0};
int numOfSquare = 0;
void main() 
{
	string path;
	int selection = -1;
	int versi [VERSI_SIZE + WALL_SIZE * 2][VERSI_SIZE + WALL_SIZE * 2] = {0};
	createDiractionVector();
	cout << "hi player, please press 1 for new game or 2 for open an old one. every round can press 99 and end the game " << endl;
	cin >> selection;
	int saveMod = -1;
	while (selection != 99)
	{
		if (selection == 1)
		{
			saveMod = 1;
			createFirstMat(versi);// create te walls of the mat
			print_mat(versi);
			makeTurn(versi,WHITE);
			makeTurn(versi,BLACK);
		}
		else if (selection == 2)
		{
			saveMod = 2;
			createFirstMat(versi);
			path = importFromFile(versi);
			print_mat(versi);
			makeTurn(versi,WHITE);
			makeTurn(versi,BLACK);
		}
		else if (selection == 5)
		{
			makeTurn(versi,WHITE);
			makeTurn(versi,BLACK);
		}
		else 
		{
			cout << "ilegal key" << endl;
		}
		if (numOfSquare == ROW_SIZE * COLUMN_SIZE)
		{
			gameEnded(versi);
		}
		else
		{
			cout << "to keep playing press 5, to exit and save press 99, if want to exit without save then press 5 to continue and press 999 in the row number" << endl;
			cin >> selection;
		}
		
	}
	if (saveMod == 1)
	{
		exitToNewFile(versi);
	}
	else 
	{
		exitToExistFile(versi, path);
	}
	
}

// print the all mat include the walls
void print_matWalls (int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	for (int i = 0; i < ROW_SIZE + WALL_SIZE * 2; i++)
	{
		 for (int j = 0; j < COLUMN_SIZE + WALL_SIZE * 2; j ++)
		 {
			 cout << " " << mat [i][j];
		 }
		 cout << endl;
	}
}

// print the all mat exept to the walls
void print_mat (int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
	{
		 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
		 {
			 cout << "  " << mat [i][j];
		 }
		 cout << endl;
	}
}

// create the walls of the mat
void createFirstMat(int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
	{
		 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
		 {
			mat [i][j] = 2;
		 }
	}
	for (int i = 0; i < VERSI_SIZE + WALL_SIZE * 2; i ++) 
	{
		mat [0] [i] = WALL;	
	}
	for (int i = 0; i < VERSI_SIZE + WALL_SIZE * 2; i ++) 
	{
		mat [VERSI_SIZE + WALL_SIZE * 2 - 1] [i] = WALL;
	}
	for (int i = 0; i < VERSI_SIZE + WALL_SIZE * 2; i ++) 
	{
		mat [i] [0] = WALL;	
	}
	for (int i = 0; i < VERSI_SIZE + WALL_SIZE * 2; i ++) 
	{
		mat [i] [VERSI_SIZE + WALL_SIZE * 2 - 1] = WALL;	
	}
	mat[ROW_SIZE / 2][COLUMN_SIZE / 2] = BLACK;
	mat[ROW_SIZE / 2][COLUMN_SIZE / 2 + 1] = WHITE;
	mat[ROW_SIZE / 2 + 1][COLUMN_SIZE / 2 + 1] = BLACK;
	mat[ROW_SIZE / 2 + 1][COLUMN_SIZE / 2] = WHITE;
	
}

void makeTurn(int mat[][VERSI_SIZE + WALL_SIZE * 2],int player) 
{
	int row = -1, column = -1;
	bool legalNumbers = false;
	while (!legalNumbers) 
	{
		cout << player << " is playing now" << endl;
		cout << "enter row number" << endl;
		cin >> row;
		cout << "enter column number" << endl;
		cin >> column;
		column = 9 - column;//because the order of 1 to 8 is different
		if (column > 0 && column < 9 && row > 0 && row < 9 && mat [row][column] == 2) 
		{
			mat [row][column] = player;
			legalNumbers = true;
			numOfSquare ++;
		}
		else if (row == 999)
		{//exit and ask if want to save the game
			char answer = 0;
			cout << "do you want to save the game? press y for yes or n for no" << endl;
			cin >> answer;
			if(answer == 'y')
			{
				exitToNewFile(mat);
				exit(0);
			}
			else if (answer == 'n')
			{
				exit(0);
			}
			
		}
		else
		{
			cout << "enter legal numbers" << endl;
		}
	}
	print_mat(mat);
	cout << endl;
	cout << endl;
	checkIfSeria(mat, row, column);
	
}
//create the diraction vactor. run once in every running
void createDiractionVector()
{
	diractions[0].row = -1;
	diractions[0].column = -1;
	diractions[1].row = -1;
	diractions[1].column = 0;
	diractions[2].row = -1;
	diractions[2].column = 1;
	diractions[3].row = 0;
	diractions[3].column = 1;
	diractions[4].row = 1;
	diractions[4].column = 1;
	diractions[5].row = 1;
	diractions[5].column = 0;
	diractions[6].row = 1;
	diractions[6].column = -1;
	diractions[7].row = 0;
	diractions[7].column = -1;
}
void checkIfSeria(int mat[][VERSI_SIZE + WALL_SIZE * 2],int row, int column)
{
	int tempRow = row, tempColumn =column;
	bool refresh = false;
	int counter = 0;
	for(int i = 0; i < diractionSize; i++)
	{
		tempRow += diractions[i].row;
		tempColumn += diractions[i].column;
		while ((mat[row][column] + 1) % 2 == mat[tempRow][tempColumn])
		{
			tempRow += diractions[i].row;
			tempColumn += diractions[i].column;
			counter ++;
		}
		if (mat[tempRow][tempColumn] == mat[row][column] && counter > 0)
		{
			seriaFound(mat, row, column,i);
			refresh = true;
		}
		tempRow = row;
		tempColumn =column;
	 }
	if (refresh) 
	{
		cout << "after refresh the board" << endl;
		print_mat(mat);
	}
	
}
void seriaFound(int mat[][VERSI_SIZE + WALL_SIZE * 2],int row, int column, int diraction)
{
	int tempRow = row, tempColumn =column;
	tempRow += diractions[diraction].row;
	tempColumn += diractions[diraction].column;
	while(mat[tempRow][tempColumn] != mat[row][column])
	{
		mat[tempRow][tempColumn] = mat[row][column];
		tempRow += diractions[diraction].row;
		tempColumn += diractions[diraction].column;
	}
	
}
void exitToNewFile(int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	 string path = "D:/ex.txt";
	 cout << "enter path and file name: "<< endl;
	 cin >> path;
	 fstream pf;
	 pf.open(path,ios::out);
	 if (!pf.is_open())
	 {
		cout << "Error opening file: " << path << endl;
	 }
	 else
	 {
		 for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
		{
			 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
			 {
				 if (mat [i][j] != 2)
				 {
					 square sq;
					 sq.row = i;
					 sq.column = j;
					 sq.color = mat [i][j];
					 pf.write((char*)&sq, sizeof(square));
				 }
			 }
		}
		 pf.close();
	 }
}
void exitToExistFile(int mat[][VERSI_SIZE + WALL_SIZE * 2], string path)
{
	 fstream pf;
	 pf.open(path,ios::app);
	 if (!pf.is_open())
	 {
		cout << "Error opening file: " << path << endl;
	 }
	 else
	 {
		 for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
		{
			 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
			 {
				 if (mat [i][j] != 2)
				 {
					 cout << "in write file";
					 square sq;
					 sq.row = i;
					 sq.column = j;
					 sq.color = mat [i][j];
					 pf.write((char*)&sq, sizeof(square));
				 }
			 }
		}
		 pf.close();
	 }
}
string importFromFile(int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	 string path = "D:/ex.txt";
	 cout << "enter path and file name: "<< endl;
	 cin >> path;
	 fstream pf;
	 pf.open(path,ios::in);
	 square sq;
	 if (!pf.is_open())
	 {
		cout << "Error opening file: " << path << endl;
	 }
	 else
	 {
		 pf.read((char*)&sq, sizeof(square));
		 while (!pf.eof())
		 {
			 mat[sq.row][sq.column] = sq.color;
			 pf.read((char*)&sq, sizeof(square));
		 }
	 }
	 pf.close();
	 return path;
}
int countBlack (int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	int counter = 0;
	for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
	{
		 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
		 {
			 if(mat [i][j] == BLACK)
			 {
				counter ++;			 
			 }
		 }
	}
	return counter;
}
int countWhite (int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	int counter = 0;
	for (int i = 1; i < ROW_SIZE + (WALL_SIZE * 2) - WALL_SIZE ; i++)
	{
		 for (int j = 1; j < COLUMN_SIZE + WALL_SIZE * 2 - WALL_SIZE ; j ++)
		 {
			 if(mat [i][j] == WHITE)
			 {
				counter ++;			 
			 }
		 }
	}
	return counter;
}
void gameEnded(int mat[][VERSI_SIZE + WALL_SIZE * 2])
{
	int blackSquare = 0, whiteSquare = 0;
	blackSquare = countBlack(mat);
	whiteSquare = countWhite(mat);
	if (blackSquare > whiteSquare)
	{
		cout << "the black is the winner" << endl;
		exit(0);
	}
	else if (blackSquare < whiteSquare)
	{
		cout << "the white is the winner" << endl;
		exit(0);
	}
	else
	{
		cout << "the white and the black are the winner" << endl;
		exit(0);
	}
}