#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <list>
#include <ctype.h>

// gets a guess from the user, used for testing
std::pair<char,int>* getGuess() {
    
    // holds the guesses input by the user
    std::pair<char,int>* guess_pairs = new std::pair<char,int>[5];
    
    // iterates 5 times, getting the letter and value for each letter of the guess
    for (int i = 0;i<5;i++) {

        // holds the current pair and its data
        std::pair<char,int> cur_pair;
        char cur_char;
        int cur_val;

        // gets the values from the user
        std::cin>>cur_char;
        std::cin>>cur_val;

        // make the current pair and append it to the array
        cur_pair.first=cur_char;
        cur_pair.second=cur_val;
        guess_pairs[i]=cur_pair;
    }
    return guess_pairs;
}

// guess is taken and stored as an array of pairs 
// first is the letter second is letter value
// 0-not in word
// 1-wrong location
// 2-correct location
std::pair<char,int>* makeGuess () {

    // holds the current 5 letter word guess
    std::string guess;
    // holds all of the letters and the data on its correctness
    std::pair<char,int>* data = new std::pair<char,int>[5];
    // holds the color of each letter
    std::string color;

    // promps user and stores guess
    std::cout<<"Enter Guess\n";
    std::cin>>guess;
    if (guess.length()!=5) {
        std::cerr<<"ERROR: invalid guess, length must be 5 not "<<guess.length()<<std::endl;
        return nullptr;
    }

    // gets data on each letter
    std::cout<<"What color was each letter?\n";
    for (short i = 0;i<5;i++) {

        // adds each letter to data
        data[i].first=guess[i];

        // gets the color for each letter
        std::cout<<guess[i]<<std::endl;
        std::cin>>color;
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (color=="green"||color == "g") {
            data[i].second=2;
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

// prompts the user for what action to take
int prompt () {
    std::cout<<"Would you like to:\n"<<
                "1. Make a guess\n"<<
                "2. See possible remaining words\n"<<
                "3. See letter data\n"<<
                "4. See suggested guess\n"<<
                "0. Exit the program"<<std::endl;
    int temp;
    std::cin>>temp;
    if (temp<0||temp>4) {
        std::cerr<<"ERROR: Invalid option, please select an option from 0 - 4\n";
        temp=prompt();
    }
    return temp;
}

// print out the remaining words
void getWords(const std::list<std::string> &words) {

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

// remove all words that dont meet the criteria of the guess
void updateWords (std::list<std::string> &oldWords, 
                    std::pair<char,int>* &guess) {
    // iterates through the list of words
    for (std::list<std::string>::iterator itr = oldWords.begin();itr!=oldWords.end(); ) {
        
        std::string word = *itr;
        
        // holds whether the word was deleted or not
        bool deleted = false;

        // iterates through all the letters of the guessed word
        for (unsigned short i = 0;i<5;i++) {
            
            // if the letter is not in the word, remove the word
            if (guess[i].second==0&&word.find(guess[i].first)!=std::string::npos) {
                    
                    // remove the word and set flag to true
                    itr = oldWords.erase(itr);
                    deleted = true;
                    break;
            } 

            // if the letter is in the wrong location
            // removes the word if the letter is in the word in the correct location
            // or it is not in the word at all
            else if (guess[i].second==1&&
                    (word.find(guess[i].first)==i ||
                    word.find(guess[i].first)==std::string::npos)) {
                    
                    // remove the word and set flag to true
                    itr = oldWords.erase(itr);
                    deleted = true;
                    break;
            }

            // if the letter is in the correct position
            else if (guess[i].second==2&&!(word.find(guess[i].first)==i)){
                
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

// initially gets the words from the input file 
std::list<std::string>* parseWordsFile (std::string inputFile) {
    
    std::ifstream istr (inputFile);

    // holds the words
    std::list<std::string>* words = new std::list<std::string>();

    // holds each word temporarily
    std::string temp;

    // iterate through the file of words
    while (istr>>temp) {
        words->push_back(temp);
    }

    return words;
}

// returns the best guess for the current word list 
// find the word with the closest to optimal letter in each position
std::string bestGuessByLetter(const std::list<std::string> &words) {

}

// returns a map of the frequencies of each letter at each position
// first 5 elements of the vector are the positions in the word, 
// last element is total occurences
std::map<char,std::vector<int>> getLetterData (const std::list<std::string>& words) {
    
    // holds the occurences of each letter at each position
    std::map<char,std::vector<int>> occurences;

    // iterates through all remaining words
    for (std::string word : words) {
        
        // iterate through each letter
        for (short i = 0;i<5;i++) {

            // check if the letter is in the map yet
            if (occurences.find(word[i])==occurences.end()) {
                
                // insert the letter if not present
                std::vector<int> tempvec;
                for (short j = 0;j<6;j++) {
                    if (j==i||j==5) tempvec.push_back(1);
                    else tempvec.push_back(0);
                }
                occurences.insert(std::make_pair(word[i],tempvec));
            } 
            // if it is in the map, increment the positional and total counters
            else {
                occurences[word[i]][i]++;
                occurences[word[i]][5]++;
            }
        }
    }
    return occurences;
}

// prints the map of letter data
void printLetterData (std::map<char,std::vector<int>>& characters) {

    // formatting
    std::cout<<"Displaying letter occurences per position"<<std::endl;
    std::cout<<std::setw(6)<<"1st"
             <<std::setw(6)<<"2nd"
             <<std::setw(6)<<"3rd"
             <<std::setw(6)<<"4th"
             <<std::setw(6)<<"5th"
             <<std::setw(6)<<"total"
             <<std::endl;
             
    // iterate through the map and display the frequencies
    for (auto itr : characters) {
        std::cout<<itr.first<<":";
        for (short i = 0;i<6;i++) {
            std::cout<<std::setw(6)<<itr.second[i];
        }
        std::cout<<std::endl;
    }
}

int main () {

    // parse the input file
    std::string wordsFile = "word_list.txt";
    std::list<std::string>* words = parseWordsFile(wordsFile);

    // function the user wants to call
    int selection = -1;

    // get a guess from the user
    std::pair<char,int>* guess;

    // holds the number of occurences for each letter
    std::map<char,std::vector<int>> occurences;

    // continue running as long as user keeps calling functions
    while (selection!=0) {

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
            guess = makeGuess();
            updateWords(*words,guess);

        } else if (selection == 2) {

            // print possible remaining words
            getWords(*words);

        } else if (selection == 3) {

            // print letter data
            occurences = getLetterData(*words);
            printLetterData(occurences);

        } else if (selection == 4) {
            
            // get suggested word

        }
    }

    



    
    

    

    

    

    

    /*// iterate through each letter of each word
    for (short i = 0;i<5;i++) {
            // check if the letter is in the map
            if (characters.find(temp[i])==characters.end()) {
                // create a vector for the letter if it is not in the map yet
                std::vector<int> tempvec;
                for (short j = 0;j<6;j++) {
                    if (j==i||j==5) tempvec.push_back(1);
                    else tempvec.push_back(0);
                }
                characters.insert(std::make_pair(temp[i],tempvec));
            // if the letter is already in the map, increment the end value and positional values
            } else {
                characters[temp[i]][i]++;
                characters[temp[i]][5]++;
            }
        }*/

    // write the collected data to the output file
    

}