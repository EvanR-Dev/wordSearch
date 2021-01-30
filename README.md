Summary: A 2D array (matrix) will be used to search a document of words by checking all 8 different directions

A user will be asked what file to read in, and the file will be handled by a function
If the file does not exist, then perror() will give an error message, and the user can enter a new file
The user can also choose to quit if typed (can be caps or lowercase)

A function will skip any of the comment lines found in the file, skipping directly to the word puzzle

A 2D char array will be filled with the chars found on the file by row and column

Traverse the rows of the 2 matrix by using a nested for loop O(n^2) by starting with the first row and
checking every column of this row until the char is found
If not found, then go to next row and repeat until found (form of linear search)

When the char is found, employ a search function that searches all around it
{NW, N, NE, E, SE, S, SW, W}
Each direction will have different bounds as the word will not be found if it exceeds the
dimensions of the array as given by nRows and nColumns or by simply being less than 0 for the current row and col

Changelog:
Work on direction logic using string and array comparison (2/13/20)
Use string as array of chars rather than using .at() for comparison (2/14/20)
Use bool for checking if word is finally not found after all directions (2/15/20)
Use of concatenation of strings to display words not found (2/16/20)
Fix output lines structure (consistent spacing) (2/16/20)
Fix openForReading, proper exit when quitting (2/16/20)

Comments:
An issue with memory has occurred in this program, which is due to overflowing the word search puzzle (charArray) matrix,
as well as overflowing the stirng when checking for the next character

Thus, each if statement in each direction search function has set bounds so that this doesn't happen, and also
will no longer search if the search exceeds the bounds of the array
