#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
//Created by Thiago Clari for my Programming 2 class
using namespace std;

int sudoku[9][9];
int original[9][9];
void generatePuzzle();
void printPuzzle(int puzzle[][9]);
void shiftThree(int puzzle[][9], int row);
void shiftOne(int puzzle[][9], int row);
void randomizeFirstPerm(int puzzle[][9]);
void fillZero(int puzzle[][9], int row);
void clearPuzzle();
void flipRows(int puzzle[][9], int row1, int row2);
void flipColumns(int puzzle[][9], int col1, int col2);
void startGame();
bool isValid(string pair, int value);
void replaceCorrect(string pair, int value);
void reprint();
int calcScore(int amountWrong);
void keepOriginal();
void resetPuzzle();
void save(int puzzle[][9], char gameSave[]);
void load(char fileName[], int puzzle[][9]);
bool isComplete();


//Randomize rows per block, so flip row 1 and 2, but not 1 and 3 since those are in different 3x3 blocks

void generatePuzzle()
{

	int i = 0;
	for (int j = 1; j < 10; j++)
	{
		sudoku[0][i] = j;
		i++;
	}
	randomizeFirstPerm(sudoku);

	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = sudoku[i - 1][j];
		}
		shiftThree(sudoku, i);
	}

	i = 3;
	for (int j = 0; j < 9; j++)
	{
		sudoku[i][j] = sudoku[i - 1][j];
	}
	shiftOne(sudoku, i);

	for (int i = 4; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = sudoku[i - 1][j];
		}
		shiftThree(sudoku, i);
	}

	i = 6;
	for (int j = 0; j < 9; j++)
	{
		sudoku[i][j] = sudoku[i - 1][j];
	}
	shiftOne(sudoku, i);

	for (int i = 7; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = sudoku[i - 1][j];
		}
		shiftThree(sudoku, i);
	}

	flipRows(sudoku, 0, 2);
	flipRows(sudoku, 1, 2);
	flipRows(sudoku, 4, 5);
	flipRows(sudoku, 6, 7);
	flipColumns(sudoku, 0, 1);
	flipColumns(sudoku, 4, 5);
	flipColumns(sudoku, 6, 7);
	flipColumns(sudoku, 7, 8);

	for (int i = 0; i < 9; i++)
	{
		fillZero(sudoku, i);
	}
	

	keepOriginal();
	startGame();

	//printPuzzle(sudoku);

	//clearPuzzle(sudoku);

}
void shiftThree(int puzzle[][9], int row)
{
	for (int i = 0; i < 3; i++)
	{
		int firstElement = puzzle[row][0];
		int j;
		for (j = 0; j < 8; j++)
		{
			puzzle[row][j] = puzzle[row][j + 1];
		}
		puzzle[row][j] = firstElement;
	}
}
void shiftOne(int puzzle[][9], int row)
{
	for (int i = 0; i < 1; i++)
	{
		int firstElement = puzzle[row][0];
		int j;
		for (j = 0; j < 8; j++)
		{
			puzzle[row][j] = puzzle[row][j + 1];
		}
		puzzle[row][j] = firstElement;
	}
}
void randomizeFirstPerm(int puzzle[][9])
{
	for (int i = 0; i < 6; i++)
	{
		int randIndex = (rand() % 9);
		int randIndex2 = (rand() % 9);

		int replaced = puzzle[0][randIndex];

		puzzle[0][randIndex] = puzzle[0][randIndex2];
		puzzle[0][randIndex2] = replaced;
	}
}
void fillZero(int puzzle[][9], int row)
{
	int loopAmount = (rand() % 9) + 1;
	int i = 0;
	while (i < loopAmount)
	{
		int col = (rand() % 9);
		puzzle[row][col] = 0;
		i++;
	}

}
void flipRows(int puzzle[][9], int row1, int row2)
{
	int temp[9];

	for (int i = 0; i < 9; i++)
	{
		temp[i] = puzzle[row1][i];
	}

	for (int i = 0; i < 9; i++)
	{
		puzzle[row1][i] = puzzle[row2][i];
		puzzle[row2][i] = temp[i];
	}
}
void flipColumns(int puzzle[][9], int col1, int col2)
{
	int temp[9];

	for (int i = 0; i < 9; i++)
	{
		temp[i] = puzzle[i][col1];
	}

	for (int i = 0; i < 9; i++)
	{
		puzzle[i][col1] = puzzle[i][col2];
		puzzle[i][col2] = temp[i];
	}
}
void startGame()
{
	cout << "Enter your desired cell by using ordered pairs, ie, (0,8)" << "\n"
		<< "would represent the top right-most cell." << "\n" <<
		"Next enter the number you wish to put in the cell." << "\n";

	printPuzzle(sudoku);
	
}
bool isValid(string pair, int value)
{
	char c = pair[1];
	const char* fPair = &c;
	char c2 = pair[3];
	const char* sPair = &c2;
	
	int firstPair = atoi(fPair);
	int secondPair = atoi(sPair);

	int i = 0;
	do
	{
		if (sudoku[firstPair][i] == value)
			return false;
		else if (sudoku[i][secondPair] == value)
			return false;
		i++;
	} while (i < 9);
	
	return true;
}
void replaceCorrect(string pair, int value)
{
	char c = pair[1];
	const char* fPair = &c;
	char c2 = pair[3];
	const char* sPair = &c2;

	int firstPair = atoi(fPair);
	int secondPair = atoi(sPair);

	sudoku[firstPair][secondPair] = value;
}
void save(int puzzle[][9], char gameSave[])
{
	ofstream fout(gameSave);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fout << puzzle[i][j] << " ";
		}
		fout << "\n";
	}
}
void load(char fileName[], int puzzle[][9])
{
	ifstream fin(fileName);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fin >> puzzle[i][j];
		}
	}
	keepOriginal();
	printPuzzle(sudoku);
}
bool isComplete()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
				return false;
			
		}
	}
	return true;
}
int calcScore(int amountWrong)
{
	return 100 - amountWrong;
}
void keepOriginal()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			original[i][j] = sudoku[i][j];
		}
	}
}
void resetPuzzle()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = original[i][j];
		}
	}
}
void clearPuzzle()
{
	delete[] sudoku;
	delete[] original;
}
void printPuzzle(int puzzle[][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}
void reprint()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	srand(time(NULL));
	int amountWrong = 0;
	string pair = "";
	int value = 0;
	int saveResponse = 0;
	int menuSelect = 0;
	int puzzleSelect = 0;
	char fileName[256] = "";

	do
	{
		cout << "\n" <<" MENU " << "\n"
			<< "1) Create a new puzzle." << "\n"
			<< "2) Load a previously created puzzle." << "\n"
			<< "3) Exit the program." << "\n";
		cin >> menuSelect;
		switch (menuSelect)
		{
		case 1:
			generatePuzzle();
			
			do
			{
				cout << "Type 1 to enter values." << "\n"
					<< "Type 2 to restart puzzle." << "\n"
					<< "Type 3 to quit puzzle." << "\n";
				cin >> puzzleSelect;
				switch (puzzleSelect)
				{
				case 1:
					cout << "Enter cell location: " << "\n";
					cin >> pair;
					cout << "\n" << "Enter value: " << "\n";
					cin >> value;

					if (isValid(pair, value))
					{
						cout << "correct!" << "\n" << "\n";
						replaceCorrect(pair, value);
						
						if (isComplete())
						{
							cout << "Congratulations, you have completed the board! Your final score is: " << calcScore(amountWrong);
							exit;
						}
						reprint();
					}
					else
					{
						cout << "incorrect." << "\n";
						amountWrong++;
						reprint();
					}
					break;
				case 2:
					resetPuzzle();
					reprint();
					amountWrong = 0; //Ask if supposed to also reset this
					break;
				case 3:
					cout << "Here is your current score: " << calcScore(amountWrong) << "\n";

					cout << "Would you like to save your puzzle?" << "\n"
						<< "Type 1 for Yes, and 2 for No." << "\n";
					cin >> saveResponse;
					switch (saveResponse)
					{
					case 1:
						cout << "Enter desired save name followed by .txt, ie, mypuzzle.txt" << "\n";
						cin >> fileName;
						save(sudoku,fileName);
						cout << "File has been saved." << "\n";
						break;
					case 2:
						cout << "Thank you for playing!";
						break;
					}
					break;
				}
			} while (puzzleSelect != 3);
		break;
		case 2:
			cout << "Enter puzzle name " << "\n";
			cin >> fileName;
			cout << "Puzzle successfully loaded, now printing" << "\n" << "\n";
			load(fileName, sudoku);
			
			do
			{
				cout << "Type 1 to enter values." << "\n"
					<< "Type 2 to restart puzzle." << "\n"
					<< "Type 3 to quit puzzle." << "\n";
				cin >> puzzleSelect;
				switch (puzzleSelect)
				{
				case 1:
					cout << "Enter cell location: " << "\n";
					cin >> pair;
					cout << "\n" << "Enter value: " << "\n";
					cin >> value;

					if (isValid(pair, value))
					{
						if (isComplete())
						{
							cout << "Congratulations, you have completed the board! Your final score is: " << calcScore(amountWrong);
							exit;
						}
						
						cout << "correct!" << "\n" << "\n";
						replaceCorrect(pair, value);
						reprint();
					}
					else
					{
						cout << "incorrect." << "\n";
						amountWrong++;
						reprint();
					}
					break;
				case 2:
					resetPuzzle();
					reprint();
					amountWrong = 0; //Ask if supposed to also reset this
					break;
				case 3:
					cout << "Here is your current score: " << calcScore(amountWrong) << "\n";

					cout << "Would you like to save your puzzle?" << "\n"
						<< "Type 1 for Yes, and 2 for No." << "\n";
					cin >> saveResponse;
					switch (saveResponse)
					{
					case 1:
						cout << "Enter desired save name followed by .txt, ie, mypuzzle.txt" << "\n";
						cin >> fileName;
						save(sudoku, fileName);
						cout << "File has been saved." << "\n";
						break;
					case 2:
						cout << "Thank you for playing!";
						break;
					}
					break;
				}
			} while (puzzleSelect != 3);
			break;
		case 3:
			cout << "Now exiting";
			clearPuzzle();
			break;
		}
	} while (menuSelect != 3);
	
	return 0;
}