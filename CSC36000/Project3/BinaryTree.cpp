#include "BinaryTree.hpp"

#include <iostream>

using namespace std;

TreeNode* findHelper(const string&, const TreeNode*);
TreeNode* insertHelper(TreeNode* SubTree, const TreeNode* newNode);
void printHelper(const TreeNode* subtree, ostream& os);
void treePrint(const TreeNode* subtree, ostream& os);
int hhelp(TreeNode* r)
{
	if (r == NULL)
		return 0;
	else {
		int lheight = hhelp(r->left());
		int rheight = hhelp(r->right());

		return max(lheight, rheight) + 1;
	}
}

int
BinaryTree::height()
{
	return hhelp(_root);
}
TreeNode*
BinaryTree::find(const string& findMe) const
{
	return findHelper(findMe, _root);
}

TreeNode* findHelper(const string& val, const TreeNode* nodePtr)
{
	if (!nodePtr) 
		return NULL;

	if (nodePtr->value() == val)
		return (TreeNode*)nodePtr;

	if (val > nodePtr->value())
		return findHelper(val, nodePtr->right());
	else 
		return findHelper(val, nodePtr->left());
}

void
BinaryTree::insert(const std::string& valueToAdd)
{
	if (find(valueToAdd))
	{
		return;
	}

	TreeNode* newTreeNode = new TreeNode(valueToAdd);
	_root = insertHelper(_root, newTreeNode);
}

TreeNode* insertHelper(TreeNode* SubTree, const TreeNode* newNode)
{

	if (!newNode) 
	{
		return (TreeNode*)SubTree;
	}

	// empty subtree? the new tree will have only the node we are inserting
	if (!SubTree) //if (SubTree == NULL)
	{
		return (TreeNode*)newNode;
	}


	// note: this helper function assumes the node is not already present!

	// should we be inserting into left side?
	if (newNode->value() < SubTree->value())
	{
		// insert into left subtree, and update our left subtree pointer accordingly
		SubTree->left() = insertHelper(SubTree->left(), newNode);

		// update left subtree's "parent" pointer
		SubTree->left()->parent() = SubTree;
	}
	else // >, so must need to insert into right side
	{
		// insert into right subtree, and update our right subtree pointer accordingly
		SubTree->right() = insertHelper(SubTree->right(), newNode);

		// update right subtree's "parent" pointer
		SubTree->right()->parent() = SubTree;
	}

	return SubTree;
}

void
BinaryTree::remove(const std::string& valueToDelete)
{
	TreeNode* toDel = find(valueToDelete);

	if (!toDel)
		return;

	// test for which case we are in ....

	if (toDel->isLeaf())
	{
		// think about this ... there is only one node in tree!
		if (toDel == _root)
		{
			_root = NULL;
			return;
		}

		TreeNode* parent = toDel->parent();
		if (parent->left() == toDel)
			parent->left() = NULL;
		else // must be right child
			parent->right() = NULL;

		//toDel->parent() = toDel->left() = toDel->right() = NULL;
	}
	// check for one child case
	else if ((toDel->left() && !toDel->right()) // have left but no right child
		||
		(!toDel->left() && toDel->right()) // have no left but yes on right child
		)
	{
		if (toDel == _root)
		{
			if (toDel->left()) // is the only child on the left?
				_root = toDel->left();
			else // the only child is on the right
				_root = toDel->right();

			_root->parent() = NULL;
			return;
		}

		TreeNode* subtreeToMove;
		if (toDel->left()) // left subtree is the 1 child we have
			subtreeToMove = toDel->left();
		else // right subtree is the 1 child we have		
			subtreeToMove = toDel->right();

		TreeNode* parent = toDel->parent();
		if (parent->left() == toDel)
			parent->left() = subtreeToMove;
		else
			parent->right() = subtreeToMove;

		subtreeToMove->parent() = parent;
	}
	else // i have 2 children
	{
		TreeNode* largestInLeft;
		largestInLeft = toDel->left();
		while (largestInLeft->right() != NULL)
		{
			largestInLeft = largestInLeft->right();
		}

		string dataToKeep = largestInLeft->value();

		remove(dataToKeep);
		toDel->value() = dataToKeep;


	}

}

ostream& operator<<(ostream& stream, const BinaryTree& bt)
{
	//printHelper( bt._root , stream );
	treePrint(bt._root, stream);
	return stream;
}

void printHelper(const TreeNode* subtree, ostream& os)
{
	if (!subtree)
		return;

	printHelper(subtree->left(), os);
	os << subtree->value() << endl;
	printHelper(subtree->right(), os);
}

void treePrint(const TreeNode* subtree, ostream& os)
{
	if (!subtree)
		return;

	treePrint(subtree->right(), os);
	for (unsigned int ntabs = 0; ntabs < subtree->depth(); ntabs++)
		os << "         ";
	os << subtree->value() << endl;
	treePrint(subtree->left(), os);
}