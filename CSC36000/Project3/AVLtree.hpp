#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include "AVLnode.hpp"
#include<iostream>
#include<string>

class AVLtree
{
private:
	AVLnode* _root;    // for a tree, all we need to know is its root
public:
	AVLtree() :_root(nullptr) {}
	void insert(std::string nVal);
	void remove(std::string val);
	AVLnode* find(const std::string& findMe) const;
	int height();


	std::ostream& display(std::ostream& os) const;
};
#endif