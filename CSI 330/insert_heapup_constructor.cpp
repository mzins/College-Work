//****************Heap up****************
void heapUp (int newlast)
{//INPUT: index number location of newly inserted node (last)
 //OUTPUT: none
 //PURPOSE: heap up node of heap so that the tree is a heap

  int parent;
  T temp;
  parent=(newlast - 1)/2;
  if(newlast> 0)                      //if new last is greater than 0, stop
  {
    if(list[parent]<list[newlast])    //parent is smaller than child
    {
      temp=list[parent];
      list[newlast]=list[parent];
      list[parent]=temp;
      heapUp(parent);
    }//end if
  }//end if
}//end heapUp()



//**********constructor************
Heap(int size)                  //default of 255 is already set in header
{
  size=(size<0)? 255:size;
  list= new <T> [size];
  last=-1;
}//end Heap constructor




//***********insertHeap******************
bool insertHeap(T &val){
  T temp;
  bool retval = false;
  if (!heampFull()){
    retval=true;
    list[last+1]=val;
    last++;
    if(last != 0){
      parent=(last-1)/2;
      if(heaplist[last]>heaplist[parent]){
        temp = heaplist[last];
        heaplist[last]=heaplist[parent];
        heaplist[parent]=temp;
        heapup(parent);
      }//end if
    }//end if
  }//end if
  return retval;
}//end insertHeap()
