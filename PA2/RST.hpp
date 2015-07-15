/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/5/15

                                                       
                            Assignment Two

File Name:      RST.hpp
Description:    This program implements a random search tree data structure. 
		Each RST contains one Tree instance and zero or more BSTNode
                instances. It contains the insertion and rotation
		methods.
****************************************************************************/
//Using instructor's PA1 files but using my BST insert method
//I decided to use professor's PA1 files because they appear to run
//better than mine in the succesor method. I did receive a 24/25 on the 
//first assignment so the difference would only be in efficiency

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

/***************************************************************************
% Routine Name : virtual bool insert(const Data& item)
% File :         RST.hpp
% 
% Description :  This function will search through the tree and place an 
%                element in the correct location. If the element can be 
%                inserted the element is inserted and true is returned. 
%                Duplicate insertions will cause the pair to return false
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% item          The element to insert.
% <return>      True or false            
***************************************************************************/
  virtual bool insert(const Data& item) {
        
       BSTNode<Data> * temp_node = BST<Data>::root; 
	 while(true){
                //checks if root is null
		if(BST<Data>::root == nullptr){
			//cout<<"make a root"<<endl;
			BST<Data>::root = new BSTNode<Data>(item);
			BST<Data>::isize++;
			BST<Data>::root->priority = (int)rand();			
			return true;
		}
                //checks for duplicates
		if(item == temp_node->data){
			return false;
		}
                //checks if item is smaller than data
		if(item < temp_node->data){
			if(temp_node->left){
				temp_node = temp_node->left;
				continue;
			}
			else{
                                //creates a node left of parent node
				temp_node->left = new BSTNode<Data>(item);
				temp_node->left->parent = temp_node;
				BST<Data>::isize++;
			        adjust(temp_node->left);
				
				return true;
			}
		}
		else{
                        //checks for right node and goes right
			if(temp_node->right){
				temp_node = temp_node->right;
				continue;
			}
			else{
				
				temp_node->right = new BSTNode<Data>(item);
				temp_node->right->parent = temp_node;
				BST<Data>::isize++;
				adjust(temp_node->right);                     
				return true;
			}
		}
	}	
        return true;
  }


private:


/***************************************************************************
% Routine Name : adjust(BSTNode<Data> * newNode)
% File :         RST.hpp
% 
% Description :  This function checks the priority of the node and parent 
		 nodes and calls the correct rotation method when
		 necessary.

% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% newNode       a pointer to a BSTNode<Data> type
% <return>      none           
***************************************************************************/
  void adjust(BSTNode<Data> * newNode){
    
      newNode->priority = rand();
      while (newNode->parent != nullptr && newNode->parent->priority <
	     newNode->priority) {
            
         
            if (newNode->data < newNode->parent->data) {	
                rotateRight(newNode->parent, newNode);
            }

            else {
                rotateLeft(newNode->parent, newNode);
            }
      }	
  }

/***************************************************************************
% Routine Name : rotateRight( BSTNode<Data>* par, BSTNode<Data>* child )
% File :         RST.hpp
% 
% Description :  This function performs a 'right rotation' that changes the 
                 structure of the tree without interfering with the size, 
                 data content, and left->right order of nodes in the RST.
                 This rotation is done by changing the 'left', 'right', 
                 and/or 'parent' pointers of a subset of nodes without 
                 changing their 'priority' values.
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% par           a parent node in the RST with a left child
% child         the left child node of par
% <return>      none           
***************************************************************************/
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {

	  //child = par -> left;
	  par -> left = child -> right;
	  if(child-> right)
		  child-> right-> parent = par;
	  child->parent = par -> parent;

	  if(!par -> parent){
		  BST<Data>::root = child;
		  child -> parent = nullptr;
	  }
	  else if(par -> parent -> left == par)
		  par -> parent ->left = child;
	  else
		  par -> parent -> right = child;
	  child -> right = par;
	  par -> parent = child;

  }

/***************************************************************************
% Routine Name : rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
% File :         RST.hpp
% 
% Description :  This function performs a 'left rotation' that changes the 
                 structure of the tree without interfering with the size, 
                 data content, and left->right order of nodes in the RST.
                 This rotation is done by changing the 'left', 'right', 
                 and/or 'parent' pointers of a subset of nodes without 
                 changing their 'priority' values.
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% par           a parent node in the RST with a left child
% child         the left child node of par
% <return>      none           
***************************************************************************/
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  { 
     

	  par -> right = child -> left;
	  if(child-> left)
		  child->left -> parent = par;

	  child -> parent = par -> parent;

	  if(!par -> parent){
		  BST<Data>::root = child;
		  child -> parent = nullptr;
	  }
	  else if(par -> parent -> left == par)
		  par -> parent ->left = child;
	  else
		  par -> parent -> right = child;
	  child -> left = par;
	  par -> parent = child;
      
  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   * 
   */
  bool BSTinsert(const Data& item) {
    
    return BST<Data>::insert(item);
    
  }
  
  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {
    // cout<<"hi"<<endl;
     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }
     
     if (current == 0 or current->data != item) {
       return 1;
     }
     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);
     
       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }
       
     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);
       
       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
