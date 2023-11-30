#include "TreeNode.hpp"	

bool
TreeNode::isLeaf() const //checks to see if node is a leaf by having no children
{
	return !_right && !_left;

}


unsigned int
TreeNode::depth() const
{
	unsigned int cnt = 0;

	TreeNode* curr = (TreeNode*)this;
	while (curr->_parent != NULL)
	{
		cnt++;
		curr = curr->_parent;
	}

	return cnt;
}