/*Ugur Sezer Asikoglu 26355 CS300 Assignment 3*/
#include<iostream>
#include<string>
#include <vector>
#include "ModifiedPriorityQueue.h"

ModifiedPriorityQueue::ModifiedPriorityQueue(int cap) /*Constructor constructor arrays with given capacity (cap)*/
{
	arrayCurrentSize = 0;  //Assign current condition and total capacity of heap array
	arrayCapacity = cap; 
	heapElement elementToAdd(0,0); /*Add a dummy node*/
	for (int i = 0; i < arrayCapacity+1; i++) /*Creates vector of location and heap with given size*/
	{
		Heap.push_back(elementToAdd);
		Location.push_back(0);
	}
}

ModifiedPriorityQueue::~ModifiedPriorityQueue() //Destructor pops out created arrays
{
	for (int i = 0; i < arrayCapacity+1; i++) /*Pop backs the location and heap array make theme empty at the end*/
	{
		Heap.pop_back();
		Location.pop_back();
	}
}

void ModifiedPriorityQueue::insert( int valueToInsert, int labelOfValue) //Insert element with given height (valueToInsert) and label of that height (label of building)
{
	if(arrayCurrentSize== arrayCapacity) /*If array is full cannot insert element*/
	{
		cout<<endl<<"Overflow Occured: Could not insert value "<<endl;
		return ;
	}
	heapElement elementToAdd(valueToInsert,labelOfValue);
	int temp,temp1,temp2;
	int hole = ++arrayCurrentSize; /*Index of array to add that element */
	Heap[hole]=elementToAdd; /*Assign element at hole index to elementToAdd*/
	Location[Heap[hole].label]=hole; /*Assign its location with its label at location array*/


	for( ; hole > 1 && valueToInsert < Heap[ hole / 2 ].value; hole /= 2 ) /*Inserts element with holding heap property this loops help to preserve heap property*/
	{
		temp = Heap[ hole ].value; 	
		temp1=Heap[ hole ].label;

		Heap[ hole ].value = Heap[ hole / 2 ].value;
		Heap[ hole ].label = Heap[ hole / 2 ].label;
		Location[Heap[ hole ].label]=hole;

		Heap[ hole / 2 ].value = temp;
		Heap[ hole / 2 ].label = temp1;
		Location[Heap[ hole/2 ].label]= hole/2;
	}
}

void ModifiedPriorityQueue::percolateDown(int i)  //Percolate down element at given index i
{
	int child;
	int tmp,tmp2;

	for(tmp=Heap[i].value,tmp2=Heap[i].label; 2*i < arrayCurrentSize; i = child ) //Hold element in tmp and checks whether there exist child of that element
	{
		child = 2*i;
		if( child != arrayCurrentSize && Heap[ child+1].value < Heap[ child ].value ) /*If right child is smaller updates that child*/
		{
			child++;
		}
		if( Heap[child ].value < tmp ) /*If value of */
		{
			Heap[i] = Heap[ child ];
			Location[Heap[child].label]=i;
		}
		else
		{
			break;
		}
	} 
	Heap[ i ].value = tmp;
	Heap[ i ].label = tmp2;
	Location[Heap[i].label]=i;

}
int ModifiedPriorityQueue::Remove(int labelToRemove)/*Removes element with given label*/
{
	int itemToDelete=Heap[Location[labelToRemove]].value; /*Assigned returned element to itemToDelete and returns at the end*/
	Heap[Location[labelToRemove]]=Heap[arrayCurrentSize];  /*Assigned element with labelToRemove with last element*/
	arrayCurrentSize--;  //Decrease current size cause we delete that

	if(arrayCurrentSize>1) /*If there exist more than 1 element percolates down*/
	{
		percolateDown(Location[labelToRemove]); //percolateDown to preserve minHeap property
	}
	else /*Otherwise only 1 or 0 element condition update their location*/
	{
		Location[Heap[1].label]=1;
	}
	Location[labelToRemove]=-1; //Assign location of deleted label building to -1 
	return itemToDelete;
}
int ModifiedPriorityQueue::GetMax() /*Return maximum element of array*/
{
	int maxValue=0;
	for (int i = 1; i <= arrayCurrentSize; i++) /*Iterator over array*/
	{
		if(Heap[i].value> maxValue) /*if value in heap is larger than maxValue*/
		{
			maxValue=Heap[i].value; /*updates maxValuee*/
		}
	}
	return maxValue; /*End of for loop returns max*/
}
bool ModifiedPriorityQueue::isEmpty()const /*Checks whether array is empty if its empty return true*/
{
	if(arrayCurrentSize==0) /*If our current size is 0 that means array is empty(But in reality its not)*/
	{
		return true;
	}
	else /*Otherwise currently there exist elements in array*/
	{
		return false;
	}
}
void swap(int & x, int & y) /*Swaps given item x and y values*/
{ 
	int temp = x; 
	x = y; 
	y = temp; 
} 
void percDown( vector<Edge> &a, int i, int n )
{
	int child;
	Edge tmp;

	for(tmp=a[i] ; 2*i < n; i = child )
	{
		child = 2*i;
		if( child != n-1 && a[ child  ].x < a[ child+1 ].x )
			child++;
		if( a[child ].x > tmp.x )
			a[i] = a[ child ];
		else
			break;
	} 
	a[ i ] = tmp;
}
void heapsort(vector<Edge> & a)
{
	for(int i= a.size()/2; i >=0;i--) /*Builds heaps with given locations by i*/
	{
		percDown(a, i, a.size()); //perc down that locations to make min heap propert
	}

	// sort
	for(int j = a.size()-1; j >0; j--)
	{
  	   swap(a[0], a[j]);  // swap max to the last pos.
       percDown(a, 0, j); // re-form the heap
	}
}