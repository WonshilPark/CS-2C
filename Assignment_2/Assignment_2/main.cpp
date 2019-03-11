//
//  main.cpp
//  Assignment_2
//
//  Created by Won Shil Park on 1/20/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

#include <iostream>

using namespace std;

#include "FHvector.h"
#include <vector>
#include "FHlist.h"
#include <list>
#include <iomanip>

#define MAT_SIZE 100000

template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;
   // we need a default constructor for lists
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }

   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=( const Object &x ) { return (data = x);}
};

template <class Object>
class SparseMat
{
public:
   SparseMat(int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);

protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;
};

// --------------- main ---------------
int main()
{
   typedef SparseMat<float> SpMat;
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

   // test mutators
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4,4, -9);
   mat.set(4,4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE-1, MAT_SIZE-1, 99);

   // required testers
   mat.set(300, MAT_SIZE-1,50);
   mat.set(500, 500,300);
   mat.set(MAT_SIZE-1, 700,100);

   // test accessors and exceptions
   try
   {
      cout << mat.get(7, 8) << endl;
      cout << mat.get(2, 5) << endl;
      cout << mat.get(9, 9) << endl;
      cout << mat.get(-4, 7) << endl;  // should throw an exception
   }
   catch (...)
   {
      cout << "oops" << endl;
   }

   // show top left 15x15
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   mat.showSubSquare(MAT_SIZE - 15, 15);

   // show mat.set(300, MAT_SIZE-1,50);
   cout << mat.get(300, MAT_SIZE-1) << endl;

   // show mat.set(500, 500,300);
   cout << mat.get(500, 500) << endl;

   // show mat.set(MAT_SIZE-1, 700,100);
   cout << mat.get(MAT_SIZE-1, 700) << endl;
}

template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal): rowSize(r), colSize(c), defaultVal(defaultVal)
{
   for (int i = 0; i < rowSize; i++)
      rows.push_back(MatRow());
}

template <class Object>
const Object & SparseMat<Object>::get(int r, int c) const
{
   if (rows[r].empty() || r > rowSize)
   {
      return defaultVal;
   }
   for(typename MatRow::const_iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
   {
      if ((*iter).getCol() == c)
      {
         return (*iter).data;
      }
   }
   return defaultVal;
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   // A mutator that places x in row r and column c. It returns false without an exception if bounds are violated.
   if ((r < 0 || r >= rowSize) || (c < 0 || c >= colSize))
      return false;

   if (x == defaultVal)
   {
      for (typename MatRow::iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
      {
         if ((*iter).getCol() == c)
            rows[r].erase(iter);
         else
            return true;
      }
   }
   else
      for (typename MatRow::iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
      {
         if ((*iter).getCol() == c)
            (*iter).data = x;
         else
         {
            MatNode<Object> temp = MatNode<Object>(c, x);
            rows[r].push_back(temp);
         }
      }
   MatNode<Object> temp = MatNode<Object>(c, x);
   rows[r].push_back(temp);
   return true;
}

template <class Object>
void SparseMat<Object>::clear()
{
   for (int i = 0; i < rowSize; i++)
   {
      rows[i].clear();
   }
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
   int temp = start + size;
   for (int i = start; i < temp; i++)
   {
      for (int j = start; j < temp; j++)
         cout << setw(3) << get(i, j);
      cout << endl;
   }
   cout << endl;
   cout << endl;
}

/*
 0
 35
 21
 oops
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0 35  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 21  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0


 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0 99


 50
 300
 100
 Program ended with exit code: 0
 */
