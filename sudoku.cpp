// sudoku2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
#include<string>
#define random(min,max) min+rand()%(max-min+1)
using namespace std;

enum SwapWays {
	TRANSPORING,
	SWAP_ROWS_SMALL,
	SWAP_COLUMNS_SMALL,
	SWAP_ROWS_AREA,
	SWAP_COLUMNS_AREA
};

enum Levels {
	EASY=40,
	NORMAL=45,
	HARD=50
};

struct Cage {
	int x;
	int y;
};

Levels returnLevel(int level) {
	switch (level)
	{
	case 1:
		 return Levels::EASY;
	case 2:
		return Levels::NORMAL;
	case 3:
		return Levels::HARD;
	default:
		cout << "this level not exist" << endl;
		break;
	}
}


SwapWays returnWay(int way) {
	switch (way)
	{
	case 0:
		return SwapWays::TRANSPORING;
	case 1:
		return SwapWays::SWAP_ROWS_SMALL;
	case 2:
		return SwapWays::SWAP_COLUMNS_SMALL;
	case 3:
		return SwapWays::SWAP_ROWS_AREA;
	case 4:
		return SwapWays::SWAP_COLUMNS_AREA;
	}
}

void initBaseSqr(int** array, int n = 3) {
	int current = 1;
	for (int i = 0; i < n * n; i++) {
		for (int e = 0; e < n * n; e++) {
			array[i][e] = current;
			(current == 9) ? current = 1 : current++;
		}
		if (i == 2) current = 2;
		else if (i == 5) current = 3;
		else current = array[i][3];
	}
}

void transporting(int**& array) {
	for (int i = 0; i < 9; i++) {
		for (int e = i; e < 9; e++) {
			if (i == e) continue;
			swap(array[i][e], array[e][i]);
		}
	}
}

void swapRowsSmall(int**& array) {
	int row1 = random(0, 6);
	while (row1 % 3 != 0) {
		row1 = random(0, 6);
	}
	int row2 = row1 + random(1,2);
	for (int i = 0; i < 9; i++) {
		swap(array[row1][i], array[row2][i]);
	}
}

void swapColumnsSmall(int**& array) {
	int column1 = random(0, 6);
	while (column1 % 3 != 0) {
		column1 = random(0, 6);
	}
	int column2 = column1 + random(1,2);
	for (int i = 0; i < 9; i++) {
		swap(array[i][column1], array[i][column2]);
	}
}

void swapRowsArea(int**& array) {
	int firstRowArea1 = random(0, 3);
	while (firstRowArea1 % 3 != 0) {
		firstRowArea1 = random(0, 3);
	}
	int firstRowArea2;
	if (firstRowArea1 == 0) {
		firstRowArea2 = random(3, 6);
		while (firstRowArea2 % 3 != 0) firstRowArea2 = random(3, 6);
	}
	else firstRowArea2 = 6;
	for (int i = 0; i < 3; i++) {
		for (int e = 0; e < 9; e++) {
			swap(array[firstRowArea1+i][e], array[firstRowArea2+i][e]);
		}
	}
}

void swapColumnsArea(int**& array) {
	int firstColArea1 = random(0, 3);
	while (firstColArea1 % 3 != 0) firstColArea1=random(0, 3);
	int FirstColArea2;
	if (firstColArea1 == 0) {
		FirstColArea2 = random(3, 6);
		while (FirstColArea2 % 3 != 0) FirstColArea2 = random(3, 6);
	}
	else FirstColArea2 = 6;
	for (int i = 0; i < 3; i++) {
		for (int e = 0; e < 9; e++) {
			swap(array[e][firstColArea1 + i], array[e][FirstColArea2 + i]);
		}
	}
}

void runSwapWay(SwapWays way, int**& array) {
	switch (way)
	{
	case TRANSPORING:
		transporting(array);
	case SWAP_ROWS_SMALL:
		swapRowsSmall(array);
	case SWAP_COLUMNS_SMALL:
		swapColumnsSmall(array);
	case SWAP_ROWS_AREA:
		swapRowsArea(array);
	case SWAP_COLUMNS_AREA:
		swapColumnsArea(array);
	}
}

void swaping(int**& array) {
	int amt = random(10, 20);
	for (int i = 0; i < amt; i++) {
		int swapWay = random(0,4);
		runSwapWay(returnWay(swapWay), array);
	}
}
int** copySpace(int** array) {
	int** copiedArray = new int* [9];
	for (int i = 0; i < 9; i++) copiedArray[i] = new int[9];
	for (int i = 0; i < 9; i++) {
		for (int e = 0; e < 9; e++) {
			copiedArray[i][e] = array[i][e];
		}
	}
	return copiedArray;
}

void sortArray(int*& array,int size) {
	if (size < 1) return;
	bool flag = true;
	for (int i = 0; i < size; i++)
	{
		for (int e = 0; e < size-1-i; e++)
		{
			if (array[e] > array[e + 1]) {
				swap(array[e], array[e + 1]);
				flag = false;
			}
		}
		if (flag) break;
	}
}



bool search(int* array,int size, int target) {
	if (size < 1) return false;
	for (int i = 0; i < size; i++) {
		if (array[i] == target) return true;
	}
	return false;
}

int* cagesToDelete(int amount) {
	int* cages = new int[amount];
	for (int i = 0; i < amount; i++) {
		int cage = random(0, 80);
		while (search(cages, i-1, cage) == true)cage = random(0, 80);
		cages[i] = cage;
	}
	sortArray(cages, amount);
	return cages;
}

Cage* createCagePoints(int* array, int size) {
	Cage* cagePoints = new Cage[size];
	for (int i = 0; i < size; i++) {
		Cage cage;
		cage.y = array[i] / 9;
		cage.x = array[i] % 9;
		cagePoints[i] = cage;
	}
	return cagePoints;
}


void deleteCages(int**& array,Cage* cages) {
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int e = 0; e < 9; e++) {
			if (i == cages[count].y and e == cages[count].x) {
				array[i][e] = 0;
				count++;
			}
		}
	}
}



void showSpace(int**& array) {
	cout << "    " << 1 << ".  " << 2 << ".  " << 3 << ".  " << 4 << ".  " << 5 << ".  " << 6 << ".  "
		<< 7 << ".  " << 8 << ".  " << 9 << endl << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << i + 1 << ".  ";
		for (int e = 0; e < 9; e++)
		{
			if (array[i][e] == 0) {
				cout << "_   ";
			}
			else {
				cout << array[i][e] << "   ";
			}
		}
		cout << endl;
		cout << endl;
	}
}

bool findCage(Cage* cages, Cage cage, int emptyCages) {
	for (int i = 0; i < emptyCages; i++)
	{
		if (cages[i].x == cage.x and cages[i].y == cage.y) return true;
	}
	return false;
}

int findIndexCage(Cage* cages, Cage cage, int emptyCages) {
	for (int i = 0; i < emptyCages; i++)
	{
		if (cages[i].x == cage.x and cages[i].y == cage.y) return i;
	}
}


void deleteCage(Cage*&cages,Cage cage,int& emptyCages) {
	int index = findIndexCage(cages, cage, emptyCages);
	Cage* buf = new Cage[emptyCages - 1];
	for (int i = 0; i < emptyCages; i++) {
		if (i < index) buf[i] = cages[i];
		else if (i == index) continue;
		else buf[i - 1] = cages[i];
	}
	delete[] cages;
	cages = buf;
	--emptyCages;
}

void replaceCage(int**& space, int answer,Cage cage) {
	space[cage.y][cage.x] = answer;
}

bool checkCol(int answer, Cage cage,int** space) {
	for (int i = 0; i < 9; i++) {
		if (space[i][cage.x] == answer) return false;
	}
	return true;
}
bool checkRow(int answer,Cage cage,int**space) {
	for (int i = 0; i < 9; i++) {
		if (space[cage.y][i] == answer) return false;
	}
	return true;
}
bool checkSqr(Cage cage,int** space,int answer) {
	int iStart, eStart;
	if (cage.x <= 2)iStart = 0;
	else if (cage.x >= 3 and cage.x <= 5) iStart = 3;
	else  iStart = 6;
	if (cage.y <= 2) eStart = 0;
	else if (cage.y >= 3 and cage.y <= 5) eStart = 3;
	else eStart = 6;
	for (int i = iStart; i < iStart+3; i++)
	{
		for (int e = eStart; e < eStart + 3; e++) {
			if (i == cage.x and e == cage.y) continue;
			if (space[i][e] == answer) return false;
		}
	}
	return true;
}
bool checkAnswerIn(int answer,Cage cage,int**space) {
	if (checkCol(answer,cage,space) == true && checkRow(answer,cage,space) == true && checkSqr(cage,space,answer) == true) return true;
	else return false;
}


void checkAnswer(int x, int y, int answer, int** correctSpace,int **& space, Cage*& cages, int& emptyCages) {
	Cage cage{ x,y };
	bool flag = findCage(cages,cage,emptyCages);
	if (flag){
		if (correctSpace[y][x] == answer ) {
			cout << "correct answer" << endl;
			replaceCage(space, answer,cage);
			deleteCage(cages, cage, emptyCages);
		}
		else if (checkAnswerIn(answer,cage,space) == true) {
			cout << "correct answer" << endl;
			replaceCage(space, answer, cage);
			deleteCage(cages, cage, emptyCages);
		}
		else {
			cout << "answwer isn't correct, try agian" << endl;
			return;
		}
	}
	else {
		cout << "this cage isn't empty" << endl;
		return;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
    srand(time(NULL));
	int** correctSpace = new int* [9];
	for (int i = 0; i < 9; i++) correctSpace[i] = new int[9];
	initBaseSqr(correctSpace);
	swaping(correctSpace);
	int** copiedArray = copySpace(correctSpace);
	bool work = true;
	while (work) {
		cout << "1. start game" << endl << "2. rules" << endl << "0. exit" << endl;
		int buttonMainMenu;
		cout << "player: ";
		cin >> buttonMainMenu;
		switch (buttonMainMenu)
		{
		case 1:
		{
			system("cls");
			bool game = true;
			int level;
			cout << "1.easy" << endl << "2.normal" << endl << "3.hard" << endl;
			cout << "your level: ";
			cin >> level;
			system("cls");
			int emptyCages = returnLevel(level);
			Cage* cagePoints = createCagePoints(cagesToDelete(emptyCages), emptyCages);
			deleteCages(copiedArray, cagePoints);
			while (game) {
				cout << "введите х=10 если хотите выйти из игры" << endl;
				//cout << " введите х=11 если хотите получить подсказку" << endl;
				showSpace(copiedArray);
				int x, y;
				cout << "x: ";
				cin >> x;
				if (x == 10) {
					game = false;
					system("cls");
					break;
				}
				cout << "y: ";
				cin >> y;
				int answer;
				cout << "answer: ";
				cin >> answer;
				
				if (y > 9 or answer > 9 or x>10) cout << "вы вышли за пределы!" << endl;
				if (y <= 0 or answer <= 0 or x <= 0) cout << "вы вышли за пределы!" << endl;
				else checkAnswer(--x, --y, answer, correctSpace, copiedArray, cagePoints, emptyCages);
				if (emptyCages == 0) {
					system("cls");
					cout << "good job!" << endl;
					game = false;
				}
				Sleep(2000);
				system("cls");
				continue;
			}
			break;
		}
		case 2: {
			cout << "вам дана таблица 9х9 с пропущенными значениями, вам необходимо заполнить эти пропуски так, чтобы значения не повторялись в квадрате 3х3, в строке и в столбце." << endl;
			cout << "ответ вводится по координатам. (пример х: 1; у: 3). x-по горизонтали;у-по вертикали" << endl;
			cout << "введите любой символ, чтобы выйти" << endl;
			string symb;
			while (symb=="")getline(cin,symb);
			system("cls");
			break;
		}
		case 0:
			system("cls");
			work = false;
			break;
		default:
			break;
		}
	}
}


