//Madelaine Zinser
//12/10/2015
//Open and read in names with SS numbers use a map and a 2D array 
//to store elements and describe efficiency

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

void insertSort (string [][2], int);
string binarySearch(string [][2], int, string);

string ** Matrix (){
  string **ary = new string *[1000];
  for(int i=0; i<1000; i++)
    ary[i]=new string [2];
  return ary;
}//end Matrix()

int main ()
{
  string filename, inputfilename;
  ifstream fin;
  map<string,int> mymap;
  typedef std::map<std::string,int>::iterator it_type; 
  string tempname, tempssn, searcher, data[10000][2];
  int size;
  while(!fin.is_open()){
    cout<<"Input filename: ";
    getline(cin, inputfilename);
    fin.open(inputfilename.c_str(), ios :: in | ios :: binary);
  }//end while
  int i=0;
  while(fin>>tempname>>tempssn){
    data[i][0]=tempname;
    data[i][1]=tempssn;
    i++;
  }//end while
  size=i;

  mymap["JimFeher"] = 555669999;
  mymap["MadelaineZinser"] = 222113333;
  mymap["GregOrtiz"] = 444229999;

  for(it_type iterator = mymap.begin(); iterator !=mymap.end(); iterator++){
    string key = iterator->first;
    int value = iterator->second;
    cout << key <<"\t" << value << "\n";
  }//end for
  bool test=true;
  int val;
  string person;
  cout<<"Who do you want to search for int the map?\n";
  getline(cin, person);

  try{
    val=mymap.at(person);
  } catch(const out_of_range & oor){
    test=false;
  }
  if(test)
    cout << person << ": " << val << endl;
  else
    cout << person << " is not in the list\n";

  insertSort(data, size);

  for(int x; x<size; x++)
    cout<<data[x][0]<<"\t"<<data[x][1]<<endl;
  cout<<"Who do you want to search for?\n";
  getline(cin, searcher);
  cout<<searcher<<": "<<binarySearch(data, size, searcher)<<endl;





  return 0;
}



void insertSort(string l[][2], int size){
  string temp, tempnum;
  const bool DEBUG =false;
  int walker;
  for(int cur=1; cur<size; cur++){
    temp=l[cur][0];
    tempnum=l[cur][1];
    for(walker=cur-1;walker>=0&& temp<l[walker][0];walker--){
      l[walker+1][0]=l[walker][0];
      l[walker+1][1]=l[walker][1];
      DEBUG && cout<<"\n    walker is: "<<walker<<endl;
    }//end for
    l[walker+1][0]=temp;
    l[walker+1][1]=tempnum;
    DEBUG && cout<<"\n outter for walker is: "<<walker<<endl;
  }//end for

  /*cout<<"\nin function after sort\n";
  for(int x=0; x<size+1; x++)
    cout<<"x: " << x << "\t" << l[x][0]<<"\t "<<l[x][1]<<endl; 
  cout<<endl;*/
}//end insertSort()

string binarySearch(string m[][2], int size, string name){

  int first=0, last=size-1, middle, position=-1;
  bool found=false;
  string ssn;

  while(!found && first <= last){
    middle=(first+last)/2;
    if(m[middle][0]==name){
      found=true;
      ssn=m[middle][1];
    }//end if
    else if(m[middle][0] > name)
      last=middle-1;
    else
      first=middle+1;
  }//end while
  if(!found)
    ssn="Sorry we do not have that person";
  return ssn;
}//end binarySearch()
