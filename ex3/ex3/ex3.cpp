#include <iostream>
#include <fstream>
//#include <string.h>
//#include <cstring>
using namespace std;

int const MAT_SIZE = 10;
int const ROW_SIZE = 10;
int const COLUMN_SIZE = 10;
int const WALL_SIZE = 1;
int const WALL = -1;
char const BLANK = '-';
int const diractionSize = 4;

struct wordDat 
{
	 char cWordString[16];
	 int value;
	 bool isStore;
 };
struct Diraction 
{
	 int row;
	 int column;
 };


void createFile();
wordDat *resizeArr(wordDat *arrOldArr, int nNewSize);
void readFromFile();
void printBoard();
void createFirstMat();
void createDiractionVector();
bool findWordToInsert(int nRow, int nColumn);
bool tryToInsertWordHorizontal(int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter);
bool tryToInsertWordVertical(int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter);
void insertWord(int diracrion, int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter);


const char FILE_NAME[] = "D:/newfile.txt";
char arrBoard[ROW_SIZE + WALL_SIZE * 2][COLUMN_SIZE + WALL_SIZE * 2];
wordDat *arrWords;
int nWordsSize = 0;
int nWordsIndex = 0;
Diraction diractions[diractionSize + 1];
void main()
{
	int nIndex;
	bool bIsDone = false;
	createFile();
	createDiractionVector();
	arrWords = new wordDat[nWordsSize];
	readFromFile();
	createFirstMat();
	
	for (nIndex = 0; nIndex < strlen(arrWords[0].cWordString); nIndex++)
	{
		arrBoard[ROW_SIZE / 2][COLUMN_SIZE / 2 + nIndex] = arrWords[0].cWordString[nIndex];
	}
	arrWords[0].isStore = true;// becuse the first word used ( it is on the board now)
	printBoard();
	//cout << strchr(arrWords[0].cWordString, arrBoard[5][7]) << endl;//arrBoard[nRow][nColumn]
	//cout << strchr(arrWords[0].cWordString, 'L') << endl;
	for (int i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE && !bIsDone; i++)
	{
		for (int j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 if(arrBoard[i][j] != BLANK)
			 {
				 cout << i << "  " << j << endl;
				 bIsDone = findWordToInsert(i, j);
				 if (bIsDone)
				 {
					 cout << "hiii" << endl;
					 break;
				 }
			 }
		 }
	}
	printBoard();
	bIsDone = false;
	cout << "after print" << endl ;
	for (int i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE && !bIsDone; i++)
	{
		cout << "hi" << endl;
		for (int j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 cout << "hi" << endl;
			 if(arrBoard[i][j] != BLANK)
			 {
				 cout << i << "  " << j << endl;
				 bIsDone = findWordToInsert(i, j);
				 if (bIsDone)
				 {
					 break;
				 }
			 }
		 }
	}
	printBoard();
	bIsDone = false;
	for (int i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE && !bIsDone; i++)
	{
		for (int j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 if(arrBoard[i][j] != BLANK)
			 {
				 bIsDone = findWordToInsert(i, j);
				 if (bIsDone)
				 {
					 break;
				 }
			 }
		 }
	}
	printBoard();
}
// a method that create the textfile with the words and thier values
void createFile()
{
	fstream file;
	file.open(FILE_NAME, ios::out);
	if (!file.is_open())
	{ 
		cout << "Error opening file: " << FILE_NAME << endl;
	}
	else
	{
		file << "HELLO" << " " << 100 << endl;
		file << "MESS" << " " << 80 << endl;
		file << "CAUTION" << " " << 75 << endl;
		file << "VOTE" << " " << 70 << endl;
		file << "SEVEN" << " " << 40 << endl;
		file << "OR" << " " << 10 << endl;
		file << "SASA" << " " << 5 << endl;
		file.close();
	}
}

// a method that reads the words and thier values from file and store it in an array
void readFromFile()
{
	wordDat word;
	fstream file;
	file.open(FILE_NAME, ios::in);
	if (!file.is_open())
	{ 
		cout << "Error opening file: " << FILE_NAME << endl;
	}
	else
	{
		 while (!file.eof())
		 {
			file >> word.cWordString;
			if (file.eof())
			{
				break;
			}
			else
			{
				file >> (int)word.value;
			}
			if (file.eof())
			{
				break;
			}
			word.isStore = false;
			arrWords = resizeArr(arrWords, nWordsSize + 1);
			arrWords[nWordsSize - 1] = word;
			
			
			
		 }
	}
}
// a method that changes the size of the array, actually it create a new array with the new size and copy he old values.
wordDat *resizeArr(wordDat *arrOldArr, int nNewSize)
{
	wordDat *newArr = new wordDat[nNewSize];
	std::copy_n(arrOldArr, std::min(nWordsSize, nNewSize), newArr);
	delete[] arrOldArr;
	nWordsSize = nNewSize;
	return newArr;
}
void createFirstMat()
{
	int i;
	int j;
	for (i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [0] [i] = WALL;	
	}
	for (i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [MAT_SIZE + WALL_SIZE * 2 - 1] [i] = WALL;
	}
	for (i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [i] [0] = WALL;	
	}
	for (i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [i] [MAT_SIZE + WALL_SIZE * 2 - 1] = WALL;	
	}	

	for (i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE; i++)
	{
		for (j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 arrBoard [i][j] = BLANK;
		 }
	}
}
void printBoard()
{
	for (int i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE; i++)
	{
		for (int j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 cout << "  " << arrBoard [i][j];
		 }
		 cout << endl;
	}
	 cout << endl;
	 cout << endl;
}
bool findWordToInsert(int nRow, int nColumn)
{
	//cout << nRow << "  " << nColumn << endl;
	bool bIsWordAdded = false;
	int nIndex;
	char *ch;
	for (nIndex = 0; nIndex < nWordsSize; nIndex ++)
	{
		//cout <<   arrBoard[nRow][nColumn] << endl;
		//cout << arrWords[nIndex].cWordString << endl;
		if (!arrWords[nIndex].isStore)
		{
			ch = strchr(arrWords[nIndex].cWordString, arrBoard[nRow][nColumn]);//arrBoard[nRow][nColumn]
			if (strchr(arrWords[nIndex].cWordString, arrBoard[nRow][nColumn]))
			{
				cout << strchr(arrWords[nIndex].cWordString, arrBoard[nRow][nColumn]) << endl;
			}
			if(ch != NULL)
			{
				cout << "in if" << endl;
				if (tryToInsertWordHorizontal(nRow, nColumn, nIndex, ch))
				{
					cout << "in inner if" << endl;
					insertWord(2, nRow, nColumn, nIndex, ch);
					arrWords[nIndex].isStore = true;
					bIsWordAdded = true;
					break;
				}
				else if (tryToInsertWordVertical(nRow, nColumn, nIndex, ch))
				{
					cout << "in inner if" << endl;
					insertWord(3, nRow, nColumn, nIndex, ch);
					arrWords[nIndex].isStore = true;
					bIsWordAdded = true;
					break;
				}
			}
		}
		
	}

	return bIsWordAdded;
}
bool tryToInsertWordVertical(int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter)
{
	/*bool bIshorizontalRIght = true;
	bool bIshorizontalLeft = true;*/
	bool bIsVerticalUp = true;
	bool bIsVerticalDown = true;
	int nTempRow = nRow;
	int nTempColumn = nColumn;
	char *arrTempPointer = fromLetter;
	char *arrCTempWord = arrWords[nIndexInWordsArr].cWordString;
	//check if can store in vertical way (up)
	while(*arrCTempWord != *fromLetter)
	{
		nTempRow += diractions[1].row;
		nTempColumn += diractions[1].column;
		if (arrBoard[nTempRow][nTempColumn] != '-')
		{
			bIsVerticalUp = false;
			break;
		}
		arrCTempWord ++;
	}
	arrTempPointer = fromLetter;
	nTempRow = nRow;
	nTempColumn = nColumn;
	//check if can store in vertical way (down)
	while(*arrTempPointer != 0)
	{
		nTempRow += diractions[3].row;
		nTempColumn += diractions[3].column;
		if (arrBoard[nTempRow][nTempColumn] != '-')
		{
			bIsVerticalUp = false;
			break;
		}
		arrTempPointer ++;
	}

	return bIsVerticalUp && bIsVerticalDown;
}
bool tryToInsertWordHorizontal(int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter)
{
	bool bIshorizontalRIght = true;
	bool bIshorizontalLeft = true;
	/*bool bIsVerticalUp = true;
	bool bIsVerticalDown = true;*/
	int nTempRow = nRow;
	int nTempColumn = nColumn;
	char *arrTempPointer = fromLetter;
	char *arrCTempWord = arrWords[nIndexInWordsArr].cWordString;
	//check if can store in horizontal way (left)
	while(*arrCTempWord != *fromLetter)
	{
		nTempRow += diractions[4].row;
		nTempColumn += diractions[4].column;
		if (arrBoard[nTempRow][nTempColumn] != '-')
		{
			bIshorizontalLeft = false;
			break;
		}
		arrCTempWord ++;
	}
	arrTempPointer = fromLetter;
	nTempRow = nRow;
	nTempColumn = nColumn;
	//check if can store in vertical way (down)
	while(*arrTempPointer != 0)
	{
		nTempRow += diractions[2].row;
		nTempColumn += diractions[2].column;
		if (arrBoard[nTempRow][nTempColumn] != '-')
		{
			bIshorizontalRIght = false;
			break;
		}
		arrTempPointer ++;
	}

	return bIshorizontalRIght && bIshorizontalLeft;
}
void insertWord(int diracrion, int nRow, int nColumn, int nIndexInWordsArr, char *fromLetter)
{
	int nCounter = 0;
	int nIndex ;
	int nTempRow = nRow;
	int nTempColumn = nColumn;
	char *arrCTempWord = arrWords[nIndexInWordsArr].cWordString;
	while (*arrCTempWord != *fromLetter)
	{
		nCounter ++;
		arrCTempWord ++;
	}
	arrCTempWord = arrWords[nIndexInWordsArr].cWordString;
	if (diracrion == 3)
	{
		nTempRow -= nCounter;
		for (nIndex = 0; nIndex < strlen(arrWords[nIndexInWordsArr].cWordString); nIndex++)
		{
			arrBoard[nTempRow + nIndex][nTempColumn] = *arrCTempWord;
			arrCTempWord ++;
		}
	}
	else if (diracrion == 2)
	{
		nTempColumn -= nCounter;
		for (nIndex = 0; nIndex < strlen(arrWords[nIndexInWordsArr].cWordString); nIndex++)
		{
			arrBoard[nTempRow][nTempColumn + nIndex] = *arrCTempWord;
			arrCTempWord ++;
		}
	}
	
}
void createDiractionVector()
{
	diractions[1].row = -1;
	diractions[1].column = 0;
	diractions[2].row = 0;
	diractions[2].column = 1;
	diractions[3].row = 1;
	diractions[3].column = 0;
	diractions[4].row = 0;
	diractions[4].column = -1;
}