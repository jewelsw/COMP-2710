//Ella Jewel Wolter
//ejw0073@auburn.edu
//COMP 2710 Project 1
//project1_Wolter_ejw0073.cpp
//compile with g++ project1_Wolter_ejw0073.cpp
//run with ./a.out 

//refernaces:
//used https://www.quora.com to figure out how to not include "std::" before each cin or cout.
//used www.w3schools.com for help on how to implement a "while" loop. (didnt end up using)
//refered to https://www.geeksforgeeks.org/ for how to implement a ternary operator. (didnt end up using)
//looked up how to prevent scientific notation when using .precision(2) on https://stackoverflow.com/
//used https://cplusplus.com/forum/beginner/113132/ to find how to use setw() and left, 
//then looked up https://stackoverflow.com to know to type #include <iomanip> at the top
//used https://study.com/academy/ for help with validating a user input for interest rate

//for test case 12 it doesnt pring invalid interrest rate, but it does print invalid payment...
#include <iostream>
#include <iomanip>

int main() {
//define variables
//inputs
   double loanAmnt;
   double intrRate;
   double mnthPay;
   
//working varables
   int month = 0;
   double rate;
   double balInitial;
   double balFinal;
   double principal;
   double interest;
   double totalInterest;

//take in loan amount, interest rate, and monthly payments
//make sure that the input numbers are numbers and are positive
//interest rate can be 0, but others cant
   using namespace std;
   cout << "\nLoan Amount: ";
   cin >> loanAmnt;
   if (loanAmnt <= 0) {
      cout << "Invalid Loan\n";
      return 1;
   }
   cout << "Interest Rate (% per year): ";
   //cin >> intrRate;
   if (!(cin >> intrRate) || intrRate < 0) {
      cout << "Invalid Interest Rate\n";
      return 1;
   }
   cout << "Monthly Payments: ";
   cin >> mnthPay;
   if (mnthPay <= 0) {
      cout << "Invalid Payment\n";
      return 1;
   }

   rate = intrRate / 12;
   balInitial = loanAmnt;
   
   //format the numbers
   cout << fixed;
   cout << showpoint;  
   cout.precision(2);
   
   interest = balInitial * (rate / 100);
   if (mnthPay > interest) {
   //print header for the table
      cout << "\n**********************************************************\n"
         "\tAmortization Table\n"
         "**********************************************************\n";
      cout << left << setw(9) << "Month" << left << setw(10) << "Balance" << left << setw(10) << "Payment"
         << left << setw(10) << "Rate" << left << setw(10) << "Interest" 
         << left << setw(10) << "Principal\n";
   
      cout << left << setw(9) << month << "$" << left << setw(10) << balInitial << left << setw(10) << "N/A"
         << left << setw(10) << "N/A" << left << setw(10) << "N/A" << left << setw(10) << "N/A\n";
   //do the math 
   
      for (month = 1; balInitial > 0; month++) {
         interest = balInitial * (rate / 100);
      
         if (mnthPay >= balInitial + interest) {
            principal = balInitial;
            balFinal = 0;
            cout << left << setw(9) << month << "$" << left << setw(10) << balFinal << "$" << 
               left << setw(10) << principal << left << setw(10) << rate << "$" << 
               left << setw(10) << interest << "$" << left << setw(10) << principal << "\n";
               //month, balFinal, principal, rate, interest, principal
         }
         else {
            principal = mnthPay - interest;
            balFinal = balInitial - principal;
            cout << left << setw(9) << month << "$" << left << setw(10) << balFinal << "$" << 
               left << setw(10) << mnthPay << left << setw(10) << rate << "$" << 
               left << setw(10) << interest << "$" << left << setw(10) << principal << "\n";
               //month, balFinal, mnthPay, rate, interest, principal
         }
      
         totalInterest += interest;  
         balInitial = balFinal;
      }
      //else {
         //cout << "Insufficent Payment\n";
         //return 1;
      //}
   }
   else {
      cout << "Insufficent Payment\n";
      return 1;
   }    
   month -= 1;
    //print out the footer
   cout << "**********************************************************\n\n"
      "It takes " << month << " months to pay off the loan. Total interest paid is: $" 
      << totalInterest << "\n";
   
      
      
      //print out totals (months to pay off loan and total interest)
   return 0;
}