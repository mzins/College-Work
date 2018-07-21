//Madelaine Zinser
//9/14/15
//purpose: This program reads in matrices from a file. The program will
//then display the addition and multiplication of the two matricies 
//Time: 2.5 hours total
//Attempted extra credit

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_SIZE=10;
bool multiplyMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE], int size, float C[][MAX_SIZE]);
void addMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE],int size,float C[][MAX_SIZE]);
void subtractMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE],int size,float C[][MAX_SIZE]);
void displayMatrix(int size, const float A[][MAX_SIZE]);

int main ()
{
        int size;
	float A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];
	bool check;

	//Opens file and checks for import
	ifstream IN;
	IN.open("matrix.txt");
	if(!IN)
	{
		cout<<"ERROR! File not read in";
		return 0;
	}

	//Reads in matrix from file
	IN>>size;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			IN>>A[i][j];
		}
	}
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			IN>>B[i][j];
		}
	}
	cout<<"A\n";
	displayMatrix(size, A);
	cout<<"\nB\n";
	displayMatrix(size, B);
	addMatrix(A,B,size,C);
        subtractMatrix(A,B,size,C);
        check=multiplyMatrix(A,B,size,C);
	if(!check)
	{
		cout<<"/nERROR sizes are incorrect. Cannot multiply/n";
	}

	return 0;
}

void addMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE],int size,float C[][MAX_SIZE]) 
{
// INPUT  : 2 square matrix, size of the matrices
// OUTPUT : The resultant sum matrix
// PURPOSE: Add two matricies

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			C[i][j]=A[i][j]+B[i][j];
		}
	}
	cout<<"\nAddition Matrix\n";
	displayMatrix(size, C);
}

void subtractMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE],int size,float C[][MAX_SIZE]) 
{
// INPUT  : 2 square matrix, size of the matrices
// OUTPUT : The resultant sum matrix
// PURPOSE: Add two matricies

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			C[i][j]=A[i][j]-B[i][j];
		}

	}
	cout<<"\nSubtraction  Matrix(A-B)\n";
	displayMatrix(size, C);
}

bool multiplyMatrix(const float A[][MAX_SIZE], const float B[][MAX_SIZE], int size, float C[][MAX_SIZE])
{
// INPUT  : 2 square matrix, size of the matrices
// OUTPUT : The resultant product matrix
// PURPOSE: Multiply two matricies
	
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{C[i][j]=0;
			for(int k=0; k<size; k++)
			{
				C[i][j]=C[i][j]+(A[i][k]*B[k][j]);

			}
		}
	}
	cout<<"\nMultiply Matrix\n";
	displayMatrix(size,C);

	return true;

}

void displayMatrix( int size, const float A[][MAX_SIZE] ) 
{
// INPUT  : a square matrix, size of the matrix
// OUTPUT : matrix
// PURPOSE: Display the matrix neatly

		for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			cout<<setw(3)<<A[i][j]<<"\t";
		}
		cout<<endl;
	}
}
