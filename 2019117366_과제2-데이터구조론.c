#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> // needs for making boolean variables
#include <time.h> // needs for generating random numbers
#define _CRT_SECURE_NO_WARNINGS //disable error
#pragma warning(disable:4996) // disable error 
#define RANGE_NUMBER 100 // Define the maximum range for generated numbers(Possible to change), the minimum is 1 

// define TreeNode Structure
typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

// # Searching Algorythm
TreeNode* search(TreeNode* node, int key) {
	// # Check if TreeNode is not empty
	if (node == NULL) return NULL;
	// # Check if value of root key is equal to searching key
	if (key == node->key) { 
		return node; 
	}
	// # Recursion Algorigthm for searching element in subtrees
    // # if value of key is lower than root key go to *LEFT* subtree	
	else if (key < node->key) {
		return search(node->left, key);
	}
	// # if value of key is greater than root key go te *RIGHT* subtree
	else {
		return search(node->right, key);
	}
	 
}
// # Memory allocation for TreeNode
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}



// # Insert node to tree
TreeNode* insert_node(TreeNode* node, int key) {
	// # if node does not exist create new node
	if (node == NULL) return new_node(key);
	// # check if key is unique in the treeNode
	if (node->key == key) return NULL;
	// ---- Recursion for inserting element if key is lower than root key insert it in left subtree 
	if (key < node->key) {
		node->left = insert_node(node->left, key);
	}
	 //  if key is greater than root key, insert it in the right subtree
	else {
		node->right = insert_node(node->right, key);
	}

	return node;
}

// # Returns node with minimum key value
TreeNode* min_value_node(TreeNode* node){
	TreeNode * currentNode = node;
	// Repeats till finds node with minimum value
	while (currentNode->left != NULL)
	{
		currentNode = currentNode->left;
	}
  return currentNode;
}

// # Algorithm for deleting node
TreeNode* delete_node(TreeNode* root, int key) {
	// check whether root is not empty
	if (root == NULL) return root;
	// if key is lower than root key go to the left subtree
	if (key < root->key) {
		root->left = delete_node(root->left, key);
	}
	// if greater than go to the right subtree
	else if (key > root->key) {
		root->right = delete_node(root->right, key);
	}
	// if key is equal to root key 

	// only God knows whats happening here
	else {
		
		if (root->left == NULL) {
			TreeNode* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			TreeNode* tmp = root->left;
			free(root);
			return tmp;
		}
		else {
			TreeNode* tmp = min_value_node(root->right);
			root->key = tmp->key;
			root->right = delete_node(root->right, tmp->key);
		}
		
	}
	return root;
}

// # Get size of TreeNode
int size(TreeNode* node)
{
	if (node == NULL)
		return 0;
	else
		return(size(node->left) + 1 + size(node->right)); // +1 for root
}

// # Inorder Algorythm ( Left Root Right  )
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); //starts from left subtree 
		printf("[%d] \t", root->key); // then root (prints its value)
		inorder(root->right); // then right subtree
	}
}
// #  Algorithm returns sorted 2x NodeTrees
TreeNode* sortedTree(TreeNode* firstTree, TreeNode* secondTree) {
	TreeNode* tmp = NULL;
	
	for (int i = 0; i < RANGE_NUMBER+1; i++) {
		// if element exists(not NULL) save element to template
		if (search(firstTree, i)) {
			tmp = insert_node(tmp, i);
		}
		// If element doesn't exist in the first treenode, search it in the second tree
		else if(search(secondTree,i)){
			tmp = insert_node(tmp,i);
		} 
	}
	//return sorted tree
	return tmp;
}
// Drawing separetor
void drawSeparetor(int count) {
	printf("\n");
	for (int i = 0; i < count; i++)
	{
	printf("=");
	} printf("\n\n\n");
}

int main(void) {
	// INIT srand
	srand((unsigned)time(NULL));

	// INIT TreeNodes for even/odd nums
	TreeNode* rootForEvenNs = NULL;
	TreeNode* rootForOddNs = NULL;

	// INIT Program variables
	int nCount = 0;
	int element = 0;
	int i = 0;
	bool isValid = false;

	// Get valid number for generating random numbers (between 1 - 100)
	do {
	printf("How much number should be generated?(MAXSIZE is %d, *included): ",RANGE_NUMBER);
	scanf("%d", &nCount);
	// validator for user input
	if (nCount != 0 && nCount <= RANGE_NUMBER) {
		isValid = true;
	}
	else {
		printf("Invalid Number. Please provide valid number from 1 to %d.",RANGE_NUMBER);
		drawSeparetor(50);
	}
	} while (!isValid);

	// ********** Inserting Unique Numbers to Correspondent TreeNode  *********** 
	while (i < nCount) {

		// range_number is defined in the top
		// generate numbers between 1 to 100
		element = rand() % RANGE_NUMBER + 1; // +1 since range starts from 1
		
		// Check isEven
		if (element % 2 == 0) {
			// if TreeNode isEmpty we don't need to check whether number isExists (to ensure we dont have duplicated keys in node Tree) 
			if (rootForEvenNs == NULL) {
				rootForEvenNs = insert_node(rootForEvenNs, element);
				i++;
			/*
			
			if tree is not empty we should check whether key exists in the given TreeNode * 
			Search function returns null if key does not exist in the given nodeTree
			So we can use it to make our keys unique, because rand() function sometimes returns duplcated random numbers
			for example when search function returns null(didn't found number in the tree) 
			we could just put '!'(NOT) because in C Language NULL is equal to 0 and false;
			
			*/
			} else if (!search(rootForEvenNs, element)) {
				rootForEvenNs = insert_node(rootForEvenNs, element);
				i++;
			}
		} 
		// doing same algorithm for odd numbers
		else {
			if (rootForOddNs == NULL) {
				rootForOddNs = insert_node(rootForOddNs, element);
				i++;
			} else if (!search(rootForOddNs, element)) {
				rootForOddNs = insert_node(rootForOddNs, element);
				i++;
			}
		}

	}
	
	// # OUTPUTS
	drawSeparetor(100);
	printf("TreeNode for odd numbers, its size is %d\n\n ",size(rootForOddNs));
	inorder(rootForOddNs); 
	
	drawSeparetor(100);
	printf("TreeNode for even numbers, its size is %d\n\n ", size(rootForEvenNs));
	inorder(rootForEvenNs);
	
	
	drawSeparetor(100);
	printf("TreeNode for sorted odd and even numbers, its size is %d\n\n ", size(rootForOddNs)+size(rootForEvenNs));
	inorder(sortedTree(rootForOddNs,rootForEvenNs));
	drawSeparetor(100);
	return 0;
}