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

const int FLAG_WEIRD = 0;
const int FLAG_POSSIBLE = 1;
const int FLAG_NO_SOLUTION = 2;
const int FLAG_INFINITE_SOLUTION = 3;
const int MATRIX_MAX_DIMEN = 10;
int mPrintCounter = 0;
int numberOfEquation;
double mMatrix[MATRIX_MAX_DIMEN][MATRIX_MAX_DIMEN + 1];

// Function display the matrix
void printMatrix(double matrix[][MATRIX_MAX_DIMEN + 1], int equationLength) {
    printf("Solving step: %i\n\n", ++mPrintCounter);

    for (int rowCounter = 0; rowCounter < equationLength; rowCounter++) {
        for (int columnCounter = 0; columnCounter < equationLength + 1;
             columnCounter++) {
            if (columnCounter == equationLength) {
                printf(":\t%f\t|", matrix[rowCounter][columnCounter]);
            } else if (columnCounter == 0) {
                printf("|\t%f\t", matrix[rowCounter][columnCounter]);
            } else {
                printf("%f\t", matrix[rowCounter][columnCounter]);
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

void swap_row(double matrix[][MATRIX_MAX_DIMEN + 1], int i, int j) {
    for (int k = 0; k <= numberOfEquation; k++) {
        double temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;
    }
}

int forwardElim(double matrix[][MATRIX_MAX_DIMEN + 1]) {
    for (int k = 0; k < numberOfEquation; k++) {
        int maxValIndex = k;
        int maxValue = matrix[maxValIndex][k];

        for (int i = k + 1; i < numberOfEquation; i++) {
            if (abs(matrix[i][k]) > maxValue)
                maxValue = matrix[i][k], maxValIndex = i;
            printMatrix(mMatrix, numberOfEquation);
        }

        if (!matrix[k][maxValIndex]) return k;

        if (maxValIndex != k) swap_row(matrix, k, maxValIndex);

        for (int i = k + 1; i < numberOfEquation; i++) {
            double f = matrix[i][k] / matrix[k][k];

            for (int j = k + 1; j <= numberOfEquation; j++) {
                matrix[i][j] -= matrix[k][j] * f;
                printMatrix(mMatrix, numberOfEquation);
            }

            matrix[i][k] = 0;
        }
    }
    return -1;
}

void backSubsitution(double matrix[][MATRIX_MAX_DIMEN + 1]) {
    double result[numberOfEquation];  // An array to store solution

    for (int i = numberOfEquation - 1; i >= 0; i--) {
        result[i] = matrix[i][numberOfEquation];
        for (int j = i + 1; j < numberOfEquation; j++) {
            result[i] -= matrix[i][j] * result[j];
        }
        printMatrix(mMatrix, numberOfEquation);
        result[i] = result[i] / matrix[i][i];
    }

    printf("\nSolution:\n");
    for (int i = 0; i < numberOfEquation; i++)
        printf("%c: %f\n", getNthVariable(i + 1), result[i]);
}
void gaussianElimination(double matrix[][MATRIX_MAX_DIMEN + 1]) {
    int singular_flag = forwardElim(matrix);

    if (singular_flag != -1) {
        printf("Singular Matrix.\n");

        if (matrix[singular_flag][numberOfEquation])
            printf("Inconsistent System.");
        else
            printf("Has Infinite Solution.");

        return;
    }

    backSubsitution(matrix);
}

void print(double matrix[][MATRIX_MAX_DIMEN + 1]) {
    for (int i = 0; i < numberOfEquation; i++, printf("\n"))
        for (int j = 0; j <= numberOfEquation; j++)
            printf("%lf ", matrix[i][j]);

    printf("\n");
}

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

void constructMatrixForm() {
    for (int i = 1; i <= numberOfEquation; i++) {
        cout << "|";
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
    int offsetX = 0;
    int offsetY = (cursorPos.Y - numberOfEquation) - 1;

    // SetConsoleCursorPosition();
    for (int r = 0; r < numberOfEquation; r++) {
        setCursorPos(2, ++offsetY);

        for (int c = 0; c <= numberOfEquation; c++) {
            if (c == numberOfEquation) {
                cout << ": ";
            }

            cin >> mMatrix[r][c];
            cursorPos = getCurrentCursorPos(GetStdHandle(STD_OUTPUT_HANDLE));

            // The offset is base on tab space which is 8.
            offsetX = cursorPos.X + ((c + 1) * 8);
            setCursorPos(offsetX, offsetY);
        }
    }
    cout << "\n\n";
    gaussianElimination(mMatrix);
}

// This function is use for testing!
void test() {
    const double testCaseMatrix[3][4] = {
        {3.0, 2.0, -4.0, 3.0}, {2.0, 3.0, 3.0, 15.0}, {5.0, -3, 1.0, 14.0}};

    numberOfEquation = 3;
    for (int i = 0; i < numberOfEquation; i++) {
        for (int j = 0; j < numberOfEquation + 1; j++) {
            mMatrix[i][j] = testCaseMatrix[i][j];
        }
    }

    gaussianElimination(mMatrix);
}

int main() {
    askInputInCascadingForm();
    getch();
    return 0;
}
