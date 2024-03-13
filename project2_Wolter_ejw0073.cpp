/*Ella Jewel Wolter
*ejw0073@auburn.edu
*COMP 2710 Project 2
*project2_Wolter_ejw0073.cpp
*compile with g++ project2_Wolter_ejw0073.cpp
*run with ./a.out
*/

/*referances:
*used stackoverflow.com to realize that my srand(time(0)) was missing a specifier and was out of place
*looked at www.softwaretestinghelp.com/assert-in-cpp/ for more info on assert()
*referenced www.geeksforgeeks.org for more help with the ternary operator
*/

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>

using namespace std;
//constant variables
double aaronProb = 0.3333333;
double bobProb = .5;
double charlieProb = 1.0;

int totalDuels = 10000;

//prototypes

/*Inputs:   aAlive indicates whether aaron is alive
*           bAlive indicates whether bob is alive
*           cAlive indicates whether charlie is alive
*Return:    true if at least two are alive
*           false otherwise                                  
*/
bool at_least_two_alive(bool aAlive, bool bAlive, bool cAlive) {
   int playersAlive = 0;

   if (aAlive) {
      playersAlive += 1;
   }
   if (bAlive) {
      playersAlive += 1;
   }
   if (cAlive) {
      playersAlive += 1;
   }

   if (playersAlive >= 2) {
      return true;
   }
   else {
      return false;
   }
}

/*Performs the shot
*Input:     double prob indicates the person whose 
*           currently shooting's probability
*Return:    true if the shot is successful (person's prob > prob)
*           false otherwise                                 
*/
bool shoot(double prob) {
   int randNum = rand() % 100; 
   return randNum < (prob * 100);
}

/*Strategy 1: Use call by reference
* Input:    bAlive indicates whether Bob alive or dead
*           cAlive indicates whether Charlie is alive or dead
* Change:   Change bAlive into false if Bob is killed.
*           Change cAlive into false if Charlie is killed. 
* Return:   return 2 if charlie is being shot at
*           return 1 if bob is being shot at 
*/
int Aaron_shoots1(bool& bAlive, bool& cAlive) {
   if (cAlive) {
      bool shoots = shoot(aaronProb);
      cAlive = shoots ? false : cAlive;
      return 2;
   }
   else if (bAlive) {
      bool shoots = shoot(aaronProb);
      bAlive = shoots ? false : bAlive;
      return 1;
   }
   return 3; 
}

/*Call by reference
* Input:    aAlive indicates if Aaron is alive or dead
*           cAlive indicates whether Charlie is alive or dead
* Change:   Change aAlive into false if Aaron is killed.
*           Change cAlive into false if Charlie is killed. 
* Return:   return 2 if charlie is being shot at
*           return 0 if aaron is being shot at  
*/
int Bob_shoots(bool& aAlive, bool& cAlive) {
   if (cAlive) {
      bool shoots = shoot(bobProb);
      if (shoots) {
         cAlive = false;
      }
      return 2;
   }
   else if (aAlive) {
      bool shoots = shoot(bobProb);
      if (shoots) {
         aAlive = false;
      }
      return 0;
   }
   return 3;
}

/*Call by reference
* Input:    aAlive indicates if Aaron is alive or dead
*           bAlive indicates whether Bob is alive or dead
* Change:   Change aAlive into false if Aaron is killed.
*           Change bAlive into false if Bob is killed. 
* Return:   return 1 if bob is being shot at
*           return 0 if aaron is being shot at      
*/
int Charlie_shoots(bool& aAlive, bool& bAlive) {
   if (bAlive) {
      bool shoots = shoot(charlieProb);
      if (shoots) {
         bAlive = false;
      }
      return 1;
   }
   else if (aAlive) {
      bool shoots = shoot(charlieProb);
      if (shoots) {
         aAlive = false;
      }
      return 0;
   }
   return 3;
}

/*Strategy 2: Use call by reference
* Input:    bAlive indicates whether Bob alive or dead
*           cAlive indicates whether Charlie is alive or dead
* Return:   Change bAlive into false if Bob is killed.
*           Change cAlive into false if Charlie is killed.   
*/
int Aaron_shoots2(bool& bAlive, bool& cAlive) {
   if (bAlive && cAlive) {
      return 3;
   //no action is taken-- aaron intentionally misses his first shot
   }
   return Aaron_shoots1(bAlive, cAlive);
}


//Actual Duel
/*runs the duel
*Input:     strategy indicates whether strategy 1 or 2 is used
*Return:    number cooresponding to who is still  alive.
*           0 for aaron, 1 for bob, 2 for charlie
*/
int duel(int strategy) {
   bool aAlive = true;
   bool bAlive = true;
   bool cAlive = true;
   
   while (at_least_two_alive(aAlive, bAlive, cAlive)) {
      if (aAlive) {
         if (strategy == 1) {
            Aaron_shoots1(bAlive, cAlive);
         }
         else if (strategy == 2) {
            Aaron_shoots2(bAlive, cAlive);
         }
      }
      if (bAlive) {
         Bob_shoots(aAlive, cAlive);
      }
      if (cAlive) {
         Charlie_shoots(aAlive, bAlive);
      }
   }
   
   return aAlive ? 0 : bAlive ? 1 : cAlive ? 2 : 3;
}

//Continuation Tool
void continue_tool(void) {
   cout << "Press Enter to continue...";
   cin.ignore().get(); //Pause Command for Linux Terminal
}

//Test Drivers 

/*Test Driver for at_least_two_alive()
*gives every possible combonation of persons status
*/ 
void test_at_least_two_alive(void){
   cout << "Unit Testing 1: Function, at_least_two_alive()\n";
   
   cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(true, true, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(false, true, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
   assert(true == at_least_two_alive(true, false, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
   assert(true == at_least_two_alive(true, true, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase passed...\n";
   
   cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase passed...\n";
   
   continue_tool();
}

/*Test Driver for Aaron_shoots1()
*gives truth values to Bob and Charlie and tests which one 
*Aaron shoots at based on which hes supposed to first.
*/
void test_Aaron_shoots1(void) {
   cout << "Unit Testing 2: Function, Aaron_shoots1(bAlive, cAlive)\n";

   cout << "\tCase 1: Bob alive, Charlie alive\n";
   bool bob = true;
   bool charlie = true;
   assert(2 == Aaron_shoots1(bob, charlie));
   cout << "\tAaron is shooting at Charlie\n";

   cout << "\tCase 2: Bob dead, Charlie alive\n";
   bob = false;
   charlie = true;
   assert(2 == Aaron_shoots1(bob, charlie));
   cout << "\tAaron is shooting at Charlie\n";

   cout << "\tCase 3: Bob alive, Charlie dead\n";
   bob = true;
   charlie = false;
   assert(1 == Aaron_shoots1(bob, charlie));
   cout << "\tAaron is shooting at Bob\n";

   continue_tool();
}

/*Test Driver for Bob_shoots()
*gives truth values to Aaron and Charlie and tests which one 
*Bob shoots at based on which hes supposed to first.
*/
void test_Bob_shoots(void) {
   cout << "Unit Testing 3: Function, Bob_shoots(aAlive, cAlive)\n";

   cout << "\tCase 1: Aaron alive, Charlie alive\n";
   bool aaron = true;
   bool charlie = true;
   assert(2 == Bob_shoots(aaron, charlie));
   cout << "\tBob is shooting at Charlie\n";

   cout << "\tCase 2: Aaron dead, Charlie alive\n";
   aaron = false;
   charlie = true;
   assert(2 == Bob_shoots(aaron, charlie));
   cout << "\tBob is shooting at Charlie\n";

   cout << "\tCase 3: Aaron alive, Charlie dead\n";
   aaron = true;
   charlie = false;
   assert(0 == Bob_shoots(aaron, charlie));
   cout << "\tBob is shooting at Aaron\n";

   continue_tool();
}

/*Test Driver for Charlie_shoots()
*gives truth values to Aaron and Bob and tests which one 
*Charlie shoots at based on which hes supposed to first.
*/
void test_Charlie_shoots(void) {
   cout << "Unit Testing 4: Function, Charlie_shoots(aAlive, bAlive)\n";

   cout << "\tCase 1: Aaron alive, Bob alive\n";
   bool aaron = true;
   bool bob = true;
   assert(1 == Charlie_shoots(aaron, bob));
   cout << "\tCharlie is shooting at Bob\n";

   cout << "\tCase 2: Aaron dead, Bob alive\n";
   aaron = false;
   bob = true;
   assert(1 == Charlie_shoots(aaron, bob));
   cout << "\tCharlie is shooting at Bob\n";

   cout << "\tCase 3: Aaron alive, Bob dead\n";
   aaron = true;
   bob = false;
   assert(0 == Bob_shoots(aaron, bob));
   cout << "\tCharlie is shooting at Aaron\n";

   continue_tool();
}

/*Test Driver for Aaron_shoots2()
*gives truth values to Bob and Charlie and tests which one 
*Aaron shoots at based on which hes supposed to first and shows that
*he intentionally misses his first shot.
*/
void test_Aaron_shoots2(void) {
   cout << "Unit Testing 5: Function, Aaron_shoots2()\n";

   cout << "\tCase 1: Bob alive, Charlie alive\n";
   bool bob = true; 
   bool charlie = true;
   assert(3 == Aaron_shoots2(bob, charlie));
   cout << "\tAaron intentionally misses his first shot\n";
   assert(bob == true); 
   assert(charlie == true);
   cout << "\tBoth Bob and Charlie are alive\n";

   cout << "\tCase 2: Bob dead, Charlie alive\n";
   bob = false; 
   charlie = true;
   assert(2 == Aaron_shoots2(bob, charlie));
   cout << "\tAaron is shooting at Charlie\n";

   cout << "\tCase 3: Bob alive, Charlie dead\n";
   bob = true; 
   charlie = false;
   assert(1 == Aaron_shoots2(bob, charlie));
   cout << "\tAaron is shooting at Bob\n";

   continue_tool();
}

/*finally running the duel
*/
int duelFinal(int strategy) {
   cout << "Ready to test strategy " << strategy << " (run 10,000 times):\n";
   continue_tool();

   int aWins = 0;
   int bWins = 0; 
   int cWins = 0;
   
   for (int i = 0; i < totalDuels; i++) {
      int result = duel(strategy);
      
      switch (result) {
         case 0: 
            aWins++;
            break;
         case 1: 
            bWins++;
            break;
         case 2: 
            cWins++;
            break;
      }
   }
  
   cout << "Aaron won " << aWins << "/10000 duels or " << static_cast<double>(aWins) / 100 << "%\n";
   cout << "Bob won " << bWins << "/10000 duels or " << static_cast<double>(bWins) / 100 << "%\n";
   cout << "Charlie won " << cWins << "/10000 duels or " << static_cast<double>(cWins) / 100 << "%\n";
   cout << endl;

   return aWins;
}

int main(){
//format the numbers
   cout << fixed;
   cout << showpoint;  
   cout.precision(2);
   
//random seed based on time
   srand(time(0));
   rand();

   cout << "***Welcome to Jewels' Duel Simulator!***\n";

//tests output
   test_at_least_two_alive();
   test_Aaron_shoots1();
   test_Bob_shoots();
   test_Charlie_shoots();
   test_Aaron_shoots2();
   
//strategy 1 output
   int aWins1 = duelFinal(1);
   
//strategy 2 output
   int aWins2 = duelFinal(2);

//final thoughts 
   if (aWins1 > aWins2) {
      cout << "Strategy 1 is better than strategy 2. (no it isnt)";
   }
   else if (aWins2 > aWins1) {
      cout << "Strategy 2 is better than strategy 1.";
   }
   else {
      cout <<  "they are equal.";
   }
   
   cout << endl;
   return 3;
}
