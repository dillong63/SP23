#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#include <iostream>
#include <string>

class TreeNode
{
private:
	std::string _element;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode* _parent;
public:
	TreeNode(const std::string& data) :
		_element(data), _left(NULL), _right(NULL), _parent(NULL) {}

	// accessors 
	const std::string& value() const { return _element; }
	const TreeNode* left() const { return _left; }
	const TreeNode* right() const { return _right; }
	const TreeNode* parent() const { return _parent; }

	// modifiers
	std::string& value() { return _element; }
	TreeNode*& left() { return _left; }
	TreeNode*& right() { return _right; }
	TreeNode*& parent() { return _parent; }

	bool isLeaf() const;
	unsigned int depth() const;
};
#endif
