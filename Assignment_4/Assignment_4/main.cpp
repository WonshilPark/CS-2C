//
//  main.cpp
//  Assignment_4
//
//  Created by Won Shil Park on 2/2/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

// CS 2C  Simple Search Tree Client - Lazy Deletion, int data
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
#include "FHsearch_tree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   /*
    --------------- main from example ---------------
    int k;
    FHlazySearchTree<int> searchTree;
    PrintObject<int> intPrinter;

    searchTree.traverse(intPrinter);

    cout << "initial size: " << searchTree.size() << endl;
    searchTree.insert(50);
    searchTree.insert(20);
    searchTree.insert(30);
    searchTree.insert(70);
    searchTree.insert(10);
    searchTree.insert(60);

    cout << "After populating -- traversal and sizes: \n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    // test assignment operator
    FHlazySearchTree<int> searchTree2 = searchTree;

    cout << "\n\nAttempting 1 removal: \n";
    if (searchTree.remove(20))
    cout << "removed " << 20 << endl;
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting Garbage - should clean 1 item. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting Garbage again - no change expected. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    // test soft insertion and deletion:

    cout << "Adding 'hard' 22 - should see new sizes. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAfter soft removal. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Repeating soft removal. Should see no change. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Soft insertion. Hard size should not change. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\n\nAttempting 100 removals: \n";
    for (k = 100; k > 0; k--)
    {
    if (searchTree.remove(k))
    cout << "removed " << k << endl;
    }
    searchTree.collectGarbage();

    cout << "\nsearchTree now:\n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;

    searchTree2.insert(500);
    searchTree2.insert(200);
    searchTree2.insert(300);
    searchTree2.insert(700);
    searchTree2.insert(100);
    searchTree2.insert(600);
    cout << "\nsearchTree2:\n";
    searchTree2.traverse(intPrinter);
    cout << "\ntree 2 size: " << searchTree2.size()
    << "  Hard size: " << searchTree2.sizeHard() << endl;

    return 0;
    */

   // --------------- my main ---------------
   int k;
   FHlazySearchTree<int> secondTree;
   PrintObject<int> intPrinter;

   cout << "--------------- a hard-empty tree --" << endl;
   cout << "Current tree:\n";
   try
   {
      cout << "\nCurrent max value: " << secondTree.findMax();
   }
   catch (FHlazySearchTree<int>::EmptyTreeException)
   {
      cout << "Caught EmptyTreeException() as expected.";
   }

   try
   {
      {
         cout << "\nCurrent min value: " << secondTree.findMin();
      }
   }
   catch (FHlazySearchTree<int>::EmptyTreeException)
   {
      cout << "Caught EmptyTreeException() as expected." << endl;
   }
   cout << endl;
   cout << endl;

   cout << "--------------- a tree that has non-deleted stuff in it --" << endl;
   for (k = 0; k < 5; k++)
   {
      secondTree.insert(k);
   }
   cout << "Current tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.insert(5);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.insert(6);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.collectGarbage();
   cout << endl;
   cout << endl;

   cout << "---------------  Completely empty but has all soft-deleted nodes test --" << endl;
   for (k = 0; k < 5; k++)
   {
      secondTree.insert(k);
   }
   cout << "Current tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(1);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(2);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(3);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(4);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(5);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(6);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   cout << "\nCurrent max value: " << secondTree.findMax();
   cout << "\nCurrent min value: " << secondTree.findMin() << endl;
   secondTree.remove(0);
   cout << "\nCurrent tree: ";
   secondTree.traverse(intPrinter);
   try {
      cout << "\nCurrent max value: " << secondTree.findMax();
   } catch (FHlazySearchTree<int>::EmptyTreeException) {
      cout << "Caught EmptyTreeException() as expected.";
   }

   try {
      {
         cout << "\nCurrent min value: " << secondTree.findMin();
      }
   } catch (FHlazySearchTree<int>::EmptyTreeException) {
      cout << "Caught EmptyTreeException() as expected." << endl;
   }
   secondTree.collectGarbage();
   cout << endl;

   return 0;
}

/* ---------------------- Run for example main() --------------------------
 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6


 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6
 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5
 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6

 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 5  Hard size: 6


 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10

 searchTree now:

 tree 1 size: -1  Hard size: 0

 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12
 Program ended with exit code: 0

 ---------------------- Run for my main() --------------------------
 --------------- a hard-empty tree --
 Current tree:

 Current max value: Caught EmptyTreeException() as expected.
 Current min value: Caught EmptyTreeException() as expected.


 --------------- a tree that has non-deleted stuff in it --
 Current tree: 0 1 2 3 4
 Current max value: 4
 Current min value: 0

 Current tree: 0 1 2 3 4 5
 Current max value: 5
 Current min value: 0

 Current tree: 0 1 2 3 4 5 6
 Current max value: 6
 Current min value: 0


 ---------------  Completely empty but has all soft-deleted nodes test --
 Current tree: 0 1 2 3 4 5 6
 Current max value: 6
 Current min value: 0

 Current tree: 0 2 3 4 5 6
 Current max value: 6
 Current min value: 0

 Current tree: 0 3 4 5 6
 Current max value: 6
 Current min value: 0

 Current tree: 0 4 5 6
 Current max value: 6
 Current min value: 0

 Current tree: 0 5 6
 Current max value: 6
 Current min value: 0

 Current tree: 0 6
 Current max value: 6
 Current min value: 0

 Current tree: 0
 Current max value: 0
 Current min value: 0

 Current tree:
 Current max value: Caught EmptyTreeException() as expected.
 Current min value: Caught EmptyTreeException() as expected.

 Program ended with exit code: 0
 */
