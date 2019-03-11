//
//  main.cpp
//  Assignment_6
//
//  Created by Won Shil Park on 2/22/19.
//  Copyright © 2019 Won Shil Park. All rights reserved.
//

#include <iostream>
#include <string>
#include <time.h>
#include "EBookEntry.h"

using namespace std;

// ----------- prototypes -------------
int Hash(const EBookEntry & item);
int Hash(const string & key);
int Hash(int key);

#include "FHhashQPwFind.h"

int getKey(const EBookEntry & item);
//string getKey( const EBookEntry & item);

const int NUM_RANDOM_INDICES = 25;
int main()
{
   int i;
   srand(time(NULL));
   EBookEntryReader bookInput("catalog-short4.txt");
   EBookEntry book;
   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
                                             //FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   // we want two books to be identical in different ways:  ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << bookInput.getFileName() << endl;
   cout << "Number of books inside text file: " << bookInput.getNumBooks() << endl;

   // create a QP hash table of EBooks ...
   // generate some random indices into the EBookEntryReader vector ...
   // insert all books into the hash table (if SORT_BY_ID) or fewer (If SORT_BY_CREATOR) ...
   // display NUM_RANDOM_INDICES books from array ...
   for (i = 0; i < bookInput.getNumBooks(); i++)
      hashTable.insert(bookInput[i]);

   int randomIndices[NUM_RANDOM_INDICES];
   for (i = 0; i < NUM_RANDOM_INDICES; i++)
      randomIndices[i] = (int)(rand()) % bookInput.getNumBooks();

   cout << NUM_RANDOM_INDICES << " Random books found: \n" << endl;

   for (i = 0; i < NUM_RANDOM_INDICES; i++)
   {
      cout << "ETextNum: " << bookInput[randomIndices[i]].getETextNum() << endl;
      cout << "Random book #" << i << endl;
      cout << "Title: " << bookInput[randomIndices[i]].getTitle() << endl;
      cout << "   Creator: " << bookInput[randomIndices[i]].getCreator() << endl;
      cout << "   Subject: " << bookInput[randomIndices[i]].getSubject() << endl;
      cout << endl << endl;
   }

   // attempt to find on the selected key
   cout << "The same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find(bookInput[randomIndices[k]].getETextNum());
         //book = hashTable.find( bookInput[ randomIndices[k] ].getCreator() );
         cout << "ETextNum: " << book.getETextNum() << endl;
         cout << "Random book from hash table #" << k << endl;
         cout << "Title: " << book.getTitle() << endl;
         cout << "   Creator: " << book.getCreator() << endl;
         cout << "   Subject: " << book.getSubject() << endl;
         cout << endl << endl;

      }
      catch (...)
      {
         cout << "not found\n";
      }
      cout << endl;
   }

   // test known failures exceptions:
   try
   {
      book = hashTable.find( -3 );
      //book = hashTable.find( "Jack Kerouac" );
      cout << "Found book: " << book.getTitle() << endl;

   }
   catch (...)
   {
      cout << "not found\n";
   }

   // more failures

   try
   {
      book = hashTable.find(INT_MAX);
      //book = hashTable.find( "Ray Park" );
      cout << "Found book: " << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "not found\n";
   }

   try
   {
      book = hashTable.find(-1);
      //book = hashTable.find( "Sam West" );
      cout << "Found book: " << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "not found\n";
   }
}

// used for author equality
/*
 string getKey( const EBookEntry & item )
 {
 return item.getCreator() ;
 }
 */

int Hash(const EBookEntry & item)
{
   return Hash(item.getETextNum());  // used for ID equality
                                     //return Hash( item.getCreator() );  // used for author equality
}

// a hash routine for strings that admits negative returns
int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for(k = 0; k < key.length( ); k++ )
      retVal = 37 * retVal + key[k];

   return retVal;
}

int Hash(int key)
{
   return key;
}

// used for ID equality
int getKey(const EBookEntry & item)
{
   return item.getETextNum();
}

/*--------------------------------eTextNum as a key field----------------------------
 catalog-short4.txt
 Number of books inside text file: 4863
 25 Random books found:

 ETextNum: 24779
 Random book #0
 Title: Millennium
 Creator: Cole, Everett B., 1918-
 Subject: Science fiction, American


 ETextNum: 25729
 Random book #1
 Title: Travel Tales in the Promised Land (Palestine)
 Creator: May, Karl Friedrich, 1842-1912
 Subject: Middle East -- Description and travel


 ETextNum: 28104
 Random book #2
 Title: The Pulpit Of The Reformation, Nos. 1, 2, 3 and 4.
 Creator: Welch, John, 1568?-1622
 Subject: Sermons, English


 ETextNum: 25302
 Random book #3
 Title: Jack1877
 Creator: Daudet, Alphonse, 1840-1897
 Subject: PQ


 ETextNum: 9506
 Random book #4
 Title: Georgian Poetry 1913-15
 Creator: (no data found)
 Subject: (no data found)


 ETextNum: 28075
 Random book #5
 Title: The Christian Foundation, Or, Scientific and Religious Journal, March, 1880
 Creator: Various
 Subject: Religion and science -- Periodicals


 ETextNum: 29263
 Random book #6
 Title: The Autobiography of Sergeant William LawrenceA Hero of the Peninsular and Waterloo Campaigns
 Creator: Lawrence, William, 1791-1867
 Subject: Great Britain. Army -- Military life


 ETextNum: 25979
 Random book #7
 Title: Sonnets of Shakespeare's Ghost
 Creator: Thornton, Gregory
 Subject: Shakespeare, William, 1564-1616 -- Poetry


 ETextNum: 25873
 Random book #8
 Title: The Motor Girls on Crystal Bayor, The Secret of the Red Oar
 Creator: Penrose, Margaret
 Subject: Detective and mystery stories


 ETextNum: 27993
 Random book #9
 Title: BruinThe Grand Bear Hunt
 Creator: Reid, Mayne, 1818-1883
 Subject: Adventure and adventurers -- Fiction


 ETextNum: 28935
 Random book #10
 Title: Captain Dieppe
 Creator: Hope, Anthony, 1863-1933
 Subject: PR


 ETextNum: 29521
 Random book #11
 Title: Enamels and Cameos and other Poems
 Creator: Gautier, Théophile, 1811-1872
 Subject: French poetry -- Translations into English


 ETextNum: 5338
 Random book #12
 Title: Mark Rutherford's Deliverance
 Creator: Rutherford, Mark, 1831-1913
 Subject: PR


 ETextNum: 112
 Random book #13
 Title: Violists
 Creator: McGowan, Richard, 1958-
 Subject: Love stories


 ETextNum: 28614
 Random book #14
 Title: Ave Roma Immortalis, Vol. 1Studies from the Chronicles of Rome
 Creator: Crawford, F. Marion (Francis Marion), 1854-1909
 Subject: Rome (Italy) -- Description and travel


 ETextNum: 28740
 Random book #15
 Title: The Girls of Central High in CampOr, the Old Professor's Secret
 Creator: Morrison, Gertrude W.
 Subject: Camps -- Juvenile fiction


 ETextNum: 29794
 Random book #16
 Title: Tree, Spare that Woodman
 Creator: Dryfoos, Dave
 Subject: Science fiction


 ETextNum: 26262
 Random book #17
 Title: Utility of Quaternions in Physics
 Creator: McAulay, Alexander, 1863-1931
 Subject: Mathematical physics


 ETextNum: 28439
 Random book #18
 Title: The Comings of Cousin Ann
 Creator: Sampson, Emma Speed, 1868-1947
 Subject: PS


 ETextNum: 26268
 Random book #19
 Title: Romeo and Juliet
 Creator: Shakespeare, William, 1564-1616
 Subject: Vendetta -- Drama


 ETextNum: 28468
 Random book #20
 Title: The American Missionary — Volume 54, No. 2, April, 1900
 Creator: Various
 Subject: Congregational churches -- Missions -- Periodicals


 ETextNum: 25034
 Random book #21
 Title: Report of the Chief Librarianfor the Year Ended 31 March 1958: Special Centennial Issue
 Creator: Wilson, J. O.
 Subject: General Assembly Library -- Periodicals


 ETextNum: 28004
 Random book #22
 Title: A Little Tour of France
 Creator: James, Henry, 1843-1916
 Subject: France -- Description and travel


 ETextNum: 25418
 Random book #23
 Title: The Baby's Opera
 Creator: Crane, Walter, 1845-1915
 Subject: Nursery rhymes


 ETextNum: 30294
 Random book #24
 Title: The Century Handbook of Writing
 Creator: Jones, Easley S. (Easley Stephen), 1884-1947
 Subject: English language -- Rhetoric


 The same random books from the hash table
 ETextNum: 24779
 Random book from hash table #0
 Title: Millennium
 Creator: Cole, Everett B., 1918-
 Subject: Science fiction, American



 ETextNum: 25729
 Random book from hash table #1
 Title: Travel Tales in the Promised Land (Palestine)
 Creator: May, Karl Friedrich, 1842-1912
 Subject: Middle East -- Description and travel



 ETextNum: 28104
 Random book from hash table #2
 Title: The Pulpit Of The Reformation, Nos. 1, 2, 3 and 4.
 Creator: Welch, John, 1568?-1622
 Subject: Sermons, English



 ETextNum: 25302
 Random book from hash table #3
 Title: Jack1877
 Creator: Daudet, Alphonse, 1840-1897
 Subject: PQ



 ETextNum: 9506
 Random book from hash table #4
 Title: Georgian Poetry 1913-15
 Creator: (no data found)
 Subject: (no data found)



 ETextNum: 28075
 Random book from hash table #5
 Title: The Christian Foundation, Or, Scientific and Religious Journal, March, 1880
 Creator: Various
 Subject: Religion and science -- Periodicals



 ETextNum: 29263
 Random book from hash table #6
 Title: The Autobiography of Sergeant William LawrenceA Hero of the Peninsular and Waterloo Campaigns
 Creator: Lawrence, William, 1791-1867
 Subject: Great Britain. Army -- Military life



 ETextNum: 25979
 Random book from hash table #7
 Title: Sonnets of Shakespeare's Ghost
 Creator: Thornton, Gregory
 Subject: Shakespeare, William, 1564-1616 -- Poetry



 ETextNum: 25873
 Random book from hash table #8
 Title: The Motor Girls on Crystal Bayor, The Secret of the Red Oar
 Creator: Penrose, Margaret
 Subject: Detective and mystery stories



 ETextNum: 27993
 Random book from hash table #9
 Title: BruinThe Grand Bear Hunt
 Creator: Reid, Mayne, 1818-1883
 Subject: Adventure and adventurers -- Fiction



 ETextNum: 28935
 Random book from hash table #10
 Title: Captain Dieppe
 Creator: Hope, Anthony, 1863-1933
 Subject: PR



 ETextNum: 29521
 Random book from hash table #11
 Title: Enamels and Cameos and other Poems
 Creator: Gautier, Théophile, 1811-1872
 Subject: French poetry -- Translations into English



 ETextNum: 5338
 Random book from hash table #12
 Title: Mark Rutherford's Deliverance
 Creator: Rutherford, Mark, 1831-1913
 Subject: PR



 ETextNum: 112
 Random book from hash table #13
 Title: Violists
 Creator: McGowan, Richard, 1958-
 Subject: Love stories



 ETextNum: 28614
 Random book from hash table #14
 Title: Ave Roma Immortalis, Vol. 1Studies from the Chronicles of Rome
 Creator: Crawford, F. Marion (Francis Marion), 1854-1909
 Subject: Rome (Italy) -- Description and travel



 ETextNum: 28740
 Random book from hash table #15
 Title: The Girls of Central High in CampOr, the Old Professor's Secret
 Creator: Morrison, Gertrude W.
 Subject: Camps -- Juvenile fiction



 ETextNum: 29794
 Random book from hash table #16
 Title: Tree, Spare that Woodman
 Creator: Dryfoos, Dave
 Subject: Science fiction



 ETextNum: 26262
 Random book from hash table #17
 Title: Utility of Quaternions in Physics
 Creator: McAulay, Alexander, 1863-1931
 Subject: Mathematical physics



 ETextNum: 28439
 Random book from hash table #18
 Title: The Comings of Cousin Ann
 Creator: Sampson, Emma Speed, 1868-1947
 Subject: PS



 ETextNum: 26268
 Random book from hash table #19
 Title: Romeo and Juliet
 Creator: Shakespeare, William, 1564-1616
 Subject: Vendetta -- Drama



 ETextNum: 28468
 Random book from hash table #20
 Title: The American Missionary — Volume 54, No. 2, April, 1900
 Creator: Various
 Subject: Congregational churches -- Missions -- Periodicals



 ETextNum: 25034
 Random book from hash table #21
 Title: Report of the Chief Librarianfor the Year Ended 31 March 1958: Special Centennial Issue
 Creator: Wilson, J. O.
 Subject: General Assembly Library -- Periodicals



 ETextNum: 28004
 Random book from hash table #22
 Title: A Little Tour of France
 Creator: James, Henry, 1843-1916
 Subject: France -- Description and travel



 ETextNum: 25418
 Random book from hash table #23
 Title: The Baby's Opera
 Creator: Crane, Walter, 1845-1915
 Subject: Nursery rhymes



 ETextNum: 30294
 Random book from hash table #24
 Title: The Century Handbook of Writing
 Creator: Jones, Easley S. (Easley Stephen), 1884-1947
 Subject: English language -- Rhetoric



 not found
 not found
 not found
 Users-MacBook-Pro-3:Assignment_6 wonshilpark$

 --------------------------------string key field----------------------------
 catalog-short4.txt
 Number of books inside text file: 4863
 25 Random books found:

 ETextNum: 30039
 Random book #0
 Title: Adventurers of the Far NorthA Chronicle of the Frozen Seas
 Creator: Leacock, Stephen, 1869-1944
 Subject: Arctic regions


 ETextNum: 25670
 Random book #1
 Title: Sea-Dogs All!A Tale of Forest and Sea
 Creator: Bevan, Tom, 1868-
 Subject: Historical fiction


 ETextNum: 18515
 Random book #2
 Title: Police!!!
 Creator: Chambers, Robert W. (Robert William), 1865-1933
 Subject: (no data found)


 ETextNum: 28484
 Random book #3
 Title: The Philosophy of the Conditioned
 Creator: Mansel, Henry Longueville, 1820-1871
 Subject: Hamilton, William, Sir, 1788-1856


 ETextNum: 24953
 Random book #4
 Title: The Flemmings And &quot;Flash Harry&quot; Of SavaitFrom &quot;The Strange Adventure Of James Shervinton and OtherStories&quot; - 1902
 Creator: Becke, Louis, 1855-1913
 Subject: Oceania -- Fiction


 ETextNum: 27395
 Random book #5
 Title: The Slave of Silence
 Creator: White, Fred M. (Fred Merrick), 1859-
 Subject: PR


 ETextNum: 28742
 Random book #6
 Title: Memorials of Old LondonVolume I
 Creator: (no data found)
 Subject: London (England) -- History


 ETextNum: 29637
 Random book #7
 Title: Introduction to the Study of History
 Creator: Langlois, Charles Victor, 1863-1929
 Subject: History -- Study and teaching


 ETextNum: 3234
 Random book #8
 Title: Letters of the Younger Pliny, First Series — Volume 1
 Creator: Pliny, the Younger, 62?-113
 Subject: Pliny, the Younger -- Correspondence


 ETextNum: 1260
 Random book #9
 Title: Jane Eyre
 Creator: Brontë, Charlotte, 1816-1855
 Subject: Orphans -- Fiction


 ETextNum: 22157
 Random book #10
 Title: Lectures on Stellar Statistics
 Creator: Charlier, Carl Vilhelm Ludvig, 1862-1934
 Subject: Astronomy


 ETextNum: 10978
 Random book #11
 Title: Hidden Creek
 Creator: Burt, Katharine Newlin, 1882-1977
 Subject: (no data found)


 ETextNum: 28457
 Random book #12
 Title: Golden Stars in Tatting and Crochet
 Creator: Riego de la Branchardière, Éléonore
 Subject: Crocheting -- Patterns


 ETextNum: 28601
 Random book #13
 Title: The Christian Foundation, Or, Scientific and Religious Journal, June, 1880
 Creator: Various
 Subject: Religion and science -- Periodicals


 ETextNum: 20390
 Random book #14
 Title: Elements of Structural and Systematic BotanyFor High Schools and Elementary College Courses
 Creator: Campbell, Douglas Houghton, 1859-1953
 Subject: Botany -- Textbooks


 ETextNum: 28245
 Random book #15
 Title: Prisoners of Poverty Abroad
 Creator: Campbell, Helen, 1839-1918
 Subject: Women -- Employment


 ETextNum: 28573
 Random book #16
 Title: Le Morvan, [A District of France,] Its Wild Sports, Vineyards and Forests; with Legends, Antiquities, Rural and Local Sketches
 Creator: Crignelle, Henri de
 Subject: Morvan (France)


 ETextNum: 27943
 Random book #17
 Title: The Home Medical Library, Volume I (of VI)
 Creator: (no data found)
 Subject: Medicine


 ETextNum: 2091
 Random book #18
 Title: Reserved: The Writings of Samuel Adams - Volume 1
 Creator: Adams, Samuel, 1722-1803
 Subject: United States -- Politics and government -- 1775-1783


 ETextNum: 24865
 Random book #19
 Title: The Premiere
 Creator: Sabia, Richard
 Subject: Science fiction


 ETextNum: 29560
 Random book #20
 Title: M. P.'s in SessionFrom Mr. Punch's Parliamentary Portrait Gallery
 Creator: Furniss, Harry, 1854-1925
 Subject: Caricatures and cartoons -- Great Britain


 ETextNum: 26201
 Random book #21
 Title: The Story of Doctor Doolittle
 Creator: Lofting, Hugh, 1886-1947
 Subject: Fantasy


 ETextNum: 27531
 Random book #22
 Title: A Manual of Moral Philosophy
 Creator: Peabody, Andrew P. (Andrew Preston), 1811-1893
 Subject: Ethics


 ETextNum: 26019
 Random book #23
 Title: Europa's Fairy Book
 Creator: Jacobs, Joseph, 1854-1916
 Subject: Fairy tales -- Europe


 ETextNum: 28024
 Random book #24
 Title: Pictorial Photography in America 1922
 Creator: Pictorial Photographers of America
 Subject: Photography, Artistic -- Periodicals


 The same random books from the hash table
 ETextNum: 28919
 Random book from hash table #0
 Title: Frenzied Fiction
 Creator: Leacock, Stephen, 1869-1944
 Subject: Humorous stories, Canadian



 ETextNum: 25670
 Random book from hash table #1
 Title: Sea-Dogs All!A Tale of Forest and Sea
 Creator: Bevan, Tom, 1868-
 Subject: Historical fiction



 ETextNum: 28440
 Random book from hash table #2
 Title: The Dark Star
 Creator: Chambers, Robert W. (Robert William), 1865-1933
 Subject: PS



 ETextNum: 28484
 Random book from hash table #3
 Title: The Philosophy of the Conditioned
 Creator: Mansel, Henry Longueville, 1820-1871
 Subject: Hamilton, William, Sir, 1788-1856



 ETextNum: 28972
 Random book from hash table #4
 Title: The Works Of Louis BeckeA Linked Index to the Project Gutenberg Editions
 Creator: Becke, Louis, 1855-1913
 Subject: Indexes



 ETextNum: 27395
 Random book from hash table #5
 Title: The Slave of Silence
 Creator: White, Fred M. (Fred Merrick), 1859-
 Subject: PR



 ETextNum: 28351
 Random book from hash table #6
 Title: Dick and His Cat and Other Tales
 Creator: (no data found)
 Subject: Animals -- Juvenile fiction



 ETextNum: 29637
 Random book from hash table #7
 Title: Introduction to the Study of History
 Creator: Langlois, Charles Victor, 1863-1929
 Subject: History -- Study and teaching



 ETextNum: 3234
 Random book from hash table #8
 Title: Letters of the Younger Pliny, First Series — Volume 1
 Creator: Pliny, the Younger, 62?-113
 Subject: Pliny, the Younger -- Correspondence



 ETextNum: 1260
 Random book from hash table #9
 Title: Jane Eyre
 Creator: Brontë, Charlotte, 1816-1855
 Subject: Orphans -- Fiction



 ETextNum: 22157
 Random book from hash table #10
 Title: Lectures on Stellar Statistics
 Creator: Charlier, Carl Vilhelm Ludvig, 1862-1934
 Subject: Astronomy



 ETextNum: 10978
 Random book from hash table #11
 Title: Hidden Creek
 Creator: Burt, Katharine Newlin, 1882-1977
 Subject: (no data found)



 ETextNum: 28457
 Random book from hash table #12
 Title: Golden Stars in Tatting and Crochet
 Creator: Riego de la Branchardière, Éléonore
 Subject: Crocheting -- Patterns



 ETextNum: 28712
 Random book from hash table #13
 Title: The American Missionary — Volume 54, No. 3, October, 1900
 Creator: Various
 Subject: Congregational churches -- Missions -- Periodicals



 ETextNum: 20390
 Random book from hash table #14
 Title: Elements of Structural and Systematic BotanyFor High Schools and Elementary College Courses
 Creator: Campbell, Douglas Houghton, 1859-1953
 Subject: Botany -- Textbooks



 ETextNum: 28245
 Random book from hash table #15
 Title: Prisoners of Poverty Abroad
 Creator: Campbell, Helen, 1839-1918
 Subject: Women -- Employment



 ETextNum: 28573
 Random book from hash table #16
 Title: Le Morvan, [A District of France,] Its Wild Sports, Vineyards and Forests; with Legends, Antiquities, Rural and Local Sketches
 Creator: Crignelle, Henri de
 Subject: Morvan (France)



 ETextNum: 28351
 Random book from hash table #17
 Title: Dick and His Cat and Other Tales
 Creator: (no data found)
 Subject: Animals -- Juvenile fiction



 ETextNum: 2091
 Random book from hash table #18
 Title: Reserved: The Writings of Samuel Adams - Volume 1
 Creator: Adams, Samuel, 1722-1803
 Subject: United States -- Politics and government -- 1775-1783



 ETextNum: 24865
 Random book from hash table #19
 Title: The Premiere
 Creator: Sabia, Richard
 Subject: Science fiction



 ETextNum: 29560
 Random book from hash table #20
 Title: M. P.'s in SessionFrom Mr. Punch's Parliamentary Portrait Gallery
 Creator: Furniss, Harry, 1854-1925
 Subject: Caricatures and cartoons -- Great Britain



 ETextNum: 26201
 Random book from hash table #21
 Title: The Story of Doctor Doolittle
 Creator: Lofting, Hugh, 1886-1947
 Subject: Fantasy



 ETextNum: 27531
 Random book from hash table #22
 Title: A Manual of Moral Philosophy
 Creator: Peabody, Andrew P. (Andrew Preston), 1811-1893
 Subject: Ethics



 ETextNum: 26460
 Random book from hash table #23
 Title: English Fairy Tales
 Creator: Jacobs, Joseph, 1854-1916
 Subject: Folklore -- England



 ETextNum: 28023
 Random book from hash table #24
 Title: Pictorial Photography in America 1921
 Creator: Pictorial Photographers of America
 Subject: Photography, Artistic -- Periodicals



 not found
 not found
 not found
 Users-MacBook-Pro-3:Assignment_6 wonshilpark$
 */
