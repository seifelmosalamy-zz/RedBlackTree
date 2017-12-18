#include "RedBlackTree.h"
#include<iostream>
#include <stddef.h>
#include<cassert>
#include<string>
#include<vector>
#include <iomanip> 
using namespace std;

RedBlackTree::RedBlackTree() :root(NULL)
{}

void RedBlackTree::insert(int value) {
	nodePointer pt = new node(value);

	// Do a normal BST insert
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations
	insertfix(root, pt);
};

void RedBlackTree::insertfix(nodePointer &root, nodePointer &newPtr) {
	nodePointer parent = NULL;
	nodePointer grand_parent = NULL;

	while ((newPtr != root) && (newPtr->color != BLACK) && (newPtr->parent->color == RED))
	{
		parent = newPtr->parent;
		grand_parent = newPtr->parent->parent;

		if (parent == grand_parent->left) { // Case A: Parent of ptr is left child of Grand-parent of ptr 
			nodePointer uncle = grand_parent->right;

			// Case 1:  The uncle of ptr is also red Only ( Recoloring required )
			if (uncle != NULL && uncle->color == RED) {
				grand_parent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				newPtr = grand_parent; //!!!!!!!
			}

			else { // Case 2: ptr is right child of its parent Left-rotation required
				if (newPtr == parent->right) {
					rotateLeft(parent);
					newPtr = parent;
					parent = newPtr->parent; //!!!!
				}
				// Case 3: ptr is left child of its parent Right-rotation required
				else {
					rotateRight(grand_parent);
					swap(parent->color, grand_parent->color);
					newPtr = parent;
				}
			}
		}

		else { // Case : B Parent of ptr is right child of Grand-parent of ptr
			nodePointer uncle = grand_parent->left;

			// Case : 1 The uncle of ptr is also red Only Recoloring required 
			if ((uncle != NULL) && (uncle->color == 'r')) {
				grand_parent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				newPtr = grand_parent;
			}
			else
			{
				// Case : 2 ptr is left child of its parent Right-rotation required
				if (newPtr == parent->left) {
					rotateRight(parent);
					newPtr = parent;
					parent = newPtr->parent;
				}

				// Case : 3 ptr is right child of its parent Left-rotation required 
				else {
					rotateLeft(grand_parent);
					swap(parent->color, grand_parent->color);
					newPtr = parent;
				}
			}
		}
	}
	root->color = BLACK;
}

void RedBlackTree::rotateLeft(nodePointer &ptr)
{
	nodePointer pt_right = ptr->right;

	ptr->right = pt_right->left;

	if (ptr->right != NULL)
		ptr->right->parent = ptr;

	pt_right->parent = ptr->parent;

	if (ptr->parent == NULL)
		root = pt_right;

	else if (ptr == ptr->parent->left)
		ptr->parent->left = pt_right;

	else
		ptr->parent->right = pt_right;

	pt_right->left = ptr;
	ptr->parent = pt_right;
}

void RedBlackTree::rotateRight(nodePointer &ptr)
{
	nodePointer pt_left = ptr->left;

	ptr->left = pt_left->right;

	if (ptr->left != NULL)
		ptr->left->parent = ptr;

	pt_left->parent = ptr->parent;

	if (ptr->parent == NULL)
		root = pt_left;

	else if (ptr == ptr->parent->left)
		ptr->parent->left = pt_left;

	else
		ptr->parent->right = pt_left;

	pt_left->right = ptr;
	ptr->parent = pt_left;
}

void RedBlackTree::remove(int value) {
	nodePointer ptr = root;
	nodePointer ptr2 = NULL;
	nodePointer ptr3 = NULL;
	bool found = false;

	if (root == NULL) {
		cerr << "*** Red Black Tree is EMPTY ***" << endl;
		return;
	}

	while (ptr != NULL && found == false) { // search!
		if (ptr->data == value)
			found = true;
		if (found == false) {
			if (ptr->data < value)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
	}
	if (found == false) {
		cerr << "**** Element Not Found ****" << endl;
		return;
	}
	else {
		cout << "Deleted Element: " << ptr->data << endl;
		cout << "Node is Deleted" << endl;
	}
	//====================================================
	if (ptr->left == NULL || ptr->right == NULL)
		ptr2 = ptr;
	else
		ptr2 = successor(ptr);
	if (ptr2->left != NULL)
		ptr3 = ptr2->left;
	else
		ptr3 = ptr2->right;
	ptr3->parent = ptr2->parent;
	if (ptr2->parent == NULL)
		root = ptr;
	else {
		if (ptr2 == ptr2->parent->left)
			ptr2->parent->left = ptr;
		else
			ptr2->parent->right = ptr;
	}

	if (ptr2 != ptr)
		ptr->data = ptr2->data;

	if (ptr2->color == BLACK)
		removefix(ptr2);
}

void RedBlackTree::removefix(nodePointer ptr) {
	nodePointer ptr2;

	while (ptr != root && ptr->color == BLACK)
	{
		if (ptr == ptr->parent->left)
		{
			ptr2 = ptr->parent->right;

			if (ptr2->color == RED)
			{
				ptr2->color = BLACK;
				ptr->parent->color = RED;
				rotateLeft(ptr->parent);
				ptr2 = ptr->parent->right;
			}

			if (ptr2->left->color == BLACK && ptr2->right->color == BLACK)
			{
				ptr2->color = RED;
				ptr = ptr->parent;
			}
			else if (ptr2->right->color == BLACK)
			{
				ptr2->left->color = BLACK;
				ptr2->color = RED;
				rotateRight(ptr2);
				ptr2 = ptr->parent->right;
			}

			ptr2->color = ptr->parent->color;
			ptr->parent->color = BLACK;
			ptr2->right->color = BLACK;
			rotateLeft(ptr2->parent);
			ptr = root;
		}
		else
		{
			ptr2 = ptr->parent->left;

			if (ptr2->color == RED)
			{
				ptr2->color = BLACK;
				ptr->parent->color = RED;
				rotateRight(ptr->parent);
				ptr2 = ptr->parent->left;
			}

			if (ptr2->right->color == BLACK && ptr2->left->color == BLACK)
			{
				ptr2->color = RED;
				ptr = ptr->parent;
			}
			else if (ptr2->left->color == BLACK)
			{
				ptr2->right->color = BLACK;
				ptr2->color = RED;
				rotateLeft(ptr2);
				ptr2 = ptr->parent->left;
			}

			ptr2->color = ptr->parent->color;
			ptr->parent->color = BLACK;
			ptr2->left->color = BLACK;
			rotateRight(ptr->parent);
			ptr = root;
		}
	}
	ptr->color = BLACK;
}

void RedBlackTree::search(int value)
{
	string color;
	string ParentIsRoot;
	if (root == NULL) {
		cerr << "*** Red Black Tree is EMPTY ***" << endl;
		return;
	}
	nodePointer ptr = root;
	bool found = false;
	while (ptr != NULL && found == false)
	{
		if (ptr->data == value)
			found = true;
		if (found == false) {
			if (ptr->data < value)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}
	}
	if (found == false)
		cerr << "**** Element Not Found ****" << endl;
	else
	{
		
		if (ptr->color == 1)
		{
			color = "Red";
			
		}
		else if(ptr->color== 0){
	
			color = "Black";
			
			}
		if (ptr->parent == NULL)
		{ 
			cout << "Node found: " << ptr->data << endl;
			cout << "It's color is: " << ptr->color << endl;
			cout << "This node has no parent ,It's the root!" << endl;
		}
		else
		{
			cout << "Node found: " << ptr->data << endl;
			cout << "It's color is: " << color << endl;
			cout << "It's parent is " << ptr->parent->data << endl;
		}
	
	
			
	}
}

void RedBlackTree::Draw(int array[])
{
	
}

void RedBlackTree:: DrawTree(node* p, int indent =0)
{
	if (p != NULL) {
		if (p->right) {
			DrawTree(p->right, indent + 4);
		}
		if (indent) {
			cout << setw(indent) << ' ';
		}
		if (p->right) cout << " /\n" << setw(indent) << ' ';
		cout << p->data << "\n ";
		if (p->left) {
			cout << setw(indent) << ' ' << " \\\n";
			DrawTree(p->left, indent + 4);
		}
	}
}
/* 
void RedBlackTree:: getLine(const node *root, int depth, vector<int>& vals)
{
	if (depth <= 0 && root != nullptr) {
		vals.push_back(root->data);
		return;
	}
	if (root->left != nullptr)
		getLine(root->left, depth - 1, vals);

	else if (depth - 1 <= 0)
		vals.push_back(placeholder);

	if (root->right != nullptr)
		getLine(root->right, depth - 1, vals);

	else if (depth - 1 <= 0)
		vals.push_back(placeholder);
}*/


void RedBlackTree::postOrderDelete(nodePointer ptr) {
	if (ptr != NULL)
	{
		postOrderDelete(ptr->left);
		postOrderDelete(ptr->right);
		delete(ptr);
	}
}

RedBlackTree::~RedBlackTree() {
	postOrderDelete(root);
}
