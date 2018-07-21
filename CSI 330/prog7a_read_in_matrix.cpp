//NAME: Madelaine Zinser
//DATE: 11/11/15
//PURPOSE: Read in a matrix from a file via a function. Send matrix to 
//         add and multiply functions

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const bool DEBUG=false;

float ** matrix(int &s)
{
  float **ary=new float*[s];
  for(int i=0; i<s; i++)
  {
    ary[i]=new float[s];
  }
  return ary;
}//end matrix

void displayMatrix(float**t, int size); 
float** multiply(float**A, float **B, int size);
float** add(float **A, float **B, int size);

int main ()
{
  int size, choice=0;
  float **m1, **m2, **m3, johncena;
  string filename, inputfilename;
  ifstream inputfile;
  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }
  inputfile>>size;

  m1=matrix(size);
  m2=matrix(size);
  m3=matrix(size);

  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      inputfile>>johncena;
      m1[i][j]=johncena;
    }
  }
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      inputfile>>johncena;
      m2[i][j]=johncena;
    }
  }
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      m3[i][j]=0;
    }
  }

  do{
    cout<<"Do you want to\n1)Add and display Matrix 1&2\n";
    cout<<"2)Multiply and display Matrix 1&2\n";
    cout<<"3)Display all Matries\n4)Quit :(\n";
    cin>>choice;

    switch(choice)
    {
      case 1:
        m3=add(m1, m2, size);
        cout<<"Matrix 1 + Matrix 2\n";
        displayMatrix(m3, size);
        break;
      case 2:
        m3=multiply(m1, m2, size); 
        cout<<"Matrix 1 X Matrix 2;\n";
        displayMatrix(m3, size);
        break;
      case 3:
        cout<<"Matrix 1:\n";
        displayMatrix(m1, size);
        cout<<"Matrix 2:\n";
        displayMatrix(m2, size);
        cout<<"Matrix 3:\n";
        displayMatrix(m3, size);
        break;
      case 4:
        cout<<"See Ya!\n";
        break;
      default:
        break;       
    }

  }while(choice!=4);

  cout<<endl<<endl;

  return 0;
}

void displayMatrix(float **a, int size)
{
// INPUT  : a square matrix, size of the matrix
// OUTPUT : matrix
// PURPOSE: Display the matrix neatly
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      cout<<setw(3)<<a[i][j]<<"\t";
    }
    cout<<endl;
  }
}


float** add(float **A, float **B,int size) 
{// INPUT  : 2 square matrix, size of the matrices
 // OUTPUT : The resultant sum matrix
 // PURPOSE: Add two matricies
 float **C;
 C=matrix(size);
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      C[i][j]=A[i][j]+B[i][j];
    }
  }
  return C;
}

float**  multiply(float**A, float** B, int size)
{// INPUT  : 2 square matrix, size of the matrices
 // OUTPUT : The resultant product matrix
 // PURPOSE: Multiply two matricies
 float**C;
 C=matrix(size);
 DEBUG && cout<<"Made it here to multiply\n";
  for(int i=0; i<size; i++)
  {DEBUG && cout<<"First for loop i="<<i<<endl;
    for(int j=0; j<size; j++)
    {DEBUG && cout<<"Second for loop j="<<j<<endl;
      C[i][j]=0;
      for(int k=0; k<size; k++)
      {DEBUG && cout<<"Third for loop k="<<k<<endl;
        C[i][j]=C[i][j]+(A[i][k]*B[k][j]);
      }
    }
  }DEBUG && cout<<"Survived all 3 for loops\n";
  return C;
}

