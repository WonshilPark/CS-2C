// ---------------------------------------------------------------------------
// CS 2C Assignment #1 Part B - iTunes Version
#include <iostream>
#include <vector>
#include <ctime>
#include "iTunes.h"

using namespace std;

ostream& operator<<(ostream &out, const iTunesEntry &tune);
int operator+(int num, const iTunesEntry &tune);

// --------------- Sublist Prototype ---------------

class Sublist
{
public:
   Sublist(vector<iTunesEntry> *orig = NULL)
   : sum(0), originalObjects (orig) { }
   Sublist addItem( int indexOfItemToAdd );
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<iTunesEntry> *originalObjects;
   vector<int> indices;
};

// ------------------ main ------------------

int main()
{
   const int TARGET = 3600;
   vector<iTunesEntry> dataSet;
   vector<Sublist> choices;
   vector<Sublist>::iterator iter, iterBest;
   int k, j, numSets, max = 0, array_size, masterSum;
   bool foundPerfect = false;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
      << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
      dataSet.push_back(tunes_input[k]);

   cout << "Target time: " << TARGET << endl;

   Sublist empty(&dataSet);
   choices.push_back(empty);

   for (k = 0; k < dataSet.size(); k++)
      max = max + dataSet[k];

   if (max <= TARGET)
   {
      cout << "TARGET (" << TARGET << ") exceeds maximum sum. \n"
      << "  sum: " << max << endl;

      for (k = 0; k < dataSet.size() - 1; k++)
         cout << "  array[" << k << "] = " << dataSet[k] << ",";

      cout << "  array[" << dataSet.size() - 1 << "] = ";
      cout << dataSet[dataSet.size() - 1] << endl << endl;

      // how we determine the time elapsed -------------------
      stopTime = clock();
      // report algorithm time
      cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;
   }
   else
   {
      for (k = 0; k < dataSet.size(); k++)
      {
         numSets = choices.size();
         for (j = 0; j < numSets; j++)
         {
            if (choices[j].getSum() + dataSet[k] < TARGET)
               choices.push_back(choices[j].addItem(k));

            if (choices[j].getSum() + dataSet[k] == TARGET)
            {
               foundPerfect = true;
               choices.push_back(choices[j].addItem(k));
               break;
            }
         }
      }
      iterBest = choices.begin();
      iterBest = choices.begin();
      for (iter = choices.begin() + 1; iter != choices.end(); iter++)
         if (iter->getSum() > iterBest->getSum())
            *iterBest = *iter;

      masterSum = iterBest->getSum();
      iterBest->showSublist();

      // how we determine the time elapsed -------------------
      stopTime = clock();
      // report algorithm time
      cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

      return 0;
   }
}

// Overloaded operator functions ---------------------------

int operator+(int num, const iTunesEntry &tune)
{
   return num + tune.getTime();
}

ostream& operator<<(ostream &out, const iTunesEntry &tune)
{
   out << tune.getTitle() << " by " << tune.getArtist();
   out << "(" << tune.getTime() << ")";
   return out;
}

// --------------- Sublist Method Definitions ---------------

Sublist Sublist::addItem(int indexOfItemToAdd)
{
   Sublist newSublist = *this;
   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = sum + originalObjects->at(indexOfItemToAdd);
   return newSublist;
}

void Sublist::showSublist() const
{
   if (indices.size() == 0)
   {
      cout << "This is an empty sublist\n"
      << "{ }\n";
   }
   else
   {
      cout << "Sublist -----------------------------\n"
      << "  sum: " << sum << endl;

      for (int i = 0; i < indices.size() - 1; i++)
      {
         cout << "  array[" << indices[i] << "] = "
         << originalObjects->at(indices[i]) << ",";
      }
      cout << "  array[" << indices[indices.size() - 1] << "] = "
      << originalObjects->at(indices[indices.size() - 1]) << endl;
   }
   cout << endl;
}

/* ----------------------- runs -----------------------

 Target time: 0
 This is an empty sublist
 { }


 Algorithm Elapsed Time: 0.000111 seconds.

 Program ended with exit code: 0

 Target time: 1200
 Sublist -----------------------------
 sum: 1200
 array[0] = Cowboy Casanova by Carrie Underwood(236),  array[1] = Quitter by Carrie Underwood(220),  array[2] = Russian Roulette by Rihanna(228),  array[6] = Bad Love by Eric Clapton(308),  array[11] = Hot Cha by Roy Buchanan(208)


 Algorithm Elapsed Time: 0.023106 seconds.

 Program ended with exit code: 0

 Target time: 3600
 Sublist -----------------------------
 sum: 3600
 array[0] = Cowboy Casanova by Carrie Underwood(236),  array[1] = Quitter by Carrie Underwood(220),  array[2] = Russian Roulette by Rihanna(228),  array[4] = Monkey Wrench by Foo Fighters(230),  array[5] = Pretending by Eric Clapton(283),  array[6] = Bad Love by Eric Clapton(308),  array[7] = Everybody's In The Mood by Howlin' Wolf(178),  array[8] = Well That's All Right by Howlin' Wolf(175),  array[9] = Samson and Delilah by Reverend Gary Davis(216),  array[11] = Hot Cha by Roy Buchanan(208),  array[12] = Green Onions by Roy Buchanan(443),  array[13] = I'm Just a Prisoner by Janiva Magness(230),  array[14] = You Were Never Mine by Janiva Magness(276),  array[15] = Hobo Blues by John Lee Hooker(187),  array[16] = I Can't Quit You Baby by John Lee Hooker(182)


 Algorithm Elapsed Time: 3.56555 seconds.

 Program ended with exit code: 0

 Target time: 4799
 Sublist -----------------------------
 sum: 4799
 array[0] = Cowboy Casanova by Carrie Underwood(236),  array[1] = Quitter by Carrie Underwood(220),  array[2] = Russian Roulette by Rihanna(228),  array[3] = All My Life by Foo Fighters(263),  array[4] = Monkey Wrench by Foo Fighters(230),  array[5] = Pretending by Eric Clapton(283),  array[6] = Bad Love by Eric Clapton(308),  array[8] = Well That's All Right by Howlin' Wolf(175),  array[9] = Samson and Delilah by Reverend Gary Davis(216),  array[10] = Twelve Sticks by Reverend Gary Davis(194),  array[11] = Hot Cha by Roy Buchanan(208),  array[12] = Green Onions by Roy Buchanan(443),  array[13] = I'm Just a Prisoner by Janiva Magness(230),  array[14] = You Were Never Mine by Janiva Magness(276),  array[15] = Hobo Blues by John Lee Hooker(187),  array[16] = I Can't Quit You Baby by John Lee Hooker(182),  array[17] = That's The Homie by Snoop Dogg(343),  array[19] = Ladies and Gentleman by The Rubyz(201),  array[20] = Watch the Girl by The Rubyz(192),  array[21] = Donuts for Benny by Veggie Tales(184)


 Algorithm Elapsed Time: 103.351 seconds.

 Program ended with exit code: 0

 Target time: 100000
 TARGET (100000) exceeds maximum sum.
 sum: 22110
 array[0] = Cowboy Casanova by Carrie Underwood(236),  array[1] = Quitter by Carrie Underwood(220),  array[2] = Russian Roulette by Rihanna(228),  array[3] = All My Life by Foo Fighters(263),  array[4] = Monkey Wrench by Foo Fighters(230),  array[5] = Pretending by Eric Clapton(283),  array[6] = Bad Love by Eric Clapton(308),  array[7] = Everybody's In The Mood by Howlin' Wolf(178),  array[8] = Well That's All Right by Howlin' Wolf(175),  array[9] = Samson and Delilah by Reverend Gary Davis(216),  array[10] = Twelve Sticks by Reverend Gary Davis(194),  array[11] = Hot Cha by Roy Buchanan(208),  array[12] = Green Onions by Roy Buchanan(443),  array[13] = I'm Just a Prisoner by Janiva Magness(230),  array[14] = You Were Never Mine by Janiva Magness(276),  array[15] = Hobo Blues by John Lee Hooker(187),  array[16] = I Can't Quit You Baby by John Lee Hooker(182),  array[17] = That's The Homie by Snoop Dogg(343),  array[18] = Gangsta Luv by Snoop Dogg(257),  array[19] = Ladies and Gentleman by The Rubyz(201),  array[20] = Watch the Girl by The Rubyz(192),  array[21] = Donuts for Benny by Veggie Tales(184),  array[22] = Our Big Break by Veggie Tales(69),  array[23] = Brahms: Symphony No. 1 in C Minor Op. 68 by Berliner Philharmoniker(839),  array[24] = Brahms: Symphony No. 4 in E Minor Op. 98 by Berliner Philharmoniker(800),  array[25] = Bach: Suite for Cello No. 1 in G Major Prelude by Yo-yo Ma(141),  array[26] = Simple Gifts by Yo-yo Ma(154),  array[27] = Alimony by Ry Cooter(175),  array[28] = France Chance by Ry Cooter(168),  array[29] = The Road by Aaron Watson(204),  array[30] = Clone by Terra Incognita(298),  array[31] = Lizard Skin by Terra Incogni(270),  array[32] = Bullhead's Psalm by Blue Record(79),  array[33] = Ogeechee Hymnal by Blue Record(155),  array[34] = Oblivion by Mastadon(348),  array[35] = The Bit by Mastadon(295),  array[36] = Fire Burning by Sean Kingston(239),  array[37] = My Girlfriend by Sean Kingston(204),  array[38] = Take Your Shirt Off by T-Pain(228),  array[39] = Give It All U Got by Lil Jon(218),  array[40] = What We Talkin' About by Jay-Z(243),  array[41] = Empire State of Mind by Jay-Z(276),  array[42] = Think About It by Snoop Dog(217),  array[43] = Lil' Crips by Snoop Dog(195),  array[44] = Shuffleboard by Jeff Golub(210),  array[45] = Goin' On by Jeff Golub(356),  array[46] = Fish Fare by Jeff Golub(299),  array[47] = Noites Cariocas by Caraivana(252),  array[48] = Tico-Tico No Fuba by Caraivana(147),  array[49] = Monk/Trane by John Patitucci(434),  array[50] = Sonny Side by John Patitucci(445),  array[51] = Pirate Jenny by Nina Simone(402),  array[52] = The Other Woman by Nina Simone(186),  array[53] = Feeling Good by Nina Simone(177),  array[54] = A Love Supreme Part 1 by John Coltrane(462),  array[55] = In a Sentimental Mood by John Coltrane(256),  array[56] = Dime Si te Vas Con El by AOL Dejando Huellas(204),  array[57] = Te Amo Tanto by AOL Dejando Huella(192),  array[58] = Blues On the Corner by McCoy Tyner(367),  array[59] = Afro Blue by McCoy Tyner(742),  array[60] = Stronger by Kanye West(311),  array[61] = Good Life by Kanye West(207),  array[62] = Black Cow by Steely Dan(310),  array[63] = Kid Charlemagne by Steely Dan(278),  array[64] = Haitian Divorce by Steely Dan(351),  array[65] = Nefertiti by Herbie Hancock(451),  array[66] = Rockit by Herbie Hancock(325),  array[67] = Chameleon by Herbie Hancock(941),  array[68] = Medieval Overture by Return to Forever(313),  array[69] = Luka by Suzanne Vega(231),  array[70] = Small Blue Thing by Suzanne Vega(235),  array[71] = Something to Talk About by Bonnie Raitt(227),  array[72] = I Can't Make You Love Me by Bonnie Raitt(331),  array[73] = This Will Be by Natalie Cole(171),  array[74] = Unforgettable by Natalie Cole(211),  array[75] = Timothy by Jet(260),  array[76] = Rip It Up by Jet(200),  array[77] = Where Did Your Heart Go? by Was (Not Was)(347),  array[78] = I Blew Up The United States by Was (Not Was)(230)


 Algorithm Elapsed Time: 0.002648 seconds.

 Program ended with exit code: 0

 Target time: 4
 This is an empty sublist
 { }


 Algorithm Elapsed Time: 0.000152 seconds.

 Program ended with exit code: 0

 Target time: 200
 Sublist -----------------------------
 sum: 200
 array[76] = Rip It Up by Jet(200)


 Algorithm Elapsed Time: 0.000271 seconds.

 Program ended with exit code: 0

 Target time: 1000
 Sublist -----------------------------
 sum: 1000
 array[3] = All My Life by Foo Fighters(263),  array[5] = Pretending by Eric Clapton(283),  array[7] = Everybody's In The Mood by Howlin' Wolf(178),  array[14] = You Were Never Mine by Janiva Magness(276)


 Algorithm Elapsed Time: 0.012532 seconds.

 Program ended with exit code: 0

 ------------------------------------------------------*/
