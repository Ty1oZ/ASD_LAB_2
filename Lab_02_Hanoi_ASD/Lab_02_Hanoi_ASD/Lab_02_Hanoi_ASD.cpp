#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <stdexcept>

using namespace std;

// Recursive function for solving the Hanoi Towers problem
void han(int n, int startKernel, int finishKernel)
{
	// Base case: if the number of disks is 1
	if (n == 1)
	{
		cout << "Move disk " << n << " from " << startKernel << " to " << finishKernel << endl;
		return;
	}

	// Auxiliary rod
	int helpKernel = 6 - startKernel - finishKernel;
	// Recursive call to move n-1 disks from the initial to the auxiliary rod
	han(n - 1, startKernel, helpKernel);
	// Moving the nth disk from the initial to the final rod
	cout << "Move disk " << n << " from " << startKernel << " to " << finishKernel << endl;
	han(n - 1, helpKernel, finishKernel);
}

// Function for reading the number of disks from a file
int readFromFile(const string& filename)
{
	ifstream inputFile(filename);
	if (!inputFile)
	{
		throw runtime_error("File opening error: " + filename);
	}

	int n;
	inputFile >> n;
	if (inputFile.fail() || n <= 0)
	{
		inputFile.close(); 
		throw invalid_argument("Incorrect data in the file! Make sure it contains a positive integer.");
	}

	inputFile.close(); 
	return n; // Returning the read number of disks
}

int main()
{
	int n;
	int choice;
	cout << "The Hanoi Towers Challenge" << endl;
	
	// Choose between console input and file input
	cout << "Hello, if you want to read the data on the number of disks from the file, ";
	cout << "then press 0, and if you want to enter from the keyboard, then press 1: ";
	
	while (true) {
		cin >> choice;

		// Checking the input of choice for correctness
		if (cin.fail() || (choice != 0 && choice != 1)) {
			cin.clear(); // clearing the cin state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignoring incorrect input
			cerr << "Invalid input! Please enter 0 or 1." << endl;
			cout << "Try again: ";
		}
		else {
			break; // exit the loop if the input is correct
		}
	}

	if (choice == 0)
	{
		string filename;
		cout << "Enter the filename: ";
		cin >> filename;
		cout << endl << endl;

		try
		{
			n = readFromFile(filename);
		}
		catch (const runtime_error& e)
		{
			cerr << e.what() << endl;
		}
		catch (const invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	}
	else if(choice == 1)
	{
		cout << "Enter the number of disks: ";
		cin >> n;
		cout << endl << endl;

		if (cin.fail() || n <= 0)
		{
			cerr << "The number of disks must be a positive integer!" << endl;
		}
	}
	// Calling a function to solve a problem
	han(n, 1, 3);
}

