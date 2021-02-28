/*Ugur Sezer Asikoglu */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "ModifiedPriorityQueue.h"

using namespace std;


bool hasDuplicates(const vector<int>& arr) /*Checks Whether There exist elements with same edge(x)*/
{
	for (int i = 0; i < arr.size(); ++i)  
	{
		for (int j = i + 1; j < arr.size(); ++j) 
		{
			if (arr[i] == arr[j])
			{
				return true;
			}
		}
	}
	return false;
}
void percDownHeight( vector<Edge> &a, int i, int n ) /*Percolate down of element with sustaining minHeap property for their height*/
{
	int child;
	Edge tmp;

	for(tmp=a[i] ; 2*i < n; i = child )
	{
		child = 2*i;
		if( child != n-1 && a[ child  ].height < a[ child+1 ].height )
			child++;
		if( child != n-1 && a[ child  ].height < a[ child+1 ].height )
			child++;
		if( a[child ].height > tmp.height )
			a[i] = a[ child ];
		else
			break;
	} 
	a[ i ] = tmp;
}
void heapsortHeight(vector<Edge> & a) /*Firstly sort edges height cause in same location different height building case condition first higher building should be inserted and deleted*/
{
	for(int i= a.size()/2; i >=0;i--) /*Builds heaps with given locations by i*/
	{
		percDown(a, i, a.size()); //perc down that locations to make min heap propert
	}

	// sort
	for(int j = a.size()-1; j >0; j--)
	{
  	   swap(a[0], a[j]);  // swap max to the last pos.
       percDownHeight(a, 0, j); // re-form the heap
	}
}

int main()
{
	ifstream file;
	int givenSize,xLeft,xRight,height,label=0,maxHeight=0,removedItem;
	bool duplicateCheck;
	string FileName="input.txt",Lines;
	file.open(FileName.c_str());

	getline(file,Lines);
	stringstream line_stream(Lines);
	line_stream>>givenSize; /*Takes the number of buildings to create size of array*/

	
	vector<int> xLeftCoordinates;
	vector<Edge> edgesArray;

	while(getline(file,Lines)) /*Helps to read txt file line by line as a loop*/
	{
		stringstream line_stream(Lines);
		while( ( (line_stream>>xLeft) >>height) >>xRight )
		{
			Edge leftEdgeToAdd(xLeft,label,true,height); /*Creates Left edge to push vector*/
			Edge rightEdgeToAdd(xRight,label,false,height); /*Creates Right edge to push vector*/

			xLeftCoordinates.push_back(xLeft); /*Push both coordinates to check duplicate in same x coordinate*/
			xLeftCoordinates.push_back(xRight);
			edgesArray.push_back(leftEdgeToAdd);
			edgesArray.push_back(rightEdgeToAdd);
			label++; /*Increase label of each building*/
		}
	}

	duplicateCheck=hasDuplicates(xLeftCoordinates); /*Checks wheether there exist a duplicate and return boolean duplicateCheck*/
	heapsortHeight(edgesArray);
	heapsort(edgesArray); /*Sorts the edge of arrays with heap sort*/
	ModifiedPriorityQueue myHeap(givenSize); /*Creats a heap with capacity of numbere of buildings*/


	for(int i=0;i<edgesArray.size();i++) /*Loops ýterator over all the edges*/
	{
		if (i==0) /*If its first edge and not in x=0 that means our origin is 0 and no building in there so height is also 0*/
		{
			if(edgesArray[i].x!=0)
			{
				cout<<"0 0"<<endl;
			}
		}
		if(edgesArray[i].left) //Left edge condition
		{
			if(myHeap.isEmpty()&&!duplicateCheck) /*If every element is unique and list is not empty insert and prints out comin left element*/
			{
				myHeap.insert(edgesArray[i].height,edgesArray[i].label); /*Inserts height of building with given label and its label*/
				cout<<edgesArray[i].x<<" "<<myHeap.GetMax()<<endl; /*Prints out x of that element and Max Building height in my heap*/
				maxHeight=myHeap.GetMax(); /*updates current maxheight to understand further changes*/
			}
			else /*If list is not empty and there exist duplicate at same coordinates enters this part*/
			{
				while(edgesArray[i].left)/*Left edge condition This while loop insert element until gets an right edge of building*/
				{
					myHeap.insert(edgesArray[i].height,edgesArray[i].label);
					if(maxHeight<myHeap.GetMax()&&edgesArray[i+1].x!=edgesArray[i].x) /*If max height changes and next element is not in same index prints out */
					{
						cout<<edgesArray[i].x<<" "<<myHeap.GetMax()<<endl;
						maxHeight=myHeap.GetMax(); /*As max height changee we should assign new max to maxHeight*/
					}
					else if(edgesArray[i+1].x==edgesArray[i].x&&!edgesArray[i+1].left&&maxHeight<myHeap.GetMax()) /*If next edge is in same x location but its right which means end of building and our max height changes enters */
					{
						cout<<edgesArray[i].x<<" "<<myHeap.GetMax()<<endl;
						maxHeight=myHeap.GetMax(); /*As max height changee we should assign new max to maxHeight*/
					}
					i++; /*For iteration of while loop we should increase i index in edgesArray*/
				}
				i--; /*Removes extra increase of i after end of while loop*/
			}
		}
		else /*Right edge condition*/
		{
			while(!myHeap.isEmpty()&&!edgesArray[i].left) /*While list is not empty and edge is right removes that buildings from heaep*/
			{
				removedItem=myHeap.Remove(edgesArray[i].label); /*remove building i with given label and returns removedItem as height of removed building*/
				if(myHeap.GetMax()<removedItem&&i+1<=edgesArray.size()-1&&edgesArray[i+1].x!=edgesArray[i].x) /*If removed building height was max one and next edge x is not equal to current x*/
				{
					cout<<edgesArray[i].x<<" "<<myHeap.GetMax()<<endl;
					maxHeight=myHeap.GetMax();
				}
				else if(myHeap.GetMax()<removedItem &&!myHeap.isEmpty())//
				{
					maxHeight=myHeap.GetMax();
				}
				i++;
			}
			i--;
			if(i==edgesArray.size()-1) /*If its end of edge then(List is empty) prints out last edge and max which is 0*/
			{
				cout<<edgesArray[i].x<<" "<<myHeap.GetMax()<<endl;
				maxHeight=myHeap.GetMax();
			}
		}
	}
    return 0;
}
