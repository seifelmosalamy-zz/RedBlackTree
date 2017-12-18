// RBTree.cpp : Defines the entry point for the console application.
//


#include "RedBlackTree.h"
#include<iostream>
#include<vector>
using namespace std;

int main()
{
	RedBlackTree obj;
	RedBlackTree * ptr; 

	int arr[10] = { 5,8,10,6,9,7,3,1,4,2 };


	for (int i = 0; i < 10; i++)
	{
		obj.insert(arr[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		obj.search(arr[i]);
	}
	//ptr->DrawTree(ptr->D);
	
	system("pause");
	return 0;
}

