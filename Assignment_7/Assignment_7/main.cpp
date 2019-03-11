//
//  main.cpp
//  Assignment_7
//
//  Created by Won Shil Park on 2/26/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

#include <iostream>
#include "FHvector.h"
#include <time.h>
#include <math.h>
#include <iomanip>

using namespace std;

// shellSort #1 -- using shell's outer loop
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (gap = arraySize/2;  gap > 0;  gap /= 2)  // outer gap loop
      for (pos = gap; pos < arraySize; pos++)  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int gaps[], int gapArraySize)
{
   int k, pos, arraySize, gap, gapPos;
   Comparable tmp;

   arraySize = a.size();
   gapPos = gapArraySize - 1;

   while (gaps[gapPos] >= arraySize)
      gapPos--;

   for (gap = gaps[gapPos];  gapPos >= 0; --gapPos, gap = gaps[gapPos])  // outer gap loop
      for (pos = gap; pos < arraySize; pos++)  // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

#define ARRAY_SIZE 200000
int main()
{
   clock_t startTime, stopTime;
   srand(time(NULL));
   int randomInt;

   FHvector<int> fhVectorOfInts1;
   FHvector<int> vectorOneVersion2;
   FHvector<int> vectorOneVersion3;
   FHvector<int> vectorOneVersion4;
   FHvector<int> vectorOneVersion5;

   FHvector<int> fhVectorOfInts2;
   FHvector<int> vectorTwoVersion2;
   FHvector<int> vectorTwoVersion3;
   FHvector<int> vectorTwoVersion4;
   FHvector<int> vectorTwoVersion5;

   FHvector<int> fhVectorOfInts3;
   FHvector<int> vectorThreeVersion2;
   FHvector<int> vectorThreeVersion3;
   FHvector<int> vectorThreeVersion4;
   FHvector<int> vectorThreeVersion5;

   FHvector<int> fhVectorOfInts4;
   FHvector<int> vectorFourVersion2;
   FHvector<int> vectorFourVersion3;
   FHvector<int> vectorFourVersion4;
   FHvector<int> vectorFourVersion5;

   FHvector<int> fhVectorOfInts5;
   FHvector<int> vectorFiveVersion2;
   FHvector<int> vectorFiveVersion3;
   FHvector<int> vectorFiveVersion4;
   FHvector<int> vectorFiveVersion5;

   FHvector<int> fhVectorOfInts6;
   FHvector<int> vectorSixVersion2;
   FHvector<int> vectorSixVersion3;
   FHvector<int> vectorSixVersion4;
   FHvector<int> vectorSixVersion5;

   for (int i = 0; i < 10000; i++)
   {
      randomInt = rand() % 10000;
      fhVectorOfInts1.push_back(randomInt);
      vectorOneVersion2.push_back(randomInt);
      vectorOneVersion3.push_back(randomInt);
      vectorOneVersion4.push_back(randomInt);
      vectorOneVersion5.push_back(randomInt);
   }

   for (int i = 0; i < 20000; i++)
   {
      randomInt = rand() % 20000;
      fhVectorOfInts2.push_back(randomInt);
      vectorTwoVersion2.push_back(randomInt);
      vectorTwoVersion3.push_back(randomInt);
      vectorTwoVersion4.push_back(randomInt);
      vectorTwoVersion5.push_back(randomInt);
   }

   for (int i = 0; i < 40000; i++)
   {
      randomInt = rand() % 40000;
      fhVectorOfInts3.push_back(randomInt);
      vectorThreeVersion2.push_back(randomInt);
      vectorThreeVersion3.push_back(randomInt);
      vectorThreeVersion4.push_back(randomInt);
      vectorThreeVersion5.push_back(randomInt);
   }

   for (int i = 0; i < 50000; i++)
   {
      randomInt = rand() % 50000;
      fhVectorOfInts4.push_back(randomInt);
      vectorFourVersion2.push_back(randomInt);
      vectorFourVersion3.push_back(randomInt);
      vectorFourVersion4.push_back(randomInt);
      vectorFourVersion5.push_back(randomInt);
   }

   for (int i = 0; i < 100000; i++)
   {
      randomInt = rand() % 100000;
      fhVectorOfInts5.push_back(randomInt);
      vectorFiveVersion2.push_back(randomInt);
      vectorFiveVersion3.push_back(randomInt);
      vectorFiveVersion4.push_back(randomInt);
      vectorFiveVersion5.push_back(randomInt);
   }

   for (int i = 0; i < 200000; i++)
   {
      randomInt = rand() % 200000;
      fhVectorOfInts6.push_back(randomInt);
      vectorSixVersion2.push_back(randomInt);
      vectorSixVersion3.push_back(randomInt);
      vectorSixVersion4.push_back(randomInt);
      vectorSixVersion5.push_back(randomInt);
   }

   // Gap Array ----------------------------------------------------------------
   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
   int gapArraySize = 21;

   cout << "Gap Array:\n";
   for (int i = 0; i < gapArraySize; i++)
      cout << "   " << gapArray[i];
   cout << endl << endl << endl;

   // Sedgewick Array ----------------------------------------------------------
   int sedgewickArray[30];
   int sedgewickArraySize = 0;

   for (int i = 0; i < 30; i++)
   {
      int value;
      if (i % 2 == 0)
         value = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
      else
         value = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;

      if (value > ARRAY_SIZE)
         break;

      sedgewickArray[i] = value;
      sedgewickArraySize++;
   }

   cout << "Sedgewick Gap Sequence:\n";
   for (int i = 0; i < sedgewickArraySize; i++)
      cout << "   " << sedgewickArray[i];
   cout << endl << endl << endl;

   // Other Gap Array ----------------------------------------------------------
   int otherGapArray[35];
   int otherGapArraySize = 0;

   for(int i = 0; i < 35; i++)
   {
      int value = pow(2, i);

      if (value > ARRAY_SIZE)
         break;

      otherGapArray[i] = value;
      otherGapArraySize++;
   }

   cout << "Other Gap Sequence:\n";
   for (int i = 0; i < otherGapArraySize; i++)
      cout << "   " << otherGapArray[i];
   cout << endl << endl << endl;

   // Another Gap Array --------------------------------------------------------
   int anotherGapArray[40];
   int anotherGapArraySize = 0;

   for(int i = 0; i < 40; i++)
   {
      int value = pow(3, i);

      if (value > ARRAY_SIZE)
         break;

      anotherGapArray[i] = value;
      anotherGapArraySize++;
   }

   cout << "Another Gap:\n";
   for (int i = 0; i < anotherGapArraySize; i++)
      cout << "   " << anotherGapArray[i];
   cout << endl << endl << endl;

   // Time ---------------------------------------------------------------------
   double implicit1, implicit2, implicit3, implicit4, implicit5, implicit6;
   double gapArray1, gapArray2, gapArray3, gapArray4, gapArray5, gapArray6;
   double sedge1, sedge2, sedge3, sedge4, sedge5, sedge6;
   double other1, other2, other3, other4, other5, other6;
   double another1, another2, another3, another4, another5, another6;

   // Implicit
   startTime = clock();
   shellSort1(fhVectorOfInts1);
   stopTime = clock();
   implicit1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(fhVectorOfInts2);
   stopTime = clock();
   implicit2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(fhVectorOfInts3);
   stopTime = clock();
   implicit3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(fhVectorOfInts4);
   stopTime = clock();
   implicit4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(fhVectorOfInts5);
   stopTime = clock();
   implicit5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(fhVectorOfInts6);
   stopTime = clock();
   implicit6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   // Gap Array
   startTime = clock();
   shellSortX(vectorOneVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorTwoVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorThreeVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFourVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFiveVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorSixVersion2, gapArray, gapArraySize);
   stopTime = clock();
   gapArray6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   // Sedgewick
   startTime = clock();
   shellSortX(vectorOneVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorTwoVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorThreeVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFourVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFiveVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorSixVersion3, sedgewickArray, sedgewickArraySize);
   stopTime = clock();
   sedge6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   // Other
   startTime = clock();
   shellSortX(vectorOneVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorTwoVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorThreeVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFourVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFiveVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorSixVersion4, otherGapArray, otherGapArraySize);
   stopTime = clock();
   other6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   // Another
   startTime = clock();
   shellSortX(vectorOneVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorTwoVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorThreeVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFourVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorFiveVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(vectorSixVersion5, anotherGapArray, anotherGapArraySize);
   stopTime = clock();
   another6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   // Table titles
   cout << "Array Size" << setw(14)
   <<  "Implicit" << setw(14)
   << "Gap Array" << setw(15)
   << "Sedgewick" << setw(15)
   << "Other" << setw(12)
   << "Another\n";

   // Size 10,000
   cout << fhVectorOfInts1.size() << setw(19)
   << implicit1 << setw(14)
   << gapArray1 << setw(15)
   << sedge1 << setw(15)
   << other1 << setw(11)
   << another1 << endl;

   // Size 20,000
   cout << fhVectorOfInts2.size() << setw(19)
   << implicit2 << setw(14)
   << gapArray2 << setw(15)
   << sedge2 << setw(15)
   << other2 << setw(11)
   << another2 << endl;

   // Size 40,000
   cout << fhVectorOfInts3.size() << setw(19)
   << implicit3 << setw(14)
   << gapArray3 << setw(15)
   << sedge3 << setw(15)
   << other3 << setw(11)
   << another3 << endl;

   // Size 50,000
   cout << fhVectorOfInts4.size() << setw(19)
   << implicit4 << setw(14)
   << gapArray4 << setw(15)
   << sedge4 << setw(15)
   << other4 << setw(11)
   << another4 << endl;

   // Size 100,000
   cout << fhVectorOfInts5.size() << setw(18)
   << implicit5 << setw(14)
   << gapArray5 << setw(15)
   << sedge5 << setw(15)
   << other5 << setw(11)
   << another5 << endl;

   // Size 200,000
   cout << fhVectorOfInts6.size() << setw(18)
   << implicit6 << setw(14)
   << gapArray6 << setw(15)
   << sedge6 << setw(15)
   << other6 << setw(11)
   << another6 << endl;

   return 0;
}
/* ---------------------------------- Output -----------------------------------
 Gap Array:
 1   2   4   8   16   32   64   128   256   512   1024   2048   4096   8192   16384   32768   65536   131072   262144   524288   1048576


 Sedgewick Gap Sequence:
 1   5   19   41   109   209   505   929   2161   3905   8929   16001   36289   64769   146305


 Other Gap Sequence:
 1   2   4   8   16   32   64   128   256   512   1024   2048   4096   8192   16384   32768   65536   131072


 Another Gap:
 1   3   9   27   81   243   729   2187   6561   19683   59049   177147


 Array Size      Implicit     Gap Array      Sedgewick          Other    Another
 10000           0.006767      0.008554       0.003694       0.009609   0.009559
 20000           0.014879      0.027115       0.008139       0.027935   0.031838
 40000           0.030799      0.083725       0.017793       0.085211   0.080175
 50000           0.039659      0.113952       0.022795       0.113919    0.09875
 100000          0.097237      0.330329       0.055986       0.316332   0.237401
 200000          0.185248      0.787509       0.118619       0.777802   0.717145
 Program ended with exit code: 0

 ****QUESTIONS****
 Why does Shell's gap sequence implied by shellSort1() give a different timing
 result than the explicit array described above and passed to shellSortX()?

 ANSWER: The explicit array and the shellSort1() give a different timing because
 the numbers are generated differently. In the shellSort1(), the numbers are
 generated by dividing the size by two repeatedly. This allows the gap to have
 both odd and even numbers, and many other varieties. In the explicit array,
 the numbers are generated by factors of 2. This creates gaps that are in uniform.


 Which is faster and why?

 ANSWER: shellSort1() is faster because the explicit array is created by factors
 of 2. This creates similar and uniform gaps which makes the program re-sort what
 was already sorted. Furthermore, the odd and even numvers are not mixed until
 the last number has been sorted. This in itself is significantly slower and less
 efficient than the shellSort1().
 */
