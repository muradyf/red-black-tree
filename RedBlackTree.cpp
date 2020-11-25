#include <iostream>
#include "RedBlackTree.h"
using namespace std;

void menu(RedBlackTree RBTree);
void askForMenu(RedBlackTree RBTree);
void insert(RedBlackTree RBTree);
void remove(RedBlackTree RBTree);
void search(RedBlackTree RBTree);
void preOrderTraversalNLR(RedBlackTree RBTree);
void inOrderTraversalLNR(RedBlackTree RBTree);
void postOrderTraversalLRN(RedBlackTree RBTree);
void preOrderTraversalNRL(RedBlackTree RBTree);
void inOrderTraversalRNL(RedBlackTree RBTree);
void postOrderTraversalRLN(RedBlackTree RBTree);
void destroyTree(RedBlackTree RBTree);
void deleteGreaterNodes(RedBlackTree RBTree);
void displayParentNode(RedBlackTree RBTree);
void copyTree(RedBlackTree RBTree);
void print(RedBlackTree RBTree);
void readFromFile(RedBlackTree RBTree);

void askForMenu(RedBlackTree RBTree)
{
	char ch = '\0';
	cin.ignore();
	cout << "\nDo you want to go back to the menu? Y/N: ";
	cin.get(ch);
	if (ch == 'y' || ch == 'Y')
		menu(RBTree);
	else
		exit(0);
	cin.ignore();
}

void insert(RedBlackTree RBTree)
{
	unsigned int size = 0;
	int val = 0;

	system("CLS");
	cout << "============= [Inserting a Value] ============\n\n";
	cout << "Enter the number of values: ";
	cin >> size;
	cout << "\nEnter the values:\n";
	for (int i = 0; i < size; i++)
	{
		cin >> val;
		RBTree.insert(val);
	}

	system("CLS");
	cout << "==========================================\n";
	cout << "\tValues have been inserted!\n";
	cout << "==========================================\n\n";
	RBTree.print();

	askForMenu(RBTree);
}

void remove(RedBlackTree RBTree)
{
	int val = 0;

	system("CLS");
	cout << "============= [Deleting a Value] ============\n\n";
	cout << "Enter the value to delete: ";
	cin >> val;
	system("CLS");
	cout << "=========================================\n";
	RBTree.remove(val);
	cout << "=========================================\n";
	RBTree.print();
	askForMenu(RBTree);
}

void search(RedBlackTree RBTree)
{
	int val = 0;

	system("CLS");
	cout << "========== [Searching for a Value] =========\n\n";
	cout << "Enter the value to find: ";
	cin >> val;
	system("CLS");
	cout << "=============================================\n";
	RBTree.search(val);
	cout << "=============================================\n";
	RBTree.print();

	askForMenu(RBTree);
}

void preOrderTraversalNLR(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tPre-Order Traversal (NLR)\n";
	cout << "=================================================\n\n";
	RBTree.preOrderNLR();
	askForMenu(RBTree);
}

void inOrderTraversalLNR(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tIn-Order Traversal (LNR)\n";
	cout << "=================================================\n\n";
	RBTree.inOrderLNR();
	askForMenu(RBTree);
}

void postOrderTraversalLRN(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tPost-Order Traversal (LRN)\n";
	cout << "=================================================\n\n";
	RBTree.postOrderLRN();
	askForMenu(RBTree);
}

void preOrderTraversalNRL(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tPre-Order Traversal (NRL)\n";
	cout << "=================================================\n\n";
	RBTree.preOrderNRL();
	askForMenu(RBTree);
}

void inOrderTraversalRNL(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tIn-Order Traversal (RNL)\n";
	cout << "=================================================\n\n";
	RBTree.inOrderRNL();
	askForMenu(RBTree);
}

void postOrderTraversalRLN(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tPost-Order Traversal (RLN)\n";
	cout << "=================================================\n\n";
	RBTree.postOrderRLN();
	askForMenu(RBTree);
}

void destroyTree(RedBlackTree RBTree)
{
	system("CLS");
	cout << "=================================================\n";
	cout << "\tRed Black Tree Destroyed!\n";
	cout << "=================================================\n\n";
	RBTree.~RedBlackTree();
	askForMenu(RBTree);
}

void deleteGreaterNodes(RedBlackTree RBTree)
{
	int val = 0;

	system("CLS");
	cout << "========== [Delete nodes greater than input] =========\n\n";
	cout << "Enter the value: ";
	cin >> val;
	system("CLS");
	cout << "=======================================================\n";
	RBTree.removeGreaterNodes(val);
	cout << "=======================================================\n";
	RBTree.print();

	askForMenu(RBTree);
}

void displayParentNode(RedBlackTree RBTree)
{
	int val = 0;

	system("CLS");
	cout << "========== [Delete nodes greater than input] =========\n\n";
	cout << "Enter the value to find its parent node: ";
	cin >> val;
	system("CLS");
	cout << "===============================================================\n";
	RBTree.displayParent(val);
	cout << "===============================================================\n";
	RBTree.print();

	askForMenu(RBTree);
}

void copyTree(RedBlackTree RBTree)
{
	RedBlackTree RBTree2;
	system("CLS");
	cout << "===========================================================\n";
	cout << "\tRed Black Tree has been successfully copied!\n";
	cout << "===========================================================\n\n";
	RBTree.copy(RBTree2);
	cout << "Original Red Black Tree:\n\n";
	RBTree.print();
	cout << "Copied Red Black Tree:\n\n";
	RBTree2.print();
	askForMenu(RBTree);
}

void deleteDup(RedBlackTree RBTree)
{
	system("CLS");
	cout << "============= [Deleting Duplicate Values] ============\n\n";
	cout << "=========================================\n";
	RBTree.removeDuplicates();
	cout << "=========================================\n";
	RBTree.print();
	askForMenu(RBTree);
}

void print(RedBlackTree RBTree)
{
	system("CLS");
	cout << "===========================================================\n";
	RBTree.print();
	cout << "===========================================================\n\n";
	askForMenu(RBTree);
}

void readFromFile(RedBlackTree RBTree)
{
	system("CLS");
	RBTree.readFromFile();
	cout << "=================================================================\n";
	cout << "\tFile has been read and values have been inserted!\n";
	cout << "=================================================================\n\n";
	system("PAUSE");
	menu(RBTree);
}

void menu(RedBlackTree RBTree)
{
	system("CLS");
	int ch = 0;

	cout << "   ===================== [Menu] =====================\n";
	cout << "   |\t\t\t\t\t\t    |\n";
	cout << "   |\t1. Insert a Value			    |\n";
	cout << "   |\t2. Delete a Value			    |\n";
	cout << "   |\t3. Search for a Value			    |\n";
	cout << "   |\t4. Perform Pre-Order NLR Traversal	    |\n";
	cout << "   |\t5. Perform In-Order LNR Traversal	    |\n";
	cout << "   |\t6. Perform Post-Order LRN Traversal	    |\n";
	cout << "   |\t7. Perform Pre-Order NRL Traversal	    |\n";
	cout << "   |\t8. Perform In-Order RNL Traversal	    |\n";
	cout << "   |\t9. Perform Post-Order RLN Traversal	    |\n";
	cout << "   |\t10. Destroy the Tree			    |\n";
	cout << "   |\t11. Delete Values Greater Than Input	    |\n";
	cout << "   |\t12. Display the Parent of a Present Node    |\n";
	cout << "   |\t13. Insert Values from File		    |\n";
	cout << "   |\t14. Delete Duplicate Values		    |\n";
	cout << "   |\t15. Copy the Red Black Tree		    |\n";
	cout << "   |\t16. Print Red Black Tree		    |\n";
	cout << "   |\t17. Exit the Program			    |\n";
	cout << "   |\t\t\t\t\t\t    |\n";
	cout << "   ==================================================\n\n\n";

	cout << "\t\tEnter your option: ";
	cin >> ch;

	switch (ch)
	{
	case 1:
		insert(RBTree);
		break;

	case 2:
		remove(RBTree);
		break;

	case 3:
		search(RBTree);
		break;

	case 4:
		preOrderTraversalNLR(RBTree);
		break;

	case 5:
		inOrderTraversalLNR(RBTree);
		break;

	case 6:
		postOrderTraversalLRN(RBTree);
		break;

	case 7:
		preOrderTraversalNRL(RBTree);
		break;

	case 8:
		inOrderTraversalRNL(RBTree);
		break;

	case 9:
		postOrderTraversalRLN(RBTree);
		break;

	case 10:
		destroyTree(RBTree);
		break;

	case 11:
		deleteGreaterNodes(RBTree);
		break;

	case 12:
		displayParentNode(RBTree);
		break;

	case 13:
		readFromFile(RBTree);
		break;

	case 14:
		readFromFile(RBTree);
		break;

	case 15:
		copyTree(RBTree);
		break;

	case 16:
		print(RBTree);
		break;

	default:
		exit(0);
		break;
	}
}

int main()
{
	RedBlackTree RBTree;
	menu(RBTree);
	return 0;
}