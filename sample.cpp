//Gauss elimination for solving LPP
#include<iostream>
#include<conio.h>
#include<math.h>
#include <bits/stdc++.h>
using namespace std;

const int MATRIX_MAX_DIMEN = 10;
const int testMatrix[3][4] ={{ 1, 1, 1, 3 },
                     { 1,2, 3, 0 },
                     { 1, 3, 2, 3 }};
int numberOfEquation;
float matrix[MATRIX_MAX_DIMEN][MATRIX_MAX_DIMEN];
float result[MATRIX_MAX_DIMEN]={0};

//Function display the matrix
void printMatrix(float arr[][MATRIX_MAX_DIMEN], int equationLength){
	for(int rowCounter=0; rowCounter<equationLength; rowCounter++){
		for(int columnCounter=0; columnCounter<equationLength+1; columnCounter++){
            if(columnCounter == equationLength){
                cout<< "|  " << arr[rowCounter][columnCounter];
            }else{
                cout<< arr[rowCounter][columnCounter];
            }
			cout<<"\t";
		}
		cout<<"\n";
	}	
	cout<<"\n";
}

void solve(){
     int flag = 0;
    // Performing elementary operations
    
    for (int i = 0; i < numberOfEquation; i++){
        if (matrix[i][i] == 0){
            int temp = 1;
            while ((i + temp) < numberOfEquation && matrix[i + temp][i] == 0)
                temp++;           
            if ((i + temp) == numberOfEquation) {
                flag = 1;
                break;
            }
            for (int j = i, k = 0; k <= numberOfEquation; k++)
                swap(matrix[j][k], matrix[j+temp][k]);
        }

        for (int j = 0; j < numberOfEquation; j++) {
            if (i != j) {
                float pro = matrix[j][i] / matrix[i][i];
                for (int k = 0; k <= numberOfEquation; k++)                
                    matrix[j][k] = matrix[j][k] - (matrix[i][k]) * pro;               
            }
        }
    }

    for (int i = 0; i < numberOfEquation; i++)        
              cout << matrix[i][numberOfEquation] / matrix[i][i] << " ";
}

void askInput(){
    //Ask user the number of equation to add.
    cout<<"-Enter no of equation: \t";
    cin>>numberOfEquation;

    for(int rowCounter=0; rowCounter < numberOfEquation; rowCounter++)
      {
          cout<<"--Enter the coeficients for the equation: "<< rowCounter+1 << "\n";
          for(int columnCounter = 0;columnCounter <= numberOfEquation; columnCounter++){
              cout<<"\n--Coefficient: " << columnCounter + 1 <<": ";
              cin>>matrix[rowCounter][columnCounter];
          }

          cout << "\n";
      }

     printMatrix(matrix, numberOfEquation);
}

void test(){
    for(int i =0; i < 3; i++){
        for(int j = 0;  j < 4; j++){
            matrix[i][j] = testMatrix[i][j];
        }
    }
    numberOfEquation = 3;
    printMatrix(matrix,3);
    solve();
}

int main(){
    test();
    return 0;
}

