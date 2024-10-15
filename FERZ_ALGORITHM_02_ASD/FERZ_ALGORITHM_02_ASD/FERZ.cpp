#include <iostream>
#include <chrono> // for measuring time
#include <stdexcept> 
using namespace std;
using namespace chrono;

// game board output
void printBoard(int** arr, int N) {
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) {
			cout << arr[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// checking the setting of the queen
bool isSafe(int** arr, int x, int y, int N)
{
	// can move along the row where it stands
	// can move along the column where it stands
	// can move diagonally
	// row - row			// x
	// col - column			// y

	// Checking for going beyond the boundaries of the board
	if (x < 0 || x >= N || y < 0 || y >= N) {
		return false;
	}

	// Checking the row
	for (int row = 0; row < N; ++row) {
		if (arr[row][y] == 1) {
			return false;
		}
	}

	// Checking the column
	for (int col = 0; col < N; ++col) {
		if (arr[x][col] == 1) {
			return false;
		}
	}

	// Checking the diagonal (down to the right)
	int row = x, col = y;
	while (row < N && col < N) {
		if (arr[row][col] == 1) {
			return false;
		}
		row++;
		col++;
	}

	// Checking the diagonal  (up to the left)
	row = x, col = y;
	while (row >= 0 && col >= 0) {
		if (arr[row][col] == 1) {
			return false;
		}
		row--;
		col--;
	}

	// Checking the diagonal  (up to the right)
	row = x, col = y;
	while (row < N && col >= 0) {
		if (arr[row][col] == 1) {
			return false;
		}
		row++;
		col--;
	}

	// Checking the diagonal  (down to the left)
	row = x, col = y;
	while (row >= 0 && col < N) {
		if (arr[row][col] == 1) {
			return false;
		}
		row--;
		col++;
	}

	return true;
}

int counter = 0;

bool Solver(int** arr, int x, int N)
{
	if (x == N) {
		printBoard(arr, N);
		counter++;
	}
	// The loop iterates through all columns of the current row `x`
	for (int col = 0; col < N; ++col) {
		try {
			if (isSafe(arr, x, col, N)) {
				arr[x][col] = 1;

				if (Solver(arr, x + 1, N)) {
					return true;
				}

				// backtrack
				arr[x][col] = 0;
			}
		}
		catch (const out_of_range& e) {
			cerr << "Error: " << e.what() << endl;
		}
	}
	return false;
}

int main()
{
	int m;
	while (true) {
		cout << "Enter the board size (M): ";
		cin >> m;

		// Checking the correctness of the input
		if (m > 0) {
			break; 
		}
		else {
			cerr << "Error: The board size must be greater than 0." << endl;
		}
	}

	// Checking the correctness of the input
	if (m <= 0) {
		cerr <<"Error: The board size must be greater than 0 " << endl;
		return 1;
	}

	// Allocating memory for an array of pointers to strings
	int** board = new int* [m];
	// We allocate memory for each row
	// "board[i]" is a pointer to the ith line
	// m is the number of columns in each row
	for (int i = 0; i < m; ++i) {
		board[i] = new int[m];
		for (int j = 0; j < m; ++j) {
			board[i][j] = 0;
		}
	}

	// Time measurement
	auto start = high_resolution_clock::now();
	cout << "Start solvind" << endl;
	Solver(board, 0, m);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(end - start);

	// Time output
	cout << "Time to solving: " << duration.count() << " seconds" << endl;

	// Output of possible arrangements
	cout << "The number of possible arrangements: " << counter << endl;

	// Freeing up memory
	for (int i = 0; i < m; ++i) {
		delete[] board[i];
	}
	delete[] board;

	// x is a row
	// y is a column

	return 0;
}



