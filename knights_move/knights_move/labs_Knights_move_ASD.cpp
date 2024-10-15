#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include <chrono> // Include for timing

using namespace std;
using namespace chrono;


const int MAX_SIZE = 76; // Maximum board size (determined by a constant)
int totalMotion = 0;  // Counter of the knight's moves
int desk[MAX_SIZE][MAX_SIZE]; // A two-dimensional array representing a chessboard
int step[8][2] = { {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2} }; // Array of possible knight moves


void readKnightFile(const string& filename, int& boardSize, int& KnightRow, int& KnightCol)
{
	ifstream file(filename);

	if (!file.is_open())
	{
		throw runtime_error("The file could not be opened: " + filename);
	}

	file >> boardSize;
	if (file.fail() || boardSize < 5 || boardSize > MAX_SIZE)
	{
		throw invalid_argument("The board size must be at least 5 and no more than 76");
	}

	// Reading the initial position of the knight
	file >> KnightRow >> KnightCol;
	if (file.fail() || KnightRow < 0 || KnightCol < 0 || KnightRow > boardSize || KnightCol > boardSize)
	{
		throw out_of_range("The knight's starting position must be within the board.");
	}

	file.close();
}


void readKnightConsole(int& boardSize, int& KnightRow, int& KnightCol)
{
	bool validInput = false; // A flag indicating that the input is correct

	while (!validInput) {
		try {
			cout << "Enter the board size (number of rows and columns): ";
			cin >> boardSize;

			if (cin.fail() || boardSize < 5 || boardSize > MAX_SIZE)
			{
				throw invalid_argument("The board size must be at least 5 and no more than 10");
			}

			cout << "Enter the position of the knight (row number and column number): ";
			cin >> KnightRow >> KnightCol;

			if (cin.fail() || KnightRow < 0 || KnightCol < 0 || KnightRow > boardSize || KnightCol > boardSize)
			{
				throw out_of_range("The knight's starting position must be within the board.");
			}

			validInput = true;
		}
		catch (const exception& e) {
			cerr << "Error: " << e.what() << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

// Function for initializing the chessboard
void setDesk(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			desk[i][j] = 0;
		}
	}
}


void printDesk(int n)
{
	printf("totalMotion=%d\n", totalMotion);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			printf(" %3d", desk[i][j]);
		}
		printf("\n");
	}
}

// Function to calculate the number of available moves
int getDegree(int x, int y, int BoardSZ)
{
	int count = 0;
	for (int i = 0; i < 8; ++i)
	{
		int nextX = x + step[i][0];
		int nextY = y + step[i][1];
		if (nextX < BoardSZ && nextY < BoardSZ && desk[nextX][nextY] == 0 && nextX >= 0 && nextY >= 0){
			count++;
		}
	}
	return count;
}

bool Warnsdorff(int& x, int& y, int BoardSZ)
{
	int minDegree = 9;
	int nextX = x;
	int nextY = y;


	// Iterate through all possible moves
	for (int i = 0; i < 8; ++i)
	{
		int nx = x + step[i][0];
		int ny = y + step[i][1];
		if (nx < BoardSZ && ny < BoardSZ && desk[nx][ny] == 0 && nx >= 0 && ny >= 0)
		{
			int degree = getDegree(nx, ny, BoardSZ);
			if (degree < minDegree)
			{
				minDegree = degree;
				nextX = nx;
				nextY = ny;
			}
		}
	}

	if (minDegree == 9)
	{
		return false;
	}

	// Update the knight's position
	x = nextX;
	y = nextY;
	return true;
}

// A function that implements the knight's move algorithm
bool set_knight(int x, int y, int BoardSZ)
{
	if ((x < 0) || (x >= BoardSZ) || (y < 0) || (y >= BoardSZ))
	{
		return false;
	}

	if (desk[x][y] != 0)
	{
		return false;
	}

	// next move
	totalMotion++;
	desk[x][y] = totalMotion;

	// stop algorithm
	if (totalMotion == BoardSZ * BoardSZ) // Check for completion of the game (all cells are passed)
	{
		return true;
	}

	if (!Warnsdorff(x, y, BoardSZ))
	{
		totalMotion--;
		desk[x][y] = 0;
		return false;
	}

	printDesk(BoardSZ);

	if (set_knight(x, y, BoardSZ))
	{
		return true;
	}

	totalMotion--;
	desk[x][y] = 0;

	// If none of the moves were successful, return false
	return false;
}
//MAIN
int main()
{
	int boardSize;
	int knightRow; // The initial line of the knight's position
	int knightCol; // The initial column of the knight's position
	int choice;


	cout << "Select the input method: \n1 - from the file\n2 - from the console\nselection: ";
	cin >> choice;

	try {
		if (choice == 1) {
			readKnightFile("input.txt", boardSize, knightRow, knightCol);
		}
		else if (choice == 2) {
			readKnightConsole(boardSize, knightRow, knightCol);
		}
		else {
			throw invalid_argument("The wrong choice. Please choose 1 or 2.");
		}

		cout << "Board size: " << boardSize << "\n";
		cout << "The initial position of the knight: (" << knightRow << ", " << knightCol << ")\n";
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}

	auto start = high_resolution_clock::now(); // Start timing

	setDesk(boardSize);
	if (set_knight(knightRow, knightCol, boardSize)) {
		printDesk(boardSize);
	}
	else {
		cout << "ERROR!" << endl;
	}

	auto stop = high_resolution_clock::now(); // Stop timing
	auto duration = duration_cast<microseconds>(stop - start); // Calculate duration
	cout << "Execution time: " << duration.count() << " microseconds" << endl; // Print duration
}










