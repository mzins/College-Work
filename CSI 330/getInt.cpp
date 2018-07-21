#include <iostream>
using namespace std;

int getInt(int min) {
// PURPOSE: Insure that we get a good int
// INPUT  : The minimum value that the int can take, default to 0 if 
//          if nothing entered.
// OUTPUT : valid int

  int a;
  cin >> a;

  while ( !cin || a < min ) {
    if (!cin) {                 // only fix if broken
      cin.clear();		// fix cin
      cin.ignore(100,'\n'); 	// clear the input buffer
    }
    cout << "Please enter an integer equal to or greater than: " << min;
    cin >> a;
  } 
  return a;
} // end getInt ()
