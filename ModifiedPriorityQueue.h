/*Ugur Sezer Asikoglu 26355*/
#include <iostream>

using namespace std;

struct Edge /*Helper Coordinate struct to hold edge inside a struct form*/
{
	int label,x,height;
	bool left; /*If its left side edge its true*/
	Edge(int xGiven, int labelGiven, bool leftGiven,int heightGiven)
	{
		x = xGiven;
		label = labelGiven;
		left=leftGiven;
		height=heightGiven;
	}
	Edge()
	{
	}
};
struct heapElement /*Struct for array of heap type cause we hold both value and its label*/
{
	int label,value;
	heapElement(int valueGiven, int labelGiven)
	{
		value = valueGiven;
		label = labelGiven;
	}
	heapElement()
	{
		value=0;
		label=0;
	}
};


class ModifiedPriorityQueue
{
	public:
		ModifiedPriorityQueue(int capacity); //Constructor
		~ModifiedPriorityQueue();            //Destructor
		bool isEmpty( ) const;               //Checks whether list is empty
		int Remove(int label);				 //Remove item with given label
		int GetMax();						//Return Maximum element of array
		void insert( int value, int label); // Insert element with given height(value) and labele
		void deleteMin( int & minItem );

	private:
		int arrayCurrentSize; // Number of elements in heap
		int arrayCapacity;    // Max capacity of array
		vector<heapElement> Heap;       // The heap array
		vector<int> Location;           //The location array
		void percolateDown( int hole );  // Percolate down with from hole index
};
void percDown( vector<Edge> &a, int i, int n ); //helper function percDown for heap sort 
void swap(int & x, int & y);     //helper function swap for heap sort 
void heapsort(vector<Edge> & a); //helper function swap for sort the array of edges




