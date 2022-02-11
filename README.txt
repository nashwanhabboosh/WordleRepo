This program uses an algorithm based on letter frequencies to find optimal guesses in the game WORDLE

Explaining the game:
The objective of the game is to guess a five letter keyword
The user inputs five letter words one by one and is given the following information for each letter in the guess word
-This letter from the guess word does not appear in the keyword
-This letter from the guess word is appears in a different location in the keyword then it does in the guess word
-This letter from the guess word appears in the same location in the guess word
These three outcomes are denoted as black, yellow, and green respectively.

Explaining the algorithm:
The user enters a starting guess and the information gotten from the guess.
The most common letter at each position in the word is found and these letters are combined into a word.
If this word is a valid guess, the guess is made.
