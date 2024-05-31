## Optimizing Wordle Guesses: A Letter Frequency-Based Algorithm

### Introduction

This program employs an advanced algorithm rooted in letter frequencies to enhance guesses in the popular word game, WORDLE.

### Understanding WORDLE

WORDLE is a game where players aim to guess a five-letter keyword. Players input five-letter words iteratively and receive feedback for each letter in the guessed word. The feedback indicates whether the letter:
- Does not appear in the keyword.
- Appears in a different position than in the keyword.
- Appears in the same position as in the keyword.

These feedback types are denoted by black, yellow, and green respectively.

### The Algorithm

For every word in the dictionary, the algorithm computes a score. The word with the highest score is recommended as the next guess. The scoring process is outlined as follows:

1. **Letter Position Scoring**: For each letter 'x' at position 'n' in the guessed word:
   - The algorithm counts the occurrences of 'x' at position 'n' in all other words in the dictionary. This count represents the score for that letter.
  
2. **Handling Repeat Letters**: If a guessed word contains duplicate letters, the score for each subsequent occurrence of a letter diminishes. Specifically, after the first appearance, the score for each subsequent occurrence is only one-fourth of its original value.

3. **Total Score Calculation**: The sum of the scores for each letter in the guessed word yields the total score for that word.

4. **Guess Selection**: The guess with the highest score is recommended to the user. If more than 60% of the letters have been correctly found, the program suggests the user look through the possible remaning words and select the one most normally used.

### Additional Features

In addition to the core algorithm, here are several features to be implemented.

- **Optional Command Line Argument for Dictionary File**: Users can specify a custom dictionary file through a command line argument.
- **Integration as a Chrome Extension**: Future iterations of the program envision offering both a simplified version and an expanded version with additional data as a Chrome extension.