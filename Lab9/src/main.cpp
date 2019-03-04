/*******************************************
Author: Martin Edmunds
Assignment: Lab 9 
Class: CS 162
Date: 03/04/19
Description: Program that implements STL containers
for a queue and a stack. Both containers utilize an underlying
list type for containment.

The queue container adds and remove numbers based on a %chance decided
by the user. The stack container is used to print a palindrome string.

********************************************/


#include <iostream>
#include <stack>
#include "InputValidationFunctions.hpp"
#include "Menu.hpp"
#include "NumGenerator.hpp"
#include <iterator>
#include <list>

#define DEFAULT_ROUNDS			100
#define DEFAULT_GEN_PERCENT		25
#define DEFAULT_REMOVE_PERCENT	25



int main() {

	srand(time(0));

	std::list<int> userQueue;		//create queue with list as underlying container
	std::stack<char, std::list<char> > userStack;		//create stack with list as underlying container

	int rounds = DEFAULT_ROUNDS;
	int generatePercent = DEFAULT_GEN_PERCENT;
	int removalPercent = DEFAULT_REMOVE_PERCENT;

	Menu queueMenu;		//create menu for queue section
	queueMenu.addPrompt("Enter number of rounds for simulation.");
	queueMenu.addPrompt("Enter percent chance to add a number to the queue.");
	queueMenu.addPrompt("Enter percent chance to remove number from the queue");
	queueMenu.addPrompt("Continue");

	Menu stackMenu;		//create menu for stack section


	//handle logic for queueMenu
	int userChoice;


	while ((userChoice = queueMenu.getUserChoice()) != queueMenu.getExitCode()){  //while the user hasnt selected '4' (exit code)
		switch (userChoice) {
			
		case 1:	//set number of rounds for sim
			rounds = validateInputGreaterThan(1, "Enter number of rounds for simulation:");
			break;

		case 2:	//set percent chance to generate to queue
			generatePercent = validateInputRange(1, 100, "Enter percent chance to add a number to the queue.");
			break;

		case 3:	//set percent chance to remove from queue
			removalPercent = validateInputRange(1, 100, "Enter percent chance to remove number from the queue.");
			break;

		default:
			break;
		}

	}


	float averageLength = 0;
	float previousAverage = 0;

	for (int i = 1; i <= rounds; i++) {	//run simulation for number of rounds

		int numToAdd = generateRandomInt(1, 1000);		//generate number to add

		int addCheck = generateRandomInt(1, 100);		//check if chance occurs to add

		if (addCheck <= generatePercent) {
			//add number to queue
			userQueue.push_back(numToAdd);				//add to back of queue
		}

		int removeCheck = generateRandomInt(1, 100);	//check if chance occurs to remove

		if (removeCheck <= removalPercent) {
			if (!userQueue.empty()) {
				userQueue.pop_front();					//remove from front of queue
			}
		}


		//print queue
		std::cout << "Buffer: " << std::endl;
		for (auto it = userQueue.begin(); it != userQueue.end(); it++) { //create iterator to loop through queue
			std::cout << *it << " ";	//print value
		}
		std::cout << std::endl;



		//output average length of buffer
		averageLength = ( (previousAverage * ((float)i - (float)1) + (float)userQueue.size()) ) / (float)i;	//calc average length
		

		std::cout << "Average Length:" << std::endl;
		std::cout << averageLength << std::endl;

		previousAverage = averageLength;

		std::cout << "\n\n\n" << std::endl;

	}



	std::string userInput;							//create string to store user input
	std::string palindromeString = "";				//create string buffer to store original string + palindrome



	stackMenu.displayMessage("Enter a string to create a palindrome: ");
	clearInputStream();	//clear "\n" chars from input
	std::getline(std::cin, userInput);				//get user input


	for (int i = 0; i < userInput.size(); i++) {	//for every character in put string
		userStack.push(userInput[i]);				//push character onto stack
		palindromeString += userInput[i];			//copy character into palindrome string
	}


	while (!userStack.empty()) {
		palindromeString += userStack.top();		//to create second half of palindrome, add top of stack to string, pop stack
		userStack.pop();
	}


	std::cout << "Palidrome:" << std::endl;			//print palindrome string
	std::cout << palindromeString << std::endl;

	std::cin.ignore('\n', 3434);
	std::cin.get();


	return 0;
}