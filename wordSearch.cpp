#include <iostream> // For input/output stream
#include <fstream> // For file streaming
#include <string> // For getline

using namespace std;

ifstream inputFile; // Input file stream
int nRows, nCols; // Actual rows and cols of matrix
const int MAX_SIZE_ROWS = 100, MAX_SIZE_COLS = 100; // Sets constant size of rows and cols to be filled, can be changed
char charArray[MAX_SIZE_ROWS][MAX_SIZE_COLS]; // Set constant size of matrix dimensions
bool notFoundWord = true; // Check for remaining words not found in matrix
string listOfMovies = "\nCouldn't find these movies: \n"; // Concatenate strings for outputting the words not found at end of program

bool openForReading(ifstream& infile, string fileName) {
	infile.open(fileName); // Open name of the file
	if (infile.good()) // then the file opened just fine
		return true;
	else {
		perror("Can't open the specified input file");
		cout << "The file name used was: " << fileName << endl;
		cout << "Enter another file name to use (or type 'quit'): ";
		getline(cin, fileName);
		if (fileName != "quit") {
			cout << "--- The new file name is: " << fileName << endl;
			//note the use of recursion below
			return openForReading(infile, fileName);
		}
		else {
			cout << "Quitting at user's request." << endl;
			return false;
			exit(0); // Quit as fail safe
		}
	}
} //openForReading

void skipAnyCommentLines(ifstream& infile) {
	string textLine;
	char ch;
	ch = infile.peek();
	while (ch == '#' || ch == '\n') {
		getline(infile, textLine);
		ch = infile.peek();
	}
	//when we leave, we're at a non-comment, non-blank line
} //skipAnyCommentLines

void displayArray() {
	cout << "\nNumber of Rows: " << nRows << "\n" << "Number of Cols: " << nCols << "\n\n";

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			cout << charArray[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}	// displayArray

void notFound(string wordNotFound) {
	listOfMovies = listOfMovies + wordNotFound + "\n";
	// notFoundWord = true;
}

void readArray(ifstream& infile) {
	infile >> nRows >> nCols; // Read actual dimensions
	skipAnyCommentLines(inputFile); // Skip instructions comment to read array

	char readChars; // Temporary variable to read characters from file

	// Reads each character in matrix into 2D charArray
	for (int row = 0; row < nRows; row++) {
		for (int col = 0; col < nCols; col++) {
			infile >> readChars; // The char in the file
			charArray[row][col] = readChars; // Store the char in the file into the same pos of the matrix
		}
	}
	skipAnyCommentLines(inputFile); // Skip comments after reading array
	//displayArray();
}	// readArray

// If there is a space in the string, go to next letter to search in charArray
// Note the counter is passed by reference
void checkWordSpace(string word, int& counter) {
	if (word[counter] == ' ')
		counter++;
}

// ***Repeat similar process for directions***
// Rows and columns decrement by 1 at the same time to move up and left
void searchTopLeft(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int initialCol = col;
	int counter = 0;
	row -= 1; // Check 2nd letter starting left from 1st letter
	col -= 1; // Check 2nd letter starting above 1st letter

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if char in array matches char in string, and also check bounds of array (word can't go above or left of matrix size)
		if ((charArray[row][col] == word[counter]) && (row > -1) && (col > -1)) {
			row--; // Move up 1 and compare next char
			col--; // Move left 1 and compare next char
		}
		else { // Word can't be found
			break;
		}
	}
	// Done searching, found match of string with matrix, report location
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: NW\n\n";
		notFoundWord = false; // Word was found, check in each direction until done
	}
}	// searchTopLeft

// Only rows change, decreaing to move upward in the given column
void searchUpwards(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int counter = 0;
	row -= 1; // Check 2nd letter starting above 1st letter

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if char array matches word string, check bounds (word can't go above height of matrix)
		if ((charArray[row][col] == word[counter]) && (row > -1)) {
			row--; // Move up 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << col + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: N\n\n";
		notFoundWord = false;
	}
}	// searchUpwards

// Rows will decrease to go up, and cols will increase to go right
void searchTopRight(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int initialCol = col;
	int counter = 0;
	row -= 1; // Check 2nd letter starting above 1st letter
	col += 1; // Check 2nd letter starting right from 1st letter

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go right of matrix and above it)
		if ((charArray[row][col] == word[counter]) && (col < nCols) && (row > -1)) {
			row--; // Move up 1 and compare next char
			col++; // Move right 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: NE\n\n";
		notFoundWord = false;
	}
}	// searchTopRight

// Only columns change, increasing to move right in the given row
void searchRight(string word, int row, int col, int wordLength) {
	int initialCol = col;
	int counter = 0;
	col += 1; // Check 2nd letter starting right from 1st letter

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go right of matrix)
		if ((charArray[row][col] == word[counter]) && (col < nCols)) {
			col++; // Move right 1 and compare next char
		}
		else {
			break;
		}
	}

	/*	Debug for cout-ing values
		cout << "\ncol:" << col << "\n";
		cout << "posOfWord:" << posOfWord << "\n";
		cout << "char in array:" << charArray[row][col] << "\n";
		cout << "wordLength:" << wordLength << "\n";
		cout << "Counter:" << counter;
		cout << word[counter];
	*/

	if (wordLength == counter) {
		cout << "Starts at (" << row + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: E\n\n";
		notFoundWord = false;
	}
}	// searchRight

// Rows will increase to go down, and cols will increase to go right
void searchBottomRight(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int initialCol = col;
	int counter = 0;
	row += 1; // Check 2nd letter starting from below 1st char
	col += 1; // Check 2nd letter starting right from 1st char

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go right of or below matrix)
		if ((charArray[row][col] == word[counter]) && (row < nRows) && (col < nCols)) {
			row++; // Move down 1 and compare next char
			col++; // Move right 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: SE\n\n";
		notFoundWord = false;
	}
}	// searchBottomRight

// Only rows change, increasing to move downward in the given column
void searchDownwards(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int counter = 0;
	row += 1; // Check 2nd letter starting from below 1st char

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go below matrix)
		if ((charArray[row][col] == word[counter]) && (row < nRows)) {
			row++; // Move down 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << col + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: S\n\n";
		notFoundWord = false;
	}
}	// searchDownwards

// Rows will increase to go down, and cols will decrease to go left
void searchBottomLeft(string word, int row, int col, int wordLength) {
	int initialRow = row;
	int initialCol = col;
	int counter = 0;
	row += 1; // Check 2nd letter starting from below 1st char
	col -= 1; // Check 2nd letter starting right from 1st char

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go left of and below matrix)
		if ((charArray[row][col] == word[counter]) && (col > -1) && (row < nRows)) {
			row++; // Move down 1 and compare next char
			col--; // Move left 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << initialRow + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: SW\n\n";
		notFoundWord = false;
	}
}	// searchBottomLeft

// Only columns change, decreasing to move left in the given row
void searchLeft(string word, int row, int col, int wordLength) {
	int initialCol = col;
	int counter = 0;
	col -= 1; // Check 2nd letter starting right from 1st char

	while (counter < wordLength) {
		counter++;

		checkWordSpace(word, counter);

		// Check if array char matches word string, check bounds (word can't go left of matrix)
		if ((charArray[row][col] == word[counter]) && (col > -1)) {
			col--; // Move left 1 and compare next char
		}
		else {
			break;
		}
	}
	if (wordLength == counter) {
		cout << "Starts at (" << row + 1 << "," << initialCol + 1 << ")\n";
		cout << "The word " << word << " was found\n";
		cout << "Direction: W\n\n";
		notFoundWord = false;
	}
}	// searchLeft

// Search all 8 directions
void searchAll(string word, int row, int col, int wordLength) {
	searchTopLeft(word, row, col, wordLength);
	searchUpwards(word, row, col, wordLength);
	searchTopRight(word, row, col, wordLength);
	searchRight(word, row, col, wordLength);
	searchBottomRight(word, row, col, wordLength);
	searchDownwards(word, row, col, wordLength);
	searchBottomLeft(word, row, col, wordLength);
	searchLeft(word, row, col, wordLength);

}	// searchAll

void search(ifstream& infile) {
	string word;

	while (!infile.eof()) {
		notFoundWord = true;
		getline(infile, word);
		int lengthWord = word.length();

		// int row = 0, col = 0; Debug for keeping row to continue search (fail to traverse next row after cols)

		for (int row = 0; row < nRows; row++) {
			for (int col = 0; col < nCols; col++) {
				//cout << "word " << word << "row " << row << "col " << col << "length of word " << lengthWord;
				if (charArray[row][col] == word.at(0)) {
					searchAll(word, row, col, lengthWord);
				}
			}
		}
		if (notFoundWord == true) { // Word is not found
			notFound(word); // Report word
		}
		skipAnyCommentLines(inputFile);
	}
	cout << listOfMovies;
	/*	Debug code for look for first char of word
		for (int i = 0; i < nRows; i++) {
			for (int j = 0; j < nCols; j++) {
				if (lookForChar == 'x')
			}
		}
	*/
}	// search

int main() {
	char choice = 'y';
	string fileName;

	while (choice == 'y') { // User wants to play again
		choice = ' '; // Initialize char
		// const int numPuzzleRows = 0, numPuzzleColumns = 0;

		cout << "Enter in the name of your file: "; // Prompt initial file entrance
		getline(cin, fileName); // File may have space (string)

		if (openForReading(inputFile, fileName)) { // Ask user for file and open it if possible
			skipAnyCommentLines(inputFile); // Skip initial comments in file
			readArray(inputFile);
			displayArray();
			search(inputFile);
			inputFile.close(); // Done with reading file that was inputted

			listOfMovies = "\nCouldn't find these movies: \n"; // Resetting to prepare for next file
			cout << "\nWould you like to play again? (Type 'y' for yes)\n"; // Prompt user
			cin >> choice; // Takes in user's choice
			cout << "\n";
			cin.ignore(); // Doesn't read empty line
			// fileName = "";
		}
	}
}	// main