#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>  
using namespace std;

int const diractionSize = 4;
int const ATOM = 7;
int const BOOM = 6;
int const MAT_SIZE = 7;
int const WALL_SIZE = 1;
int const WALL = -1;
int const EMPTY = 0;
int const UP = 1;
int const RIGHT = 2;
int const DOWN = 3;
int const LEFT = 4;
int const ROW_SIZE = MAT_SIZE;
int const COLUMN_SIZE = MAT_SIZE;

struct Diraction 
{
	 int row;
	 int column;
 };

struct Boom 
{
	 int row;
	 int column;
 };

struct atom
{
	 int row;
	 int column;
 };

struct neutron
{
	 int row;
	 int column;
	 int diraction;
 };

void createDiractionVector();
atom* resizeArr(atom *oldArr, int newSize);
neutron* resizeArr(neutron *oldArr, int newSize);
int initializationOfMat();
void createFile();
void createFirstMat();
void printBoard();
void loadDataToBoard();
bool atomAttack(int nRow, int nColumn);
void boomToNeutron();
void makeATurn();
bool isIndexExistInArray(int *arr, int nTempIndex, int nSize);
void removeDuplicateNeutron();

Diraction diractions[diractionSize + 1] ;
neutron *arrNeutrons;
atom *arrAtoms;
Boom *arrbooms;
int nAtomArrSize = 0;
int nNeutronArrSize = 0;
int nBoomArrSize = 0;
int arrBoard[ROW_SIZE + WALL_SIZE * 2][COLUMN_SIZE + WALL_SIZE * 2];
int nNumberOfBumbedAtoms = 0;
void main()
{
	bool bAtomDamaged = false;
	int nRow = 0;
	int nColumn = 0;
	arrNeutrons = new neutron[nNeutronArrSize];
	arrAtoms = new atom[nAtomArrSize];
	arrbooms = new Boom[nBoomArrSize];
	createDiractionVector();
	createFirstMat();
	initializationOfMat();
	loadDataToBoard();
	printBoard();
	cout << "enter row to bump" << endl;
	cin >> nRow;
	cout << "enter colum to bump" << endl;
	cin >> nColumn;
	bAtomDamaged = atomAttack(nRow, nColumn);
	while (bAtomDamaged == false)
	{
		cout << "enter again row to bump" << endl;
		cin >> nRow;
		cout << "enter again colum to bump" << endl;
		cin >> nColumn;
		bAtomDamaged = atomAttack(nRow, nColumn);
	}
	printBoard();
	boomToNeutron();
	createFirstMat();
	loadDataToBoard();
	printBoard();

	while (nNeutronArrSize > 0)
	{
		makeATurn();
		removeDuplicateNeutron();
		createFirstMat();
		loadDataToBoard();
		printBoard();
		boomToNeutron();
		createFirstMat();
		loadDataToBoard();
		printBoard();
	}
	cout << "atoms bumbed: " << nNumberOfBumbedAtoms << endl;

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

atom* resizeArr(atom *arrOldArr, int nNewSize)
{
	atom *newArr = new atom[nNewSize];
	std::copy_n(arrOldArr, std::min(nAtomArrSize, nNewSize), newArr);
	delete[] arrAtoms;
	nAtomArrSize = nNewSize;
	return newArr;
}

neutron* resizeArr(neutron *arrOldArr, int nNewSize)
{
	neutron *newArr = new neutron[nNewSize];
	std::copy_n(arrOldArr, std::min(nNeutronArrSize, nNewSize), newArr);
	delete[] arrNeutrons;
	nNeutronArrSize = nNewSize;
	return newArr;
}

Boom* resizeArr(Boom *arrOldArr, int nNewSize)
{
	Boom *newArr = new Boom[nNewSize];
	std::copy_n(arrOldArr, std::min(nBoomArrSize, nNewSize), newArr);
	delete[] arrbooms;
	nBoomArrSize = nNewSize;
	return newArr;
}

int* resizeArr(int *arrOldArr,int *nOldSize, int nNewSize)
{
	int *newArr = new int[nNewSize];
	std::copy_n(arrOldArr, std::min(*nOldSize, nNewSize), newArr);
	delete[] arrOldArr;
	*nOldSize = nNewSize;
	return newArr;
}

int initializationOfMat()
{
   	 int numberOfAtom = 0;
	 string path = "D:/ex.txt";
	 cout << "enter path and file name: "<< endl;
	 cin >> path;
	 fstream pf;
	 pf.open(path,ios::in);
	 if (!pf.is_open())
	 {
		cout << "Error opening file: " << path << endl;
	 }
	 else
	 {
		 atom at;
		 pf.read((char*)&numberOfAtom, sizeof(int));
		 while (!pf.eof())
		 {
			 pf.read((char*)&at, sizeof(atom));
			 arrAtoms = resizeArr(arrAtoms,nAtomArrSize + 1);
			 arrAtoms[nAtomArrSize - 1] = at;
		 }
	 }
	 pf.close();

	 return numberOfAtom;
}

// just for debug, create a file with atom's details.
void createFile()
{

	 string path = "D:/ex.txt";
	 fstream pf;
	 pf.open(path,ios::out);
	 if (!pf.is_open())
	 {
		cout << "Error opening file: " << path << endl;
	 }
	 else
	 {
		 atom at;
		 int numberOfAtoms = 6;
		 pf.write((char*)&numberOfAtoms, sizeof(int));
		 at.row = 2;
		 at.column = 2;
		 pf.write((char*)&at, sizeof(atom));
		 at.row = 2;
		 at.column = 5;
		 pf.write((char*)&at, sizeof(atom));
		 at.row = 4;
		 at.column = 3;
		 pf.write((char*)&at, sizeof(atom));
		 at.row = 4;
		 at.column = 5;
		 pf.write((char*)&at, sizeof(atom));
		 at.row = 6;
		 at.column = 2;
		 pf.write((char*)&at, sizeof(atom));
		 at.row = 7;
		 at.column = 6;
		 pf.write((char*)&at, sizeof(atom));
		 pf.close();
	 }	
}

void createFirstMat()
{
	for (int i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [0] [i] = WALL;	
	}
	for (int i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [MAT_SIZE + WALL_SIZE * 2 - 1] [i] = WALL;
	}
	for (int i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [i] [0] = WALL;	
	}
	for (int i = 0; i < MAT_SIZE + WALL_SIZE * 2; i ++) 
	{
		arrBoard [i] [MAT_SIZE + WALL_SIZE * 2 - 1] = WALL;	
	}	

	for (int i = 0 + WALL_SIZE; i < ROW_SIZE + WALL_SIZE; i++)
	{
		for (int j = WALL_SIZE; j < COLUMN_SIZE + WALL_SIZE; j ++)
		 {
			 arrBoard [i][j] = EMPTY;
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

void eraceAtom(int nIndex)
{
	for(; nIndex < nAtomArrSize - 1; nIndex ++)
	{
		arrAtoms[nIndex] = arrAtoms[nIndex + 1];
	}
	arrAtoms = resizeArr(arrAtoms,nAtomArrSize - 1);
}

void eraceNeutron(int nIndex)
{
	for(; nIndex < nNeutronArrSize - 1; nIndex ++)
	{
		arrNeutrons[nIndex] = arrNeutrons[nIndex + 1];
	}
	arrNeutrons = resizeArr(arrNeutrons,nNeutronArrSize - 1);
}

void loadDataToBoard()
{
	int nIndexAtomsArr;
	int nIndexBoomArr;
	int nIndexNeutronArr;
	//load atoms
	for(nIndexAtomsArr = 0; nIndexAtomsArr < nAtomArrSize; nIndexAtomsArr++)
	{
		arrBoard[arrAtoms[nIndexAtomsArr].row][arrAtoms[nIndexAtomsArr].column] = ATOM;
	}
	//load booms
	for(nIndexBoomArr = 0; nIndexBoomArr < nBoomArrSize; nIndexBoomArr++)
	{
		arrBoard[arrbooms[nIndexBoomArr].row][arrbooms[nIndexBoomArr].column] = BOOM;
	}
	for(nIndexNeutronArr = 0; nIndexNeutronArr < nNeutronArrSize; nIndexNeutronArr++)
	{
		arrBoard[arrNeutrons[nIndexNeutronArr].row][arrNeutrons[nIndexNeutronArr].column] = arrNeutrons[nIndexNeutronArr].diraction;
	}
}

bool atomAttack(int nRow, int nColumn)
{	
	Boom bm;
	bool bIsAtomAttacked = false;
	int nIndex;
	for(nIndex = 0; nIndex < nAtomArrSize && bIsAtomAttacked == false; nIndex ++)
	{
		if(arrAtoms[nIndex].row == nRow && arrAtoms[nIndex].column == nColumn)
		{
			bIsAtomAttacked = true;
			eraceAtom(nIndex);
			arrbooms = resizeArr(arrbooms, nBoomArrSize + 1);
			bm.row = nRow;
			bm.column = nColumn;
			arrbooms[nBoomArrSize - 1] = bm;
			//createFirstMat();
			loadDataToBoard();
			nNumberOfBumbedAtoms ++;
		}
	}
	return bIsAtomAttacked;
}

void boomToNeutron()
{
	int nBoomIndex;
	for(nBoomIndex = 0; nBoomIndex < nBoomArrSize; nBoomIndex++)
	{
		neutron ntUp;
		neutron ntLeft;
		neutron ntDown;
		neutron ntRight;

		ntUp.column = arrbooms[nBoomIndex].column;
		ntUp.row = arrbooms[nBoomIndex].row - 1;
		ntUp.diraction = UP;
		if (arrBoard[ntUp.row][ntUp.column] != WALL)
		{
			arrNeutrons = resizeArr(arrNeutrons,nNeutronArrSize + 1);
			arrNeutrons[nNeutronArrSize - 1] = ntUp;
		}
		ntRight.column = arrbooms[nBoomIndex].column + 1;
		ntRight.row = arrbooms[nBoomIndex].row;
		ntRight.diraction = RIGHT;
		if (arrBoard[ntRight.row][ntRight.column] != WALL)
		{
			arrNeutrons = resizeArr(arrNeutrons,nNeutronArrSize + 1);
			arrNeutrons[nNeutronArrSize - 1] = ntRight;
		}
		ntDown.column = arrbooms[nBoomIndex].column;
		ntDown.row = arrbooms[nBoomIndex].row + 1;
		ntDown.diraction = DOWN;
		if (arrBoard[ntDown.row][ntDown.column] != WALL)
		{
			arrNeutrons = resizeArr(arrNeutrons,nNeutronArrSize + 1);
			arrNeutrons[nNeutronArrSize - 1] = ntDown;
		}
		ntLeft.column = arrbooms[nBoomIndex].column - 1;
		ntLeft.row = arrbooms[nBoomIndex].row;
		ntLeft.diraction = LEFT;
		if (arrBoard[ntLeft.row][ntLeft.column] != WALL)
		{
			arrNeutrons = resizeArr(arrNeutrons,nNeutronArrSize + 1);
			arrNeutrons[nNeutronArrSize - 1] = ntLeft;
		}
	}
	arrbooms = resizeArr(arrbooms,0);
	createFirstMat();
	loadDataToBoard();
}
// change the position of each neutron and taking care of the wall incidence (if the next step is a wall so just zero the current place)
void makeATurn()
{
	int nTempRow = 0;
	int nTempColumn = 0;
	int nIndex;
	int nIndexNeutronToErace;
	int *arrNeutronsIndexToErace;
	int nNeutronsIndexToEraceSize = 0;
	arrNeutronsIndexToErace =new int[nNeutronsIndexToEraceSize]; 
	for(nIndex = 0; nIndex < nNeutronArrSize; nIndex ++)
	{
		nTempRow = arrNeutrons[nIndex].row + diractions[arrNeutrons[nIndex].diraction].row;
		nTempColumn = arrNeutrons[nIndex].column + diractions[arrNeutrons[nIndex].diraction].column;
		if (arrBoard[nTempRow][nTempColumn] != WALL)
		{
			arrNeutrons[nIndex].row += diractions[arrNeutrons[nIndex].diraction].row;
			arrNeutrons[nIndex].column += diractions[arrNeutrons[nIndex].diraction].column;
		}
		else
		{
			arrNeutronsIndexToErace = resizeArr(arrNeutronsIndexToErace, &nNeutronsIndexToEraceSize, nNeutronsIndexToEraceSize + 1);
			arrNeutronsIndexToErace[nNeutronsIndexToEraceSize - 1] = nIndex;
		}
	}
	 std::sort(arrNeutronsIndexToErace, arrNeutronsIndexToErace + nNeutronsIndexToEraceSize, std::greater<int>());
	for(nIndexNeutronToErace = 0; nIndexNeutronToErace < nNeutronsIndexToEraceSize; nIndexNeutronToErace ++)
	{
		eraceNeutron(arrNeutronsIndexToErace[nIndexNeutronToErace]);
	}
	delete[] arrNeutronsIndexToErace;
}
// a help method return true if the number appear in the array
bool isIndexExistInArray(int *arr, int nTempIndex, int nSize)
{
	int nIndex;
	bool isExist = false;
	for(nIndex = 0; nIndex < nSize; nIndex ++)
	{
		if (arr[nIndex] == nTempIndex)
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

void removeDuplicateNeutron()
{
	int nIndexFor;
	int nIndexInFor;
	int nIndexNeutronToErace;
	int nIndexAtomArr;
	int *arrNeutronsIndexToErace;
	int nNeutronsIndexToEraceSize = 0;
	arrNeutronsIndexToErace =new int[nNeutronsIndexToEraceSize]; 
	for (nIndexFor = 0; nIndexFor < nNeutronArrSize - 1; nIndexFor ++)// the minus 1 is fuck the mehod- needs to go all over the 
	{
		for (nIndexInFor = nIndexFor + 1; nIndexInFor < nNeutronArrSize; nIndexInFor ++)
		{
			if (arrNeutrons[nIndexFor].row == arrNeutrons[nIndexInFor].row && arrNeutrons[nIndexFor].column == arrNeutrons[nIndexInFor].column)
			{
				if (isIndexExistInArray(arrNeutronsIndexToErace, nIndexFor, nNeutronsIndexToEraceSize) == false)
				{
					arrNeutronsIndexToErace = resizeArr(arrNeutronsIndexToErace, &nNeutronsIndexToEraceSize, nNeutronsIndexToEraceSize + 1);
					arrNeutronsIndexToErace[nNeutronsIndexToEraceSize - 1] = nIndexFor;
				}
				if (isIndexExistInArray(arrNeutronsIndexToErace, nIndexInFor, nNeutronsIndexToEraceSize) == false)
				{
					arrNeutronsIndexToErace = resizeArr(arrNeutronsIndexToErace, &nNeutronsIndexToEraceSize, nNeutronsIndexToEraceSize + 1);
					arrNeutronsIndexToErace[nNeutronsIndexToEraceSize - 1] = nIndexInFor;
				}
				
			}
		}
		for (nIndexAtomArr = 0; nIndexAtomArr < nAtomArrSize; nIndexAtomArr ++)
		{
			if (arrAtoms[nIndexAtomArr].row == arrNeutrons[nIndexFor].row && arrAtoms[nIndexAtomArr].column == arrNeutrons[nIndexFor].column)
			{
				atomAttack(arrAtoms[nIndexAtomArr].row, arrAtoms[nIndexAtomArr].column);
				arrNeutronsIndexToErace = resizeArr(arrNeutronsIndexToErace, &nNeutronsIndexToEraceSize, nNeutronsIndexToEraceSize + 1);
				arrNeutronsIndexToErace[nNeutronsIndexToEraceSize - 1] = nIndexFor;
				break;
			}
		}
	}
	// need to check again on the last one that didn't checked
	for (nIndexAtomArr = 0; nIndexAtomArr < nAtomArrSize; nIndexAtomArr ++)
		{
			if (arrAtoms[nIndexAtomArr].row == arrNeutrons[nIndexFor].row && arrAtoms[nIndexAtomArr].column == arrNeutrons[nIndexFor].column)
			{
				atomAttack(arrAtoms[nIndexAtomArr].row, arrAtoms[nIndexAtomArr].column);
				arrNeutronsIndexToErace = resizeArr(arrNeutronsIndexToErace, &nNeutronsIndexToEraceSize, nNeutronsIndexToEraceSize + 1);
				arrNeutronsIndexToErace[nNeutronsIndexToEraceSize - 1] = nIndexFor;
				break;
			}
		}
	std::sort(arrNeutronsIndexToErace, arrNeutronsIndexToErace + nNeutronsIndexToEraceSize, std::greater<int>());
	for(nIndexNeutronToErace = 0; nIndexNeutronToErace < nNeutronsIndexToEraceSize; nIndexNeutronToErace ++)
	{
		eraceNeutron(arrNeutronsIndexToErace[nIndexNeutronToErace]);
	}
	delete[] arrNeutronsIndexToErace;
}
