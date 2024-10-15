#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>


using namespace std;

// Function for searching for the maximum element in a range using recursion
int MaxElement(vector<int>::iterator l, vector<int>::iterator r)
{
    // Printing the current values of the iterators
    cout << "Calling a function with a range: [" << *l << ", " << *r << "]" << endl;
    
	// If the iterators point to the same element
    // then we return this element
	if (l == r)
	{
		return *l;
	}

    // We find the middle element
	vector<int>::iterator middle = l + distance(l, r) / 2;

	// Recursively, we find the maximum element in the left and right parts
	int first_half = MaxElement(l, middle);
	int second_half = MaxElement(middle + 1, r);

    // Printing intermediate values
    cout << "The maximum between " << first_half << " and " << second_half << " is equal to ";

    // Return the larger of the two values using the ternary operator
    int result = (first_half > second_half) ? first_half : second_half;
    cout << result << endl;

    return result;
}

int main()
{
    string choice;
    vector<int> vec;

    while (true) {
        cout << "Select the data source (1 - file, 2 - console): ";
        cin >> choice;

        try
        {
            if (choice == "1")
            {
                // Opening the file for reading
                ifstream inputFile("random.txt");

                // Checking if the file was opened successfully
                if (!inputFile.is_open()) {
                    throw runtime_error("Couldn't open the file!");
                }

                int number;
                // Read the numbers from the file and add them to the vector
                while (inputFile >> number)
                {
                    vec.push_back(number);
                }
                // Closing the file after reading
                inputFile.close();
            }
            else if (choice == "2")
            {
                cout << "Enter the numbers to add to the vector (enter 'quit' to complete):" << endl;
                string input;
                while (true) {
                    cin >> input;
                    if (input == "quit") {
                        break;
                    }
                    try {
                        // Trying to convert the input to a number
                        int num = stoi(input);
                        vec.push_back(num);
                    }
                    catch (const invalid_argument&) {
                        cout << "Error: Enter an integer or 'quit' to exit." << endl;
                    }
                }
            }
            else {
                throw invalid_argument("Wrong choice, enter 1 or 2.");
            }

            // Checking if the vector is empty after reading
            if (vec.empty()) {
                throw runtime_error("The vector is empty, there is nothing to process.");
            }

            // Find the maximum element in the vector using the MaxElement function
            int max_value = MaxElement(vec.begin(), vec.end() - 1);

            vector<int>::iterator max_iter = max_element(vec.begin(), vec.end());
            int max_index = distance(vec.begin(), max_iter);

            cout << "Max element: " << max_value << " Index: " << max_index << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        if (choice == "1" || choice == "2") {
            break;
        }
    }
}

