#include "AVLnode.hpp"
#include <string>
#include <iostream>

using namespace std;

AVLnode* leftChildCase(AVLnode* k2);
AVLnode* rightChildCase(AVLnode* k2);

int getHeight(AVLnode* node)
{
    if (!node) //does the node exist
    {
        return 0; 
    }
    else
    {
        return node->height(); //return height as stored
    }
}


AVLnode* leftChildCase(AVLnode* k2)
{
    AVLnode* k1 = k2->left();
    k2->left() = k1->right(); 
    k1->right() = k2; 
    k2->height() = 1 + max(getHeight(k2->left()), getHeight(k2->right())); //look at height of left and right side and make the max the height
    k1->height() = 1 + max(getHeight(k1->left()), getHeight(k2));

    return k1;
}


AVLnode* doubleLeft(AVLnode* k3)
{
    AVLnode* k1 = k3->left();
    k3->left() = rightChildCase(k1);//rotate right first
    return leftChildCase(k3);//rotate left
}
 
AVLnode* rightChildCase(AVLnode* k2)
{
    //below pulls up right child
    AVLnode* k1 = k2->right();
    k2->right() = k1->left(); 
    k1->left() = k2;
    k2->height() = 1 + max(getHeight(k2->left()), getHeight(k2->right()));//look at height of left and right side and make the max the height
    k1->height() = 1 + max(getHeight(k1->right()), getHeight(k2));

    return k1;
}

AVLnode* doubleWithRightChild(AVLnode* k3)
{
    AVLnode* k1 = k3->right();
    k3->right() = leftChildCase(k1); //rotate left first
    return rightChildCase(k3); //rotate right
}


AVLnode*
AVLnode::insert(string newVal, AVLnode* SubTree)
{
    if (SubTree == nullptr) //basecase
    {
        AVLnode* newRoot = new AVLnode(newVal);
        return newRoot;
    }

    else if (newVal < SubTree->_val) //left subtree
    { 
        SubTree->_left = insert(newVal, SubTree->_left); 
       //look if need rotations
        int leftHeight = getHeight(SubTree->_left);
        int rightHeight = getHeight(SubTree->_right);

        if (leftHeight - rightHeight == 2)//check for imbalances
        {
            if (newVal < SubTree->_left->_val)
            {
                SubTree = leftChildCase(SubTree);
            }

            else
            {
                SubTree = doubleLeft(SubTree);
            }
        }
    }
    else if (newVal > SubTree->_val) //right insert
    {
        SubTree->_right = insert(newVal, SubTree->_right);
        int leftHeight = getHeight(SubTree->_left); //check balances
        int rightHeight = getHeight(SubTree->_right);
        if (rightHeight - leftHeight == 2)
        {
            if (newVal > SubTree->_right->_val)
            {
                SubTree = rightChildCase(SubTree);
            }
            else
            {
                SubTree = doubleWithRightChild(SubTree);
            }
        }
    }

    SubTree->height() = 1 + max(getHeight(SubTree->left()), getHeight(SubTree->right())); //update height of node with max side height
    return SubTree;
}

AVLnode*
AVLnode::remove(string remVal, AVLnode* fromSubTree)
{

    if (!fromSubTree) //basecase
        return nullptr;

    if (remVal < fromSubTree->_val) //is it to the left
    {
        fromSubTree->left() = remove(remVal, fromSubTree->left());
    }
    else if (remVal > fromSubTree->_val) //is it to the right
    {
        fromSubTree->right() = remove(remVal, fromSubTree->right());
    }
    else 
    {
        if (fromSubTree->isLeaf()) 
        {
            fromSubTree = nullptr;
        }
        else if (fromSubTree->left() && fromSubTree->right()) 
        {
            AVLnode* toDel = fromSubTree->left(); //find the largest node to the left
            while (toDel->right() != nullptr)
            {
                toDel = toDel->right();
            }
            string valueToMove = toDel->value(); //store largest val to left
            fromSubTree->left() = remove(valueToMove, fromSubTree->left());
            fromSubTree->value() = valueToMove; 
        }
        else //not 2 children
        {
            if (fromSubTree->left()) //has a left child
                fromSubTree = fromSubTree->left();
            else 
                fromSubTree = fromSubTree->right();
        }

    }
    if (!fromSubTree) //if we have deleted the tree return null
        return nullptr;

    if (getHeight(fromSubTree->left()) - getHeight(fromSubTree->right()) == 2) //violation
    {
        int subBalance = getHeight(fromSubTree->left()->left()) -
            getHeight(fromSubTree->left()->right());
        //determine side of imbalance
        if (getHeight(fromSubTree->left()->left()) - getHeight(fromSubTree->left()->right()) >= 0)
        {
            fromSubTree = leftChildCase(fromSubTree);
        }
        else
        {
            fromSubTree = doubleLeft(fromSubTree);
        }
    }

    if (getHeight(fromSubTree->left()) - getHeight(fromSubTree->right()) == -2)
    {
        int subBalance = getHeight(fromSubTree->right()->left()) -getHeight(fromSubTree->right()->right());
        //determine imbalance type
        if (getHeight(fromSubTree->right()->left()) - getHeight(fromSubTree->right()->right()) < 0)
        {
            fromSubTree = rightChildCase(fromSubTree);
        }
        else 
        {
            fromSubTree = doubleWithRightChild(fromSubTree);
        }
    }

    fromSubTree->_height = 1 + max(getHeight(fromSubTree->left()),getHeight(fromSubTree->right())); //find the new height after removal

    return fromSubTree;
}
