//Madelaine Zinser
//Sort a list up to 10,000,000 integers form a user specified file
//  using insertion, quick, and a sort from the standard library
//12/6/2015

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void insertSort(int [], int, int);
void quickSort(int [], int, int);
int partition(int [], int, int);
double findMedian (const int list[], int size);
double findMedian (vector <int> const &v);
int setpivot(int a[], int start, int end);

int main(){
  int temp, size;
  int diff_time, i_time;
  int* list = new int[20000000];

  vector<int> vect;
  vector<int> :: iterator iterP;

  string filename, inputfilename;
  ifstream inputfile;

  while(!inputfile.is_open())
  {
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    inputfile.open(inputfilename.c_str(), ios::in | ios::binary);
  }

  cout<<fixed<<showpoint<<setprecision(2);
  //Reading in list and finding size
  size= 0;
  while (inputfile >> temp) {
    list[size++] = temp;
    vect.push_back(temp);
  }

  i_time = time(0);
  sort(vect.begin(), vect.end());
  cout<<"Sorted median is "<<findMedian(vect);
  diff_time = time(0) - i_time;
  cout<<"\nVector sorted "<<vect.size()<<" numbers in ";
  cout<<diff_time<< " seconds\n";

  i_time = time(0);
  insertSort(list, 0, size-1);
  diff_time = time(0) - i_time;
  cout<<"Insert sorted "<< vect.size()<<" numbers in ";
  cout<<diff_time<< " seconds\n";
  
  cout<<"list[0]: "<<list[0]<<" list[size-1]: ";
  cout<<list[size-1]<<endl;

  
  i_time = time(0);
  quickSort(list, size, size-1);
  diff_time = time(0) - i_time;
  cout<<"Quick sorted "<< vect.size()<<" numbers in ";
  cout<<diff_time<< " seconds\n";

  cout<<"Median of array is: "<<findMedian(list, size);

  cout<<"\nMedian of vector is: "<<findMedian(vect);
  cout<<endl<<endl;
  return 0;
}  
	
void insertSort(int l[], int first, int last) {
// INPUT:   array of ints list of size size 
// OUTPUT:  sorted array
// PURPOSE: Sort the array of ints
// NOTE:    Adapted from page 556 of Gilberg
  int hold;
  int walker;

  for (int cur = first + 1; cur <= last; cur++) {
    hold = l[cur];
    // find spot to put the temp item
    for (walker = cur-1; walker >= first && hold < l[walker]; walker--) {
      // shift each item up to make space for the new one
      l[walker+1] = l[walker];
    }
    // now put the new item in place
    l[walker+1] = hold;
  }
} // end insertSort

void quickSort(int arr[], int start, int end){
//INPUT: pointer to list of numbers, starting and ending indexes
//OUTPUT: none
//PURPOSE: sort list from starting index to ending index
  if(end-start<=16){
    insertSort(arr, start, end);
  }//end if

  else if(start < end){
    //Partition the array and get the pivot point
    int p=partition(arr, start, end);

    //Sort the partition before the pivot point
    quickSort(arr, start, p-1);

    //Sort the partition after the pivot point
    quickSort(arr, p+1, end);

  }//end if
}// end quickSort
 

int partition(int arr[], int start, int end){
//INPUT: pointer to list of numbers, starting and ending indexes
//OUTPUT: pivot point
//PURPOSE: rearrange the elements from start to end so all value
//         greater or equal to the pivot are on the right of the 
//         pivot and all of the values less than are on the left
//         of the pivot

  int pivotPosition=setpivot(arr, start, end);
  int pivotValue=arr[pivotPosition];

  //Rearrange the rest of the array elements to partition
  for(int pos=start+1; pos<=end; pos++){
    if(arr[pos] < pivotValue){
      swap(arr[pivotPosition+1], arr[pos]);
      swap(arr[pivotPosition], arr[pivotPosition+1]);
      pivotPosition++;
    }//end if
  }//end for

  return pivotPosition;
}//end partition()

double findMedian(const int v[], int size){
//INPUT: list and size
//OUTPUT: median of the list of numbers
//PURPOSE: calculate the median
  double median;
  if(size<=0){
    cout<<"Cannot find median list is empty\n";
    median=-10;
  }
  else if(size==1)
    median=v[0];
  else
    size%2==0?median=(v[size/2]+v[(size/2)-1])/2 : median=v[(size/2)];
  return median;
}//end findMedian()

double findMedian (vector <int> const &v){
//INPUT: vector of numbers
//OUTPUT: median of vector list
//PURPOSE: calculate the median
  int size=v.size();
  double median;
  if(size<=0){
    cout<<"Cannot find median vector is empty\n";
    median=-10;
  }
  else if(size==1)
    median=v[0];
  else
    size%2==0?median=(v[size/2]+v[(size/2)-1])/2 : median=v[(size/2)];
  return median;
}//end findMedian()

int setpivot(int a[], int start, int end){
//INPUT: Pointer to the array, starting index, and ending index
//OUTPUT: The correct pivot position
//PURPOSE: Check staring index value, ending index value, and find the 
//         value in the middle of the list. Of the three values find
//         the middle value and return that index
  int pivot, middle;
  middle=(end-start)/2;
  if(a[start]<=a[middle] && a[middle]<=a[end])
    pivot=middle;
  else if(a[start]<=a[end] && a[end]<=a[middle])
    pivot=end;
  else if(a[middle]<=a[start] && a[start]<=a[end])
    pivot=start;
  else if(a[middle]<=a[end] && a[end]<=a[start])
    pivot=end;
  else if(a[end]<=a[start] && a[start]<=a[middle])
    pivot=start;
  else
    pivot=middle;
  return pivot;
}//end setpivot()
