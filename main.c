// Name: Sukhanin Deol
// Class: SD 247
// Date 1/18/2024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

/**
 * Asks the user for the difficulty level integer
 * 
 * @param min - minimum difficulty allowed 
 * @param max - maximum difficulty allowed 
 * 
 * @return integer inputted by user
 */
int askForDifficulty(int min, int max);

/** 
 * Asks the user to input their number guess
 * 
 * @param attempts - the current attempt number
 * @param randNum - the correct number
 * 
 * @returns boolean of if the guess was correct
*/
bool askForGuess(int attempts, int randNum);

/**
 * Prints a message based on whether the user won or not
 * 
 * @param isWon - whether the user won or ran out of attempts
 * @param attempts - number of attempts used
 * @param randNum - the correct number
 */
void printResult(bool isWon, int attempts, int randNum);


int main() 
{
    // minimum and maximum difficulty options (careful of integer limits when changing)
    const int MIN_DIFFICULTY = 1;
    const int MAX_DIFFICULTY = 5;

    // the base in which each difficulty magnifies the range
    const int DIFFICULTY_MULTIPLIER = 10;

    // maximum attempts to guess the correct number
    const int MAX_ATTEMPTS = 10;

    // introduction message
    printf("Welcome to the Guess the Number Game! \n");

    // ask user for chosen difficulty
    int difficulty = askForDifficulty(MIN_DIFFICULTY, MAX_DIFFICULTY);

    // calculate max range for guessing game (using a for-loop to apply exponent)
    int rangeMax = 1;
    for (int i = 0; i < difficulty; i++) { rangeMax *= DIFFICULTY_MULTIPLIER; }

    // give random number generator a seed based on current time
    srand(time(NULL));

    // generate random number between 0 to rangeMax (+1 is required, else when randNum == rangemax will be 0)
    int randNum = rand() % (rangeMax+1);

    // data to track game end
    int attempts = 0;
    bool isWon = false;

    // Game begins
    printf("Please guess a number between 1 and %d \n", rangeMax);

    // game loop
    while (attempts < MAX_ATTEMPTS && !isWon)
    {
        attempts++;
        isWon = askForGuess(attempts, randNum);
    }

    // game end
    printResult(isWon, attempts, randNum);
    return 0;
}


int askForDifficulty(int min, int max) 
{
    printf("Please choose a difficulty from %d-%d: ", min, max);
    int difficulty;
    scanf("%d", &difficulty);
    fflush(stdin); // cleans input buffer

    // recurse to re-prompt user if bad input
    if (difficulty > max|| difficulty < min)
    {
        printf("ERROR: Undefined Difficulty Choice\n");
        return askForDifficulty(min, max);
    }

    return difficulty;
}


bool askForGuess(int attempts, int randNum)
{
    // ask player for guess
    printf("Attempt %d Guess: ", attempts);

    int playerChoice;
    // check if inputted value is a valid int
    if (!(scanf("%d", &playerChoice) == 1))
    {
        printf("ERROR: Undefined Player Choice\n");
        return false;
    }
    fflush(stdin); // cleans input buffer

    if (playerChoice > randNum)
    {
        printf("Too High! Try Again.\n");
    }
    else if (playerChoice < randNum)
    {   
        printf("Too Low! Try Again.\n");
    }
    else if (playerChoice == randNum)
    {   // return true if correct
        return true;
    }
    return false; // return false if not correct
}


void printResult(bool isWon, int attempts, int randNum)
{
    if (isWon)
    {
        printf("\nCongratulations! You guessed the correct number in %d attempt(s)", attempts);
    }
    else 
    {
        printf("You ran out of attempts. The number was %d.", randNum);
    }
}