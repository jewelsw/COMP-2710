/*Ella Jewel Wolter
*ejw0073@auburn.edu
*COMP 2710 Project 4
*project4_Wolter_ejw0073.cpp
*compile with g++ project4_Wolter_ejw0073.cpp
*run with ./a.out
*/

/*references:
 * https://www.youtube.com/watch?v=HKfj0l7ndbc - linked lists implementations
 * https://www.youtube.com/watch?v=RNMIDj62o_o - inserting node at the end of the linked list
 * https://www.quora.com/ - solve why, when running, first q cin was being skipped
*/

#include <iostream>
#include <assert.h>
using namespace std;

//quiz mode:

//global variables
int totalPts = 0;
int listLength = 2;

//defne trivia node structure
struct node {
    string question;
    string answer;
    int points;
    node* next;
    //node* prev;
};

//create/constructs linked list of trivia using node structure
node* questionList() {
    node* first = new node();
    node* second = new node();
    node* third = new node();

    first->question = "How long was the shortest war on record? (Hint: how many minutes?) ";
    first->answer = "38";
    first->points = 100;

    second-> question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany) ";
    second->answer = "Bank of Italy";
    second->points = 50;

    third->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports) ";
    third->answer = "Wii Sports";
    third->points = 20;

    first-> next = second;
    second-> next = third;
    //third next will point to added question
    third-> next = NULL;
    //MAYBE: make return value third so that when accessing add question, initQuestionLimit = head/third/start add
    //OR put it in main method...
    return first;
}

//add new node to linked list
void addQuestion(node* last) {
    //prepare new node
    string newQuestion;
    string newAnswer;
    int newPoints;

    cout << "Please enter a new question: ";
    getline (cin, newQuestion);
    cout << "Enter the answer: ";
    getline (cin, newAnswer);
    cout << "Enter award points: ";
    cin >> newPoints;
    cin.ignore();

    node* newNode = new node();
    newNode->question = newQuestion;
    newNode->answer = newAnswer;
    newNode->points = newPoints;
    newNode->next = NULL;

    //since linked list != empty, find last node
    while (last->next != NULL) {
        last = last->next;
        listLength++;
    }
    last-> next = newNode;
    //check that node was added
}

//asks user questions and compares correct answer to user input.
int askQuestions(node* n, int numToAsk) {
    string answer;
    if (listLength < 3) {
        listLength = 3;
    }
    if (numToAsk < 1 || numToAsk > listLength){
        cout << "Invalid number of questions, can ask at least 1 and up to " << listLength << ".\n";
    }
    else {
        for (int i = 0; i < numToAsk; i++) {
            cout << "Question: " << n->question << "";
            getline (cin, answer);
            if (answer == n->answer) {
                cout << "Answer: " << n->answer << "\nYou got it right";
                cout << ", and you have earned " << n->points << " points!\n";
                totalPts += n->points;
            } else {
                cout << "You got it wrong! The correct answer was " << n->answer << "\n";
            }
            n = n->next;
        }
        cout << "Your total points earned are " << totalPts << " points!\n";
    }
    return totalPts;
}

//debugging/unit test function:
void unitTest() {
    node* head = questionList();
    string correctAnswer;
    string incorrectAnswer;

    // test case 1: ask 0 questions
    cout << "Unit Test 1: ask 0 questions. The program should give a warning message."<< endl;
    askQuestions(head, 0);
    cout << "Case 1 Passed" << endl;

    // test case 2.1: ask 1 question, correct answer
    cout << "Unit Test 2.1: ask 1 question. The tester enters the correct answer: 38."<< endl;
    askQuestions(head, 1);
    getline(cin, correctAnswer);
    assert(askQuestions(head, 1) == 100);
    cout << "Case 2.1 Passed";

    // test case 2.2: ask 1 question, incorrect answer
    cout << "Unit Test 2.1: ask 1 question. The tester enters an incorrect answer."<< endl;
    askQuestions(head, 1);
    getline(cin, incorrectAnswer);
    assert(askQuestions(head, 1) == 0);
    cout << "Case 2.2 Passed." << endl;

    // test case 3.1: ask 3 questions, correct answer
    cout << "Unit Test 3.1: ask 3 questions. The tester enters all correct answers: 38, Bank of Italy, and Wii Sports."<< endl;
    askQuestions(head, 3);
    getline(cin, correctAnswer);
    assert(askQuestions(head, 1) == 170);
    cout << "Case 3.1 Passed." << endl;

    // test case 3.2: ask 3 questions, incorrect answer
    cout << "Unit Test 3.2: ask 3 questions. The tester enters an incorrect answer on the first question."<< endl;
    askQuestions(head, 3);
    getline(cin, incorrectAnswer);
    assert(askQuestions(head, 1) == 0);
    cout << "Case 3.2 Passed." << endl;


    // test case 4: ask 5 questions, exceeding amount of questions in list
    cout << "Unit Test 4: ask 5 questions. The program should give a warning message."<< endl;
    askQuestions(head, 5);
    cout << "Case 4 Passed" << endl;

}
//main
int main() {
#ifdef Unit_Test
    unitTest();

#else
    int numToAsk;
    string yesOrNo;
    node* head = questionList();

    cout << "*** Welcome to Jewels' trivia quiz game! ***\nWould you like to add a question? (Yes or No): ";
    getline (cin, yesOrNo);
    //adding new questions (if applicable)
    while (yesOrNo != "No") {
        addQuestion(head);
        cout << "Continue? (Yes/No): ";
        getline(cin, yesOrNo);
        cin.ignore();
    }

    //running with hard coded questions and any additions
    cout << "How many questions would you like to ask? ";
    cin >> numToAsk;
    cin.ignore();
    askQuestions(head, numToAsk);

    cout << "*** (: Thank you for playing Jewels' trivia quiz game! Goodbye! :) ***";
    return 0;
#endif
}

