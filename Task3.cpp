#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

const int N = 9;
int puzzle[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

bool isOriginal[N][N];
int errorCount = 0;

void displayGrid() {
    cout << "\n   Sudoku Board:\n";
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "   ------+-------+------\n";
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0) cout << "   ";
            if (puzzle[i][j] == 0) cout << ". ";
            else cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (puzzle[row][i] == num || puzzle[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (puzzle[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool isComplete() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (puzzle[i][j] == 0)
                return false;
    return true;
}

bool giveHint() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(i, j, num)) {
                        cout << "\nHint: Try placing " << num << " at row " << i + 1 << ", column " << j + 1 << endl;
                        return true;
                    }
                }
            }
        }
    }
    cout << "\nNo hints available!\n";
    return false;
}

int main() {
    srand(time(0));
    time_t startTime = time(0);

    // Mark original puzzle cells
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            isOriginal[i][j] = (puzzle[i][j] != 0);

    cout << " Welcome to Console Sudoku!\n";
    cout << "Enter your move: row col number (1-9)\n";
    cout << "Enter 0 0 0 to quit, or type 'hint' for a suggestion.\n";

    while (true) {
        displayGrid();
        cout << "\n Mistakes: " << errorCount << "\n";

        if (isComplete()) {
            time_t endTime = time(0);
            int totalTime = (int)(endTime - startTime);
            displayGrid();
            cout << "\n Congratulations! You solved the puzzle.\n";
            cout << "⏱ Time taken: " << totalTime << " seconds.\n";
            cout << " Total mistakes: " << errorCount << endl;
            break;
        }

        string input;
        cout << "\nEnter Number in this Format Like:(Row Column Number) or 'Hint': ";
        cin >> input;

        if (input == "hint") {
            giveHint();
            continue;
        } else {
            int row = stoi(input);
            int col, num;
            cin >> col >> num;

            if (row == 0 && col == 0 && num == 0) {
                cout << "\nGame exited.\n";
                break;
            }

            row--; col--;
            if (row < 0 || row >= N || col < 0 || col >= N || num < 1 || num > 9) {
                cout << "Invalid input. Try again.\n";
                continue;
            }

            if (isOriginal[row][col]) {
                cout << "Cannot change original number.\n";
                continue;
            }

            if (isValid(row, col, num)) {
                puzzle[row][col] = num;
                cout << "Number placed successfully.\n";
            } else {
                cout << "Invalid move! Try again.\n";
                errorCount++;
            }
        }
    }

    return 0;
}
