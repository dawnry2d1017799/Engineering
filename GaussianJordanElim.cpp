/**
    Purpose: Finds the answer of system of equations with unknown variables
   using Gauss-Jordan elimination with a N Number of Square Matrix.

    Warning: Please Don't mindlessly copy my Work,
    Read this first so that this will not be added to your code.

    @author Dawnry Davocol
    @version 1.0 9/16/2021
*/

#include <bits/stdc++.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#include <iostream>
using namespace std;

const int FLAG_NEED_CHECK = 0;
const int FLAG_POSSIBLE = 1;
const int FLAG_NO_SOLUTION = 2;
const int FLAG_INFINITE_SOLUTION = 3;
const int MATRIX_MAX_DIMEN = 10;

int mPrintCounter = 0;
int numberOfEquation;
double mMatrix[MATRIX_MAX_DIMEN][MATRIX_MAX_DIMEN];
double mResult[MATRIX_MAX_DIMEN] = {0.0};

// Function display the matrix
void printMatrix() {
    printf("Solving step: %i\n\n", ++mPrintCounter);

    for (int rowCounter = 0; rowCounter < numberOfEquation; rowCounter++) {
        for (int columnCounter = 0; columnCounter < numberOfEquation + 1;
             columnCounter++) {
            double initVal = mMatrix[rowCounter][columnCounter];
            double tempVal = initVal == 0.0 ? abs(initVal) : initVal ;

            if (columnCounter == numberOfEquation) {
                printf(":\t%f\t|", tempVal);
            } else if (columnCounter == 0) {
                printf("\t|\t%f\t", tempVal);
            } else {
                printf("%f\t", tempVal);
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

/**
 * This function use to get the arbitrary variable representation
 *base on alphabet numerical order(e.g, xyz = 1234 where x = 1 and z = 3)
 *@param n the numerical order of alphabet.
 *@return return the character in the string (based on the index of the
 *character in the string).
 */
char getNthVariable(int n) {
    assert(n >= 1 && n <= 26);
    return "xyzdefghijklmnopqrstuvwabc"[n - 1];
}

int solve() {
    int flag = FLAG_POSSIBLE;

    for (int i = 0; i < numberOfEquation; i++) {
        if (mMatrix[i][i] == 0) {
            int c = 1;
            while ((i + c) < numberOfEquation && mMatrix[i + c][i] == 0) c++;

            if ((i + c) == numberOfEquation) {
                flag = FLAG_NEED_CHECK;
                break;
            }

            for (int j = i, k = 0; k <= numberOfEquation; k++) {
                swap(mMatrix[j][k], mMatrix[j + c][k]);
            }
        }

        for (int j = 0; j < numberOfEquation; j++) {
            if (i != j) {
                float temp = mMatrix[j][i] / mMatrix[i][i];

                for (int k = 0; k <= numberOfEquation; k++) {
                    mMatrix[j][k] = mMatrix[j][k] - (mMatrix[i][k]) * temp;
                }
            }
        }

        printMatrix();
    }

    return flag;
}

void calculateResult(int flagConsistency) {
    if (flagConsistency == FLAG_INFINITE_SOLUTION)
        printf("%s\n", "Infinite Solutions Exists. ");
    else if (flagConsistency == FLAG_NO_SOLUTION)
        printf("%s\n", "No Solution Exists. ");
    else if (flagConsistency == FLAG_POSSIBLE) {
        for (int i = 0; i < numberOfEquation; i++) {
            double finalResult = mMatrix[i][numberOfEquation] / mMatrix[i][i];
            mMatrix[i][numberOfEquation] = finalResult;
            mMatrix[i][i] = 1;
            mResult[i] = finalResult;

            printMatrix();
        }
    }
}

int checkMatrixConsistency() {
    int flagResult = FLAG_NO_SOLUTION;

    for (int i = 0; i < numberOfEquation; i++) {
        int sum = 0;

        for (int j = 0; j < numberOfEquation; j++) {
            sum = sum + mMatrix[i][j];
        }

        if (sum == mMatrix[i][numberOfEquation])
            flagResult = FLAG_INFINITE_SOLUTION;
    }

    return flagResult;
}

void printFinalResult() {
    for (int i = 0; i < numberOfEquation; i++) {
        printf("%c: %.6g\n", getNthVariable(i + 1), mResult[i]);
    }
}

//---Functions for setting and getting the cursor console position.
COORD getCurrentCursorPos(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;

    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    }

    return {0, 0};
}

void setCursorPos(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
//----------------------------------------------------------------------

void constructMatrixForm() {
    for (int i = 1; i <= numberOfEquation; i++) {
        cout << "\t|";
        for (int j = 0; j <= numberOfEquation; j++) {
            cout << "\t";
        }
        cout << "|\n";
    }
}

void askInputInCascadingForm() {
    cout << "\nEnter the number of equations: ";
    cin >> numberOfEquation;
    constructMatrixForm();

    // Primary Cursor position offset
    COORD cursorPos = getCurrentCursorPos(GetStdHandle(STD_OUTPUT_HANDLE));
    int offsetX = 9;
    int offsetY = (cursorPos.Y - numberOfEquation) - 1;

    // SetConsoleCursorPosition();
    for (int r = 0; r < numberOfEquation; r++) {
        setCursorPos(offsetX, ++offsetY);

        for (int c = 0; c <= numberOfEquation; c++) {
            if (c == numberOfEquation) {
                cout << ": ";
            }

            cin >> mMatrix[r][c];

            setCursorPos(offsetX + ((c + 1) * 8), offsetY);
        }
    }

    printf("\n\n");

    // Solve the input value
    int consistencyFlag = solve();
    if (consistencyFlag == FLAG_NEED_CHECK) {
        calculateResult(checkMatrixConsistency());
    } else {
        calculateResult(consistencyFlag);
    }

    printFinalResult();
}

void test() {
    const double testCaseMatrix[3][4] = {
        {0, 2, 1, 4}, {1, 1, 2, 6}, {2, 1, 1, 7}};

    numberOfEquation = 3;
    for (int i = 0; i < numberOfEquation; i++) {
        for (int j = 0; j < numberOfEquation + 1; j++) {
            mMatrix[i][j] = testCaseMatrix[i][j];
        }
    }
}

int main() {
    string reRun = " ";
    askInputInCascadingForm();

    while (reRun != "close") {
        cout << "\n\nType \"run\" to run again or type \" close\" to close the "
                "program: ";
        cin >> reRun;
        askInputInCascadingForm();
    }

    return 0;
}
