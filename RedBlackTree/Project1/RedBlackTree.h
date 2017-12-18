#pragma once
#include<string>
#include <stddef.h>

// moshkela lw fe value fel tree by3mlaha insert tany 3ady !!
#pragma once

// moshkela lw fe value fel tree by3mlaha insert tany 3ady !!

enum NodeColor {RED, BLACK };

class RedBlackTree 
{
private:
	class node {
	public:
		int data;
		NodeColor color; // RED if link from parent is red, BLACK otherwise
		node* parent;
		node* left;
		node* right;

		node() :parent(NULL), left(NULL), right(NULL), color(RED)
		{
		}

		node(int item) :data(item), parent(NULL), left(NULL), right(NULL), color(RED)
		{}
	};

	typedef node* nodePointer;
	nodePointer root;

public:

	RedBlackTree();
	void insert(int);

	void DrawTree(node* p, int indent);
	void insertfix(nodePointer&, nodePointer&);
	void rotateLeft(nodePointer&);
	void rotateRight(nodePointer&);
	public :int ColorChanged;
	//======================================
	void remove(int);
	void removefix(nodePointer);
	nodePointer successor(nodePointer ptr) {
		if (ptr->right != NULL) {
			ptr = ptr->right;
			while (ptr->left != NULL)
				ptr = ptr->left;
			return ptr;
		}
	};
	//======================================
	void search(int);
	nodePointer BSTInsert(nodePointer root, nodePointer pt)
	{
		/* If the tree is empty, return a new node */
		if (root == NULL)
			return pt;

		/* Otherwise, recur down the tree */
		if (pt->data < root->data)
		{
			root->left = BSTInsert(root->left, pt);
			root->left->parent = root;
		}
		else if (pt->data > root->data)
		{
			root->right = BSTInsert(root->right, pt);
			root->right->parent = root;
		}

		/* return the (unchanged) node pointer */
		return root;
	}
	//======================================
	void postOrderDelete(nodePointer ptr);
	void Draw(int array[]);
	~RedBlackTree();
};