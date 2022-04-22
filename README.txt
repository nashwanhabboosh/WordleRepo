This program uses an algorithm based on letter frequencies to find optimal guesses in the game WORDLE

Compiled for linux using c++ 17

Explaining the game WORDLE:
The objective of the game is to guess a five letter keyword
The user inputs five letter words one by one and is given the following information for each letter in the guess word
-This letter from the guess word does not appear in the keyword
-This letter from the guess word is appears in a different location in the keyword then it does in the guess word
-This letter from the guess word appears in the same location in the guess word
These three outcomes are denoted as black, yellow, and green respectively.

Explaining the algorithm:
For each word "guess" in the dictionary, calculates a score.
The word with the highest score is suggested.
The score is calculated as follows:
For each letter 'x' at position 'n' in the "guess", 
the number of times that 'x' appears at position 'n'
in the other words in the dictionary is the score for that letter.
If a "guess" contains repeat letters, 
each time after the first that a letter appears, 
its score is only counted as 1/4th of what it would be otherwise.
The sum of the scores for each letter in "guess" is the score for "guess".

add
if there are less than 5 words possible, say to look at possible words
add optional command line arg for dictionary file