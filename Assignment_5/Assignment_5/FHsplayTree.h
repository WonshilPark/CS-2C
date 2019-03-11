// File FHsplayTree.h
// Template definitions for FHsearchTrees, which are general trees
#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "FHsearch_tree.h"

// ---------------------- FHsplayTree Prototype --------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   
   // this is not a true override, but an overload, because we are "losing"
   // the const modifier on the function.  contains() will modify the tree due
   // to a splay() call deeper down, thus we cannot declare it to be const.
   bool contains(const Comparable &x);
   
   // like contains() this is not a true override, but an overload,
   // as we are "losing" the const function modifier.
   const Comparable &find(const Comparable &x);
   
   // returns the mRoot data, or an automatic default object if there is no master root.
   // This is useful for debugging and proving that the class really is splaying.
   const Comparable &showRoot();
   
protected:
   // this method is analyzed in depth in the modules and a detailed algorithm is given there.
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   
   // this is (almost) identical with the version found in FHavlTree.h.
   // Make the trivial adjustments and you've got it.
   void rotateWithLeftChild(FHs_treeNode<Comparable> * & k2);
   
   // this is (almost) identical with the version found in FHavlTree.h.
   // Make the trivial adjustments and you've got it.
   void rotateWithRightChild(FHs_treeNode<Comparable> * & k2);
};

// FHsplayTree public method definitions -----------------------------
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x)
{
   if (contains(x))
      return false;
   
   FHs_treeNode<Comparable> * newNode = new FHs_treeNode<Comparable>(x);
   
   if (!this->mRoot) {}
   else if (x < this->mRoot->data)
   {
      newNode->lftChild = this->mRoot->lftChild;
      this->mRoot->lftChild = NULL;
      newNode->rtChild = this->mRoot;
   }
   else if (x > this->mRoot->data)
   {
      newNode->rtChild = this->mRoot->rtChild;
      this->mRoot->rtChild = NULL;
      newNode->lftChild = this->mRoot;
   }
   
   this->mRoot = newNode;
   this->mSize++;
   
   return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
   // if the tree is empty, return false.
   // otherwise, splay for x in the master tree (the full tree)
   if (!contain(x))
      return false;
   else
      splay(this->mRoot, x);
   
   // if x != root return false.
   if (x != this->mRoot)
      return false;
   
   FHs_treeNode<Comparable> * newRoot;
   
   // if the (new) master root's left child is NULL, set newRoot to the master root's right child.
   if (this->mRoot->lftChild == NULL)
      newRoot = this->mRoot->rtChild;
   else
   {
      // set newRoot to the master root's left child.
      newRoot = this->mRoot->lftChild;
      // splay for x in the newRoot subtree (bringing the max to the top of newRoot).
      splay(newRoot, x);
      // set newRoot's right child to the master root's right child.
      newRoot->rtChild = this->mRoot->rtChild;
   }
   
   //delete the master root node (which holds x)
   delete this->mRoot;
   // set the master root to newRoot.
   this->mRoot = newRoot;
   
   return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x)
{
   try
   {
      find(x);
   }
   catch (typename FHsearch_tree<Comparable>::NotFoundException&)
   {
      return false;
   }
   catch (typename FHsearch_tree<Comparable>::EmptyTreeException&)
   {
      return false;
   }
   
   return true;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(const Comparable &x)
{
   if (!this->mRoot)
      throw typename FHsearch_tree<Comparable>::NotFoundException();
   
   splay(this->mRoot, x);
   
   if (x < this->mRoot->data || x > this->mRoot->data)
      throw typename FHsearch_tree<Comparable>::NotFoundException();
   
   return x;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::showRoot()
{
   if (this->mRoot)
      return this->mRoot->data;
   static Comparable defaultObj = Comparable();
   return defaultObj;
}

// FHsplayTree protected method definitions -----------------------------
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root, const Comparable & x)
{
   // initialize the rightTree, leftTree, rightTreeMin, and leftTreeMax to NULL
   FHs_treeNode<Comparable> * rightTree = NULL;
   FHs_treeNode<Comparable> * leftTree = NULL;
   FHs_treeNode<Comparable> * rightTreeMin = NULL;
   FHs_treeNode<Comparable> * leftTreeMax = NULL;
   
   // loop while root != NULL (root should not become NULL, but this protects against NULL parameter)
   while (root != NULL)
   {
      // if x < root, check for root's left child NULL.  If so, x not in tree, break loop.
      if (x < root->data)
      {
         if (root->lftChild == NULL)
            break;
         // if x < root's left child we have zig zig (left) so do a single rotate (left) at root
         // check for (new) root's left child NULL.  If so, x not in tree, break loop.
         if (x < root->lftChild->data)
         {
            rotateWithLeftChild(root);
            if (root->lftChild == NULL)
               break;
         }
         
         // add root to rightTree at its minimum node - update the rightTreeMin to
         // point to this node update the new working root:
         // set root to root's left child
         if (rightTree == NULL)
         {
            rightTree = root;
            rightTreeMin = rightTree;
         }
         else
         {
            rightTreeMin->lftChild = root;
            rightTreeMin = rightTreeMin->lftChild;
         }
         root = root->lftChild;
         rightTreeMin->lftChild = NULL;
      }
      
      // otherwise, if x > root
      // check for root's right child NULL.  If so, x not in tree, break loop.
      // if x > root's right child we have zig zig (right) so do a single rotate (right) at root
      // check for (new) root's right child null.  If so, x not in tree, break loop.
      // add root to leftTree at its maximum node - update the leftTreeMax to point to this node
      // update the new working root:  set root to root's right child
      // otherwise we have found x at root.  break.
      else if (x > root->data)
      {
         if (root->rtChild == NULL)
            break;
         if (x > root->rtChild->data)
         {
            rotateWithRightChild(root);
            if (root->rtChild == NULL)
               break;
         }
         
         if (leftTree == NULL)
         {
            leftTree = root;
            leftTreeMax = leftTree;
         }
         else
         {
            leftTreeMax->rtChild = root;
            leftTreeMax = leftTreeMax->rtChild;
         }
         root = root->rtChild;
         leftTreeMax->rtChild = NULL;
      }
      else
         break;
   }
   
   //reassemble
   // if the left tree is not NULL, hang root's left child onto its maximum and
   // set root's left child = the left tree.
   if (leftTree)
   {
      if (root->lftChild)
         leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   
   // if the right tree is not NULL, hang root's right child onto its minimum
   // and set root's right child = the right tree.
   if (rightTree)
   {
      if (root->rtChild)
         rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> * k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> * k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}

#endif
