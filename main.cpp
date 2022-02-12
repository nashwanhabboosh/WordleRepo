#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>

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
        data[i].first=color[i];

        // gets the color for each letter
        std::cout<<guess[i]<<std::endl;
        std::cin>>color;
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (color=="green") {
            data[i].second=2;
        } else if (color == "yellow") {
            data[i].second=1;
        } else if (color == "black") {
            data[i].second=0;
        } else {
            std::cout<<"Invalid color, please type \"green\", \"yellow\" or \"black\"\n";
        }
    }
    return data;
}

int main () {

    makeGuess();

    std::ifstream istr ("word_list.txt");
    std::string temp;
    std::map<char,std::vector<int>> characters;

    // iterate through the file of words
    while (istr>>temp) {
        // iterate through each letter of each word
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
        }
    }

    // write the collected data to the output file
    for (auto itr : characters) {
        std::cout<<itr.first<<":";
        for (short i = 0;i<6;i++) {
            std::cout<<std::setw(6)<<itr.second[i];
        }
        std::cout<<std::endl;
    }

}