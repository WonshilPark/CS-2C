//
//  main.cpp
//  Assignment_9
//
//  Created by Won Shil Park on 3/20/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"

// --------------- main ---------------
int main()
{
   int finalFlow;

   FHflowGraph<string, int> myGraph1, myG;

   // Module graph
   // didn't add the graph 2 part because there is no Kruskal function
   cout << "Module inserts:\n";
   myGraph1.addEdge("v1","v2", 2);    myGraph1.addEdge("v1","v4", 1);
   myGraph1.addEdge("v2","v4", 3);    myGraph1.addEdge("v2","v5", 10);
   myGraph1.addEdge("v3","v1", 4);    myGraph1.addEdge("v3","v6", 5);
   myGraph1.addEdge("v4","v3", 2);    myGraph1.addEdge("v4","v5", 2);
   myGraph1.addEdge("v4","v6", 8);    myGraph1.addEdge("v4","v7", 4);
   myGraph1.addEdge("v5","v7", 6);
   myGraph1.addEdge("v7","v6", 1);

   myGraph1.showResAdjTable();
   myGraph1.showFlowAdjTable();

   myGraph1.setStartVert("v1");
   myGraph1.setEndVert("v7");

   // From assignment's sample main
   cout << "\nSample main:\n";
   myG.addEdge("s","a", 3);    myG.addEdge("s","b", 2);
   myG.addEdge("a","b", 1);    myG.addEdge("a","c", 3); myG.addEdge("a","d", 4);
   myG.addEdge("b","d", 2);
   myG.addEdge("c","t", 2);
   myG.addEdge("d","t", 3);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   // My main
   // clear graph
   myG.clear();
   cout << "\nMy main:\n";
   myG.addEdge("r","s", 4);    myG.addEdge("r","b", 2);
   myG.addEdge("s","b", 1);    myG.addEdge("s","h", 4); myG.addEdge("s","d", 6);
   myG.addEdge("b","d", 5);
   myG.addEdge("h","l", 5);
   myG.addEdge("d","l", 4);

   // show the original flow graph
   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("r");
   myG.setEndVert("l");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   return 0;
}

/*
 Module inserts:
 ------------------------
 Adj Res List for v1: v2(2) v4(1) v3(0)
 Adj Res List for v2: v1(0) v4(3) v5(10)
 Adj Res List for v4: v1(0) v2(0) v5(2) v3(2) v6(8) v7(4)
 Adj Res List for v5: v2(0) v4(0) v7(6)
 Adj Res List for v3: v1(4) v4(0) v6(5)
 Adj Res List for v6: v4(0) v3(0) v7(0)
 Adj Res List for v7: v4(0) v5(0) v6(1)

 ------------------------
 Adj Flow List for v1: v2(0) v4(0)
 Adj Flow List for v2: v4(0) v5(0)
 Adj Flow List for v4: v5(0) v3(0) v6(0) v7(0)
 Adj Flow List for v5: v7(0)
 Adj Flow List for v3: v1(0) v6(0)
 Adj Flow List for v6:
 Adj Flow List for v7: v6(0)


 Sample main:
 ------------------------
 Adj Res List for s: a(3) b(2)
 Adj Res List for a: s(0) b(1) c(3) d(4)
 Adj Res List for b: s(0) a(0) d(2)
 Adj Res List for c: a(0) t(2)
 Adj Res List for d: a(0) b(0) t(3)
 Adj Res List for t: c(0) d(0)

 ------------------------
 Adj Flow List for s: a(0) b(0)
 Adj Flow List for a: b(0) c(0) d(0)
 Adj Flow List for b: d(0)
 Adj Flow List for c: t(0)
 Adj Flow List for d: t(0)
 Adj Flow List for t:

 Final flow: 5
 ------------------------
 Adj Res List for s: a(0) b(0)
 Adj Res List for a: s(3) b(1) c(1) d(3)
 Adj Res List for b: s(2) a(0) d(0)
 Adj Res List for c: a(2) t(0)
 Adj Res List for d: a(1) b(2) t(0)
 Adj Res List for t: c(2) d(3)

 ------------------------
 Adj Flow List for s: a(3) b(2)
 Adj Flow List for a: b(0) c(2) d(1)
 Adj Flow List for b: d(2)
 Adj Flow List for c: t(2)
 Adj Flow List for d: t(3)
 Adj Flow List for t:


 My main:
 ------------------------
 Adj Res List for r: s(4) b(2)
 Adj Res List for s: r(0) b(1) h(4) d(6)
 Adj Res List for b: r(0) s(0) d(5)
 Adj Res List for h: s(0) l(5)
 Adj Res List for d: s(0) b(0) l(4)
 Adj Res List for l: h(0) d(0)

 ------------------------
 Adj Flow List for r: s(0) b(0)
 Adj Flow List for s: b(0) h(0) d(0)
 Adj Flow List for b: d(0)
 Adj Flow List for h: l(0)
 Adj Flow List for d: l(0)
 Adj Flow List for l:

 Final flow: 6
 ------------------------
 Adj Res List for r: s(0) b(0)
 Adj Res List for s: r(4) b(0) h(2) d(5)
 Adj Res List for b: r(2) s(1) d(2)
 Adj Res List for h: s(2) l(3)
 Adj Res List for d: s(1) b(3) l(0)
 Adj Res List for l: h(2) d(4)

 ------------------------
 Adj Flow List for r: s(4) b(2)
 Adj Flow List for s: b(1) h(2) d(1)
 Adj Flow List for b: d(3)
 Adj Flow List for h: l(2)
 Adj Flow List for d: l(4)
 Adj Flow List for l:

 Program ended with exit code: 0
 */
