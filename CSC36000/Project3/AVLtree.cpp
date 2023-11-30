#include <iostream>
#include "AVLtree.hpp"

using namespace std;

int
AVLtree::height()
{
	return _root->height(); //find the height
}
void
AVLtree::insert(string newVal) //insert a new va'l
{
    if (!_root)
        _root = new AVLnode(newVal);
    _root = _root->insert(newVal, _root); 
}


void
AVLtree::remove(string rem) //remove a value
{
    if (!_root)
        return;
    else
        _root = _root->remove(rem, _root);
}

AVLnode* findHelper(const string& val, const AVLnode* nodePtr) //helper to find val in tree
{
	if (!nodePtr)
		return NULL;

	if (nodePtr->value() == val)
		return (AVLnode*)nodePtr;

	if (val > nodePtr->value())
		return findHelper(val, nodePtr->right());
	else
		return findHelper(val, nodePtr->left());
}
AVLnode*
AVLtree::find(const string& findMe) const //function to find a value from my Binary tree class from last year
{
	return findHelper(findMe, _root);
}