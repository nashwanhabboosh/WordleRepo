#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <list>
#include <ctype.h>

#define WORD_LENGTH 5

// initially gets the words from the input file 
std::list<std::string>* parseDictionary (const std::string &inputFile) {
    
    std::ifstream istr (inputFile);

    // holds the words
    std::list<std::string>* words = new std::list<std::string>();

    // holds each word temporarily
    std::string temp;

    // iterate through the file of words
    while (istr>>temp) {

        // convert letters to lowercase
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        
        // ensures all inputs are correct length
        if (temp.size()!=WORD_LENGTH) {
            std::cerr<<"ERROR: word of incorrect length encountered: \""<<
            temp<<"\" length "<<temp.size()<<" should be "<<WORD_LENGTH<<std::endl; 
            exit(EXIT_FAILURE);
        }

        words->push_back(temp);
    }

    return words;
}

// guess is taken and stored as an array of pairs 
// first is the letter second is letter value
// 0-not in word
// 1-wrong location
// 2-correct location
std::pair<char,int>* makeGuess (std::vector<bool>& correctLetters) {

    // holds the current WORD_LENGTH letter word guess
    std::string guess;
    // holds all of the letters and the data on its correctness
    std::pair<char,int>* data = new std::pair<char,int>[WORD_LENGTH];
    // holds the color of each letter
    std::string color;

    // promps user and stores guess
    std::cout<<"Enter Guess\n";
    std::cin>>guess;
    if (guess.length()!=WORD_LENGTH) {
        std::cerr<<"ERROR: invalid guess, length must be "<<WORD_LENGTH<<" not "<<guess.length()<<std::endl;
        return nullptr;
    }

    // makes sure only valid chars are used in the word
    for (short i = 0;i<WORD_LENGTH;i++) {
        if (!isalpha(guess[i])) {
            std::cerr<<"ERROR: guess contains invalid character: "<<guess[i]<<std::endl;
            return nullptr;
        }
    }

    // gets data on each letter
    std::cout<<"What color was each letter?\n";
    for (short i = 0;i<WORD_LENGTH;i++) {

        // adds each letter to data
        data[i].first=guess[i];

        // gets the color for each letter
        std::cout<<guess[i]<<std::endl;
        std::cin>>color;
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (color=="green"||color == "g") {
            data[i].second=2;
            correctLetters[i]=true;
        } else if (color == "yellow"||color == "y") {
            data[i].second=1;
        } else if (color == "black"||color == "b") {
            data[i].second=0;
        } else {
            std::cout<<"Invalid color, please type \"green\", \"yellow\" or \"black\"\n";
            i--;
        }
    }
    return data;
}

// gets the number of 'true's in an array of bools
int getTrueCount (std::vector<bool>& arr) {
    
    // holds number of trues
    int count = 0;

    // iterate through the array
    for (int i = 0;i<arr.size();i++) {
        
        // iterate count for each true
        if (arr[i]) {
            count++;
        }
    }

    return count;
}

// prompts the user for what action to take
int prompt () {
    std::cout<<"Would you like to:\n"<<
                "1. Make a guess\n"<<
                "2. See possible remaining words\n"<<
                "3. See letter data\n"<<
                "4. See suggested guess\n"<<
                "0. Exit the program"<<std::endl;

    // take character input and convert it to int
    char temp;
    std::cin>>temp;
    int tempNum = (int)temp-48;

    if (tempNum<0||tempNum>4) {
        std::cerr<<(int)temp<<" ERROR: Invalid option, please select an option from 0 - 4\n\n";
        return prompt();
    }
    return tempNum;
}

// print out the remaining words
void printWords(const std::list<std::string> &words) {

    if (!words.size()) {
        std::cout<<"There are no remaining possible words."<<std::endl;
        return;
    }

    std::cout<<"Remaining possibilites: "<<std::endl;

    // iterate through the words and print them
    std::list<std::string>::const_iterator itr = words.begin();
    for (unsigned int i = 0;i<words.size();i++) {
        std::cout<<*itr<<" ";
        itr++;

        // add a line break every 5 words
        if (i%5==4||i==words.size()-1) std::cout<<std::endl; 
    }
}

// determines if a letter appears more than once in a word
bool multipleApperances (char c, std::string word) {

    // counts the number of appearances of the letter
    int count = 0;
    
    // loop through the guess, iterating the count if the letter is encountered
    for (short i = 0;i<WORD_LENGTH;i++) {
        if (word[i]==c) count++;
    }

    return count>1;
}

// determines if a letter appears more than once in a guess
bool multipleApperances (char c, std::pair<char,int>* word) {

    // counts the number of appearances of the letter
    int count = 0;
    
    // loop through the guess, iterating the count if the letter is encountered
    for (short i = 0;i<WORD_LENGTH;i++) {
        if (word[i].first==c) count++;
    }

    return count>1;
}

// remove all words that dont meet the criteria of the guess
void updateWordList (std::list<std::string> &oldWords, 
                    std::pair<char,int>* &guess) {

    // iterates through the list of words
    for (std::list<std::string>::iterator itr = oldWords.begin();itr!=oldWords.end(); ) {
        
        std::string word = *itr;
        
        // holds whether the word was deleted or not
        bool deleted = false;

        // iterates through all the letters of the guessed word
        for (unsigned short i = 0;i<WORD_LENGTH;i++) {
            
            // if the letter is not in the word, remove the word
            if (guess[i].second==0&&word.find(guess[i].first)!=std::string::npos) {

                // if the letter appears only once in the guess and word, remove it
                if (!multipleApperances(guess[i].first,guess)) {

                    // remove the word and set flag to true
                    itr = oldWords.erase(itr);
                    deleted = true;
                    break;
                }
            } 

            // if the letter is in the wrong location
            // removes the word if the letter is in the word in the correct location
            // or it is not in the word at all
            else if (guess[i].second==1&&
                    (word[i]==guess[i].first ||
                    word.find(guess[i].first)==std::string::npos)) {
                    
                    // if the letter appears only once in the guess and word, remove it
                    if (!multipleApperances(guess[i].first,guess)) {

                        // remove the word and set flag to true
                        itr = oldWords.erase(itr);
                        deleted = true;
                        break;
                    }
            }

            // if the letter is in the correct position
            else if (guess[i].second==2&&guess[i].first!=word[i]){

                // remove the word and set flag to true
                itr = oldWords.erase(itr);
                deleted = true;
                break;
            }   
        }

        // iterate to the next word if none were deleted
        if (!deleted) {
            deleted = false;
            itr++;
        }
    }
}

// returns the best guess for the current word list 
// generates a score for each word based on how many occurences each 
// letter in the word has at that position
// for example, if in the word "smart", 
// s appears 100 times in the first position
// m appears 100 times in the second position
// etc, then the score for "smart" would be 500
// if a letter appears more than once in a word, its score for the non
// first appearances is halved
// whichever word has the highest score is suggested 
std::string getBestGuess(std::map<char,std::vector<int>>& characters, const std::list<std::string>& words) {
    
    // if there are no remaining possible words
    if (!words.size()) {
        return "-1";
    }
    
    // holds the highest score so far encountered and the word it came from
    double maxScore = 0;
    std::string bestWord = "";

    // iterates through all the possible words
    for (std::string word : words) {
        
        // holds the score for the current word
        double currentScore = 0;

        // iterates through each letter of the current word
        for (unsigned int i = 0;i<WORD_LENGTH;i++) {

            // if the letter has already appeared
            if (word.find(word[i])!=i) {
                currentScore += (0.25*characters[word[i]][i]);
            } 
            
            // if the letter has not yet appeared
            else {
                currentScore += characters[word[i]][i];
            }
            
        }
        // if this word is better then the previous best, remember it
        if (currentScore>maxScore) {
            maxScore = currentScore;
            bestWord = word;
        }
    }
    return bestWord;
}

// returns a map of the frequencies of each letter at each position
// first WORD_LENGTH elements of the vector are the positions in the word, 
// last element is total occurences
std::map<char,std::vector<int>> updateLetterData (const std::list<std::string>& words) {
    
    // holds the occurences of each letter at each position
    std::map<char,std::vector<int>> occurences;

    // iterates through all remaining words
    for (std::string word : words) {
        
        // iterate through each letter
        for (short i = 0;i<WORD_LENGTH;i++) {

            // check if the letter is in the map yet
            if (occurences.find(word[i])==occurences.end()) {
                
                // insert the letter if not present
                std::vector<int> tempvec;
                for (short j = 0;j<WORD_LENGTH+1;j++) {
                    if (j==i||j==WORD_LENGTH) tempvec.push_back(1);
                    else tempvec.push_back(0);
                }
                occurences.insert(std::make_pair(word[i],tempvec));
            } 
            // if it is in the map, increment the positional and total counters
            else {
                occurences[word[i]][i]++;
                occurences[word[i]][WORD_LENGTH]++;
            }
        }
    }
    return occurences;
}

// prints the map of letter data
void printLetterData (const std::map<char,std::vector<int>>& characters) {

    // absolute formatting
    std::cout<<"Displaying letter occurences per position"<<std::endl<<std::endl;
    std::cout<<std::setw(8)<<"1st";

    // print one header for each position and a final position header
    for (int i = 1;i<WORD_LENGTH;i++) {
        
        // holds the suffix of the current label
        std::string temp = std::to_string(i+1);

        // assigns the currect suffix
        if (i%10>=3||(i%100>=10&&i%100<=13)) {
            // 11, 12, and 13 are suffixed with 'th' despite ending witha a 1
            temp+= "th";
        } else if (i%10==0) {
            temp += "st";
        } else if (i%10==1) {
            temp += "nd";
        } else if (i%10==2) {
            temp += "rd";
        }

        // prints the label
        std::cout<<std::setw(6)<<temp;
    }

    // display total label
    std::cout<<std::setw(6)<<"total"<<std::endl;
             
    // iterate through the map and display the frequencies
    for (auto itr : characters) {
        std::cout<<itr.first<<":";
        for (short i = 0;i<WORD_LENGTH+1;i++) {
            std::cout<<std::setw(6)<<itr.second[i];
        }
        std::cout<<std::endl;
    }
}

int main () {

    // parse the input file
    std::string wordsFile = "Dictionaries/word_list.txt";
    std::list<std::string>* words = parseDictionary(wordsFile);

    // function the user wants to call
    int selection = -1;

    // get a guess from the user
    std::pair<char,int>* guess;

    // holds the number of occurences for each letter
    std::map<char,std::vector<int>> occurences;

    // holds which position the correct letters have been found for
    std::vector<bool> foundLetters (WORD_LENGTH,false);

    // continue running as long as user keeps calling functions
    while (selection!=0) {

        // if the correct word is found
        if (getTrueCount(foundLetters)==WORD_LENGTH) {
            std::cout<<"You found the correct word!\n"<<
                       "The word was "<<*words->begin()<<std::endl;

            exit(EXIT_SUCCESS);
        }

        // add line break between iterations
        if (selection != -1) std::cout<<std::endl; 
        
        // get user function call
        selection = prompt();
        
        // call correct function
        if (selection == 0) {
            std::cout<<"Program Terminated"<<std::endl;
            exit(0);
        } else if (selection == 1) {

            // make a guess and update the word list
            guess = makeGuess(foundLetters);
            if (guess!=nullptr) updateWordList(*words,guess);

        } else if (selection == 2) {

            // print possible remaining words
            printWords(*words);

        } else if (selection == 3) {

            // print letter data
            occurences = updateLetterData(*words);
            if (occurences.size()) {
                printLetterData(occurences);
            } else {
                std::cout<<"There are no remaining possible words."<<std::endl;
            }

        } else if (selection == 4) {

            // if sixty percent of correct letters have been found
            if (getTrueCount(foundLetters)>=(WORD_LENGTH*0.6)) {
                std::cout<<"Because you have three correct letters,\n"<<
                           "I recommend that you look at the possible words\n"<<
                           "and select one that seems like a real word to you.\n"<<
                           "However, the algorithm thinks that\n";
            }

            // get suggested word
            occurences = updateLetterData(*words);
            std::string temp = getBestGuess(occurences,*words);
            if (temp!="-1") {
                std::cout<<temp<<" seems to be the best guess."<<std::endl;
            } else {
                std::cout<<"There are no remaining possible words."<<std::endl;
            }
        }
    }

    exit(EXIT_SUCCESS);
}
