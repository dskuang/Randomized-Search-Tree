#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ 
  virtual ~BST() {
    deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ // TODO
  virtual bool insert(const Data& item) {
    BSTNode<Data> * newNode = new BSTNode<Data>(item);
    BSTNode<Data> * currentNode = root;
    if(NULL == root) {
      root = newNode;
      isize++;
      return true;
    }

    // root is not NULL
    while(true) {
      if(item < currentNode->data) {
        if(NULL == currentNode->left) {
          currentNode->left = newNode;
          newNode->parent = currentNode;
          isize++;
          return true;
        }
        else {
          currentNode = currentNode->left;
        }
      }
      else if(currentNode->data < item) { // item is bigger than current node
        if(NULL == currentNode->right) {
          currentNode->right = newNode;
          newNode->parent = currentNode;
          isize++;
          return true;
        }
        else {
          currentNode = currentNode->right;
        }
      }
      else {
        // item == currentNode->data
        delete newNode;
        return false;
      }
    }
    std::cout << "should not reach here" << std::endl;
    return false;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data> * currentNode = root;
    while(NULL != currentNode) {
      if(item < currentNode->data) { 
          currentNode = currentNode->left;
      }
      else if(currentNode->data < item){
        currentNode = currentNode->right;
      }
      else {
        // item == currentNode->data
        return iterator(currentNode);
      }
    }
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const {
    return isize;
  }

  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const {
    if(NULL == root) {
      return true;
    }
    else {
      return false;
    }
  }

  /** Return an iterator pointing to the first item in the BST.
   */ 
  iterator begin() const {
    iterator itr(first(root));
    return itr;
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */
  void inorder(BSTNode<Data>* n) const {
    if(n==0) return;
    inorder(n->left);
    std::cout << *n << std::endl;
    inorder(n->right);
  }

  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  // do a postorder traversal, deleting nodes
  static void deleteAll(BSTNode<Data>* n) {
    if (0 == n) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }
 };

#endif //BST_HPP
