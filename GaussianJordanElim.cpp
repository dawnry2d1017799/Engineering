#include <bits/stdc++.h>
#include <conio.h>
#include <math.h>

#include <iostream>
using namespace std;

const int FLAG_WEIRD = 0;
const int FLAG_POSSIBLE = 1;
const int FLAG_NO_SOLUTION = 2;
const int FLAG_INFINITE_SOLUTION = 3;
const int MATRIX_MAX_DIMEN = 10;

int numberOfEquation;
float matrix[MATRIX_MAX_DIMEN][MATRIX_MAX_DIMEN];
float result[MATRIX_MAX_DIMEN] = {0};

// Function display the matrix
void printMatrix(float arr[][MATRIX_MAX_DIMEN], int equationLength) {
    for (int rowCounter = 0; rowCounter < equationLength; rowCounter++) {
        for (int columnCounter = 0; columnCounter < equationLength + 1;
             columnCounter++) {
            if (columnCounter == equationLength) {
                cout << "|  " << arr[rowCounter][columnCounter];
            } else {
                cout << arr[rowCounter][columnCounter];
            }
            cout << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

int solve() {
    int flag = FLAG_POSSIBLE;

    for (int i = 0; i < numberOfEquation; i++) {
        if (matrix[i][i] == 0) {
            int temp = 1;
            while ((i + temp) < numberOfEquation && matrix[i + temp][i] == 0)
                temp++;
            if ((i + temp) == numberOfEquation) {
                flag = FLAG_WEIRD;
                break;
            }
            for (int j = i, k = 0; k <= numberOfEquation; k++)
                swap(matrix[j][k], matrix[j + temp][k]);
        }

        // To echelon form
        for (int j = 0; j < numberOfEquation; j++) {
            if (i != j) {
                float pro = matrix[j][i] / matrix[i][i];
                for (int k = 0; k <= numberOfEquation; k++)
                    matrix[j][k] = matrix[j][k] - (matrix[i][k]) * pro;
            }
        }
    }

    if (flag == FLAG_POSSIBLE) {
        for (int i = 0; i < numberOfEquation; i++) {
            result[i] = matrix[i][numberOfEquation] / matrix[i][i];
        }
    } else if (flag == FLAG_WEIRD) {
        // Check accuracy of the result.
        int consistencyFlag = FLAG_NO_SOLUTION;
        for (int i = 0; i < numberOfEquation; i++) {
            int sum = 0;
            for (int j = 0; j < numberOfEquation; j++) {
                sum = sum + matrix[i][j];
                if (sum == matrix[i][j])
                    consistencyFlag = FLAG_INFINITE_SOLUTION;
            }
        }

        if (consistencyFlag == FLAG_INFINITE_SOLUTION) {
            cout << "Has infinite solution!";
        } else {
            cout << "No solution!";
        }
    } else {
        cout << "Unable to solve, no possible solution found";
    }
}

char getNthVariable(int n)
{
    assert(n >= 1 && n <= 26);
    return "xyzdefghijklmnopqrstuvwabc"[n-1];
}

void printResult() {
    cout << "The result is: \n";
    for (int i = 0; i < numberOfEquation; i++) {
        cout << getNthVariable(i+1) << ": " << result[i] << "\n";
    }
}

void askInput() {
    // Ask user the number of equation to add.
    cout << "-Enter the number of equations: \t";
    cin >> numberOfEquation;

    for (int rowCounter = 0; rowCounter < numberOfEquation; rowCounter++) {
        cout << "--Enter the coeficients for the equation: " << rowCounter + 1
             << "\n";
        for (int columnCounter = 0; columnCounter <= numberOfEquation;
             columnCounter++) {
            cout << "\n--Coefficient: " << columnCounter + 1 << ": ";
            cin >> matrix[rowCounter][columnCounter];
        }

        cout << "\n";
    }

    printMatrix(matrix, numberOfEquation);
}

// This function is use for testing!
void test() {
    const int testCaseMatrix[4][5] = {{2, 1, -1, 2, 5},
                                      {0, 3, -1, 2, -1},
                                      {0, 0, -1, 4, 11},
                                      {0, 0, 0, 2, 6}};
    numberOfEquation = 4;
    for (int i = 0; i < numberOfEquation; i++) {
        for (int j = 0; j < numberOfEquation + 1; j++) {
            matrix[i][j] = testCaseMatrix[i][j];
        }
    }

    printMatrix(matrix, numberOfEquation);
    solve();
    printResult();
}

int main() {
    // test();
    askInput();
    solve();
    printResult();
    return 0;
}
