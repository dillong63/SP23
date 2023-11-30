#ifndef _AVL_NODE_HPP_
#define _AVL_NODE_HPP_
#include <string>
#include <iostream>

class AVLnode
{
private:
	std::string _val;        
	AVLnode* _left;  
	AVLnode* _right; 
	int _height;     
public:
	
	AVLnode(std::string val) :_val(val), _left(nullptr), _right(nullptr), _height(1) {};

	std::string value() const { return _val; }
	std::string& value() { return _val; }

	AVLnode* left() const { return _left; }
	AVLnode* &left() { return _left; }
	AVLnode* right() const { return _right; }
	AVLnode* &right() { return _right; }

	int height() const { return _height; }
	int& height() { return _height; }

	bool isLeaf() const { return !_left && !_right; } 
	std::ostream& print(std::ostream& os) const;
	AVLnode* insert(std::string newVal, AVLnode* SubTree);
	AVLnode* remove(std::string remVal, AVLnode* SubTree);

	
	friend  std::ostream& operator<<(std::ostream& os, const AVLnode& n);
};

#endif
