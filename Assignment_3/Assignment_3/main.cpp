//
//  main.cpp
//  Assignment_3
//
//  Created by Won Shil Park on 1/26/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

#include <iostream>

using namespace std;

#include <time.h>
#include <string>
#include <random>
#include <iomanip>

const int MAT_SIZE = 200;
typedef float* DynMat[MAT_SIZE];

DynMat mDyn, nDyn, ansDyn;

// Create a global scope method that takes two input matrices, and the third a return (reference) product matrix:
void matMultDyn( const DynMat & matA,  const DynMat & matB,
                DynMat & matC, int size);

// display method for these dynamic matrices like you did for sparse matrices last week:  one that shows a square sub-matrix of size = size anchored at position (start, start):
void matShowDyn( const DynMat & matA, int start, int size);

// timing algorithms
clock_t startClock() { return clock(); }

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   double randFrac;
   int randRow, randCol, smallPercent;

   srand(time(0));
   random_device rd;
   uniform_real_distribution<> dist(0, 1);

   // format for cout
   cout << fixed;
   cout << setprecision(2);

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float[MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0.0;
         matDynAns[r][c] = 0.0;
      }
   }

   // generate small% (bet .1 and 10%) non-default values (bet 0 and 1)
   smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
   for (r = 0; r < smallPercent; r++)
   {
      matDyn[rand() % MAT_SIZE][rand() % MAT_SIZE] = dist(rd);
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   cout << endl << endl;
   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << endl << endl;
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++)
   {
      delete[] matDyn[r];
      delete[] matDynAns[r];
   }

   cout << endl << endl;
}

void matShowDyn( const DynMat & matA, int start, int size)
{
   for (int i = start; i < start + size; i++) {
      for (int j = start; j < start + size; j++)
      {
         cout << setw(5) << matA[i][j];
      }
      cout << endl;
   }
}

void matMultDyn( const DynMat & matA,  const DynMat & matB,
                DynMat & matC, int size)
{
   for (int r = 0; r < MAT_SIZE; r++)
   {
      for (int c = 0; c < MAT_SIZE; c++)
      {
         matC[r][c] = 0.0;
         for (int i = 0; i < MAT_SIZE; i++)
         {
            matC[r][c] = matC[r][c] + (matA[r][i] * matB[i][c]);
         }
      }
   }
}

/*
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.34 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.84 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.90 0.00 0.00 0.00 0.00 0.00


 0.00 0.10 0.74 0.00 0.11 0.00 0.00 0.64 0.00 0.05
 0.00 0.00 0.00 0.60 0.10 0.00 0.03 0.38 0.00 0.00
 0.00 0.00 0.74 0.00 0.02 0.14 0.00 0.00 0.12 0.00
 0.26 0.00 0.00 0.07 0.00 0.00 0.40 0.00 0.18 0.00
 0.00 0.00 0.00 0.00 0.47 0.00 0.12 0.00 0.00 0.00
 0.00 0.01 0.00 0.00 0.02 0.00 0.00 0.20 0.09 0.00
 0.00 0.07 0.18 0.84 0.47 0.00 0.00 0.00 0.00 0.17
 0.00 0.04 0.72 0.07 0.01 0.00 0.17 0.25 0.00 0.73
 0.27 0.00 0.00 0.00 0.84 0.00 0.00 0.10 0.13 0.00
 0.00 0.00 0.00 0.05 0.31 0.00 0.00 0.79 0.00 0.00



 Size = 200 Dyn Array Mult Elapsed Time: 0.04 seconds.



 Program ended with exit code: 0

 1. M = 86 is the smallest M that gave me a non-zero time.

 2. Since there are three nested for loops, the matrix has a cubic time complexity.
 O(N*N*N) = O(N^3). When I doubled, tripled, and quadrupled the M, the time grew by about the cubic time complexity.
 M values                        Times (seconds)
 50                              0.00
 100                             0.01
 200                             0.04
 400                             0.46
 600                             1.59
 800                             4.20
 1000                            20.66

 3. At M = 30000 my program took too long to print out the output.

 4. The data disagreed with the original time complexity estimate because for O(N^3),
 every time you increase N, the data increases more slowly.
 */
