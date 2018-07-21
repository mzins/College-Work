// NAME: Jim Feher
// DATE: 01/12/10
// Program to test the size of various data elements
// two decent links:
// http://www.cs.bsu.edu/homepages/peb/cplusplus/headers/climits.htm
// http://www.cs.bsu.edu/homepages/peb/cplusplus/headers/cfloat.htm

#include <iostream>
#include <climits>
#include <cfloat>
using namespace std;

int main () { 
  int i;
  char c;
  float f;
  short s;
  double d;
  long int l;
  bool b;
  long long ll;

  cout << "The size of an int is " << sizeof(i) << " byte(s).\n";
  cout << "The size of a char is " << sizeof(c) << " byte(s).\n";
  cout << "The size of a short is " << sizeof(s) << " byte(s).\n";
  cout << "The size of a long int is " << sizeof(l) << " byte(s).\n";
  cout << "The size of a bool is " << sizeof(b) << " byte(s).\n";
  cout << "The size of a float is " << sizeof(f) << " byte(s).\n";
  cout << "The size of a double is " << sizeof(d) << " byte(s).\n";
  cout << "The size of a long long is " << sizeof(ll) << " byte(s).\n";

  // use the climits and cfloat to check your answers from below
  cout << "Maximum values for: \n"
       << "int:\t" << INT_MAX << endl
       << "char:\t" << CHAR_MAX << endl
       << "short:\t" << SHRT_MAX << endl
       << "long:\t" << LONG_MAX << endl
       << "float:\t" << FLT_MAX << endl
       << "double:\t" << DBL_MAX << endl
       << "long double:\t" << LDBL_MAX << endl
       << "Number of digits in a float: " << FLT_DIG << endl
       << "Number of digits in a double: " << DBL_DIG << endl
       << "Number of digits in a long double: " << LDBL_DIG << endl;
  
  return 0; 
} // end main

// Now answer the following questions and put them after the comment
// when you submit your program.

// 1. What is the largest signed int that can be represented, why?
//signed ints range between -(2^32)-1 and (2^31)-1. -4294967295 would be the
//most negative number. 2147483647 would be the greatest positive int.

// 2. What is the largest unsigned char that can be represented, why?
//(2^7)-1=127 127 is 'DEL'

// 3. What is the largest signed short that can be represented, why?
//The most negative short is -(2^16)-1=-65535. The most positive short is (2^15)//-1=32767.

// 4. What is the largest signed long int that can be represented, why?
// NOTE:  Use commented code to check work from 1-4.
//The most negative long int is -(2^64)-1=-1,844674407E19. The most positive
//long int is (2^63)-1=9,223372037E18.

// 5. Will all systems have the same limitiations?  Why or why not?
//If the system does not store variable types with the same number of bytes, 
//they will have varying limitations. 

// 6. How can you easily check the limitations of the size for a system?
//You can check the limitations of the size by running a program like this. 
//The sizeof() function in c++ will display the number of bytes used.
