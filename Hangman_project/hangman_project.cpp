#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
const unsigned MAX_WORD_LENGTH = 11;

void Menu(unsigned& chosenOption)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 13);
	cout << "MENU:" << endl;
	cout << " 1. Start a new game" << endl << " 2. Settings" << endl << " 3. Exit " << endl << "Enter a number: ";
	cin >> chosenOption;
	if (chosenOption < 1 || chosenOption>3)
	{
		cout << "Invalid input! Try again: ";
		cin >> chosenOption;
	}
	SetConsoleTextAttribute(h, 7);
}

void Settings(unsigned& wordLength, unsigned& numberAttempts)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
	cout << endl;
	cout << "1. Choose the word's length:" << endl << " 1. 3-5 letters" << endl << " 2. 6-7 letters" << endl << " 3. 8-10 letters" << endl << " 4. Skip this option.";
	cout << endl << "Enter a number: ";
	cin >> wordLength;
	if (wordLength < 1 || wordLength > 4) //napravi dopulnitelna proverka dali e chislo!!!
	{
		cout << "Invalid input! Try again: ";
		cin >> wordLength;
	}

	cout << endl;
	unsigned chosenAttemptsOption;
	SetConsoleTextAttribute(h, 11);
	cout << "2. Choose the number of the attempts:" << endl << " 1. Choose a number between 1 and 20. " << endl << " 2. Skip this option." << endl;
	cout << "Enter a number: ";
	cin >> chosenAttemptsOption;
	if (chosenAttemptsOption == 1)
	{
		cout << "Enter the number of the attempts: ";
		cin >> numberAttempts;
		if (numberAttempts < 1 || numberAttempts > 20)
		{
			cout << "Invalid input! Try again: ";
			cin >> numberAttempts;
		}
	}
	else if (chosenAttemptsOption == 2)
		numberAttempts = 5;
	else
	{
		cout << "Invalid input! Try again: ";
		cin >> numberAttempts;
	}

	SetConsoleTextAttribute(h, 7);
}

void getRandomWord(const vector<vector<string>> dictionary, string& gameword, unsigned wordLength)
{
	unsigned randomWordIndex = 0;
	unsigned rowNumber = 0;
	srand(time(0)); //how does it work?
	if (wordLength == 1)
		randomWordIndex = rand() % dictionary[0].size();
	else if (wordLength == 2)
	{
		randomWordIndex = rand() % dictionary[1].size();
		rowNumber = 1;
	}
	else if (wordLength == 3)
	{
		randomWordIndex = rand() % dictionary[2].size();
		rowNumber = 2;
	}
	else
	{
		rowNumber = rand() % dictionary.size();
		randomWordIndex = rand() % dictionary[rowNumber].size();

	}

	gameword = dictionary[rowNumber][randomWordIndex];
}

void hideWord(const string gameWord, char* hiddenWord)
{
	unsigned gameWordLength = gameWord.length();
	for (unsigned i = 0; i < gameWordLength; i++)
		hiddenWord[i] = '_';
	hiddenWord[gameWordLength] = '\0';
}

void printHiddenWord(char* hiddenWord)
{
	while (*hiddenWord != '\0')
	{
		cout << *hiddenWord << " ";
		hiddenWord++;
	}
}

bool doesItContain(const string gameWord, const char guess, char* hiddenWord)
{
	unsigned gameWordLength = gameWord.length();
	bool doesItContain = false;
	for (size_t i = 0; i < gameWordLength; i++)
	{
		if (gameWord[i] == guess)
		{
			hiddenWord[i] = gameWord[i];
			doesItContain = true;
		}
	}
	if (doesItContain)
		return true;
	else
		return false;

}

bool guessCheck(char guess)
{
	if (guess < 'a' || guess > 'z')
		return false;
	return true;
}

bool areTheSame(string gameWord, unsigned gameWordLength, char* hiddenWord)
{
	for (unsigned i = 0; i < gameWordLength; i++)
	{
		if (gameWord[i] != hiddenWord[i])
			return false;
	}
	return true;
}

void hangman(const vector<vector<string>> dictionary, unsigned wordLength, unsigned numberAttempts, unsigned& chosenOption)
{
	while (chosenOption != 1)
	{
		Menu(chosenOption);
		if (chosenOption == 3)
			exit(-1);
		else if (chosenOption == 2)
		{
			Settings(wordLength, numberAttempts);
		}

		cout << endl;
	}
	cout << "Let's start the game!" << endl;
	string gameWord = " ";
	char hiddenWord[MAX_WORD_LENGTH];
	getRandomWord(dictionary, gameWord, wordLength);
	hideWord(gameWord, hiddenWord);
	char guess;
	bool win = true;
	while (numberAttempts != 0)
	{
		cout << "Attempts left: " << numberAttempts << ". Guess the word ";
		printHiddenWord(hiddenWord);
		cout << endl;
		cout << "Enter your guess: ";
		cin >> guess;
		if (!guessCheck(guess))
		{
			cout << endl << "Invalid input! Try again: ";
			cin >> guess;
		}
		if (!doesItContain(gameWord, guess, hiddenWord))
		{
			numberAttempts--;
		}
		unsigned gameWordLength = gameWord.length();
		win = true;
		for (unsigned i = 0; i < gameWordLength; i++)
		{
			if (gameWord[i] != hiddenWord[i])
				win = false;
		}

		if (win)
		{
			cout << endl << "Congrats! You guessed the word " << gameWord << "!" << endl;
			break;
		}

	}
	if (!win)
	{
		cout << "Sorry, you lost the game! The word is " << gameWord << "." << endl;
	}

	cout << endl;
	Menu(chosenOption);
}

int main()
{

	vector <vector<string>> dictionary = {
	{ "bed", "cat", "dog", "card", "park", "rain", "zombi", "lemon", "scare" },
	{ "coffee", "camera", "castle", "success", "tonight", "desktop" },
	{"building", "engineer", "location", "education", "chocolate", "motivation" }
	};

	unsigned wordLength = 0;
	unsigned numberAttempts = 5;
	unsigned chosenOption = 0;
	while (chosenOption != 3)
	{
		switch (chosenOption)
		{
		case 0:
			hangman(dictionary, wordLength, numberAttempts, chosenOption);
			break;
		case 1:
			hangman(dictionary, wordLength, numberAttempts, chosenOption);
			break;
		case 2:
			Settings(wordLength, numberAttempts);
			chosenOption = 0;
			break;
		}
	}
	exit(-1);


	return 0;
}


