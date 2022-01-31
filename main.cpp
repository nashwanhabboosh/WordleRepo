#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include<iomanip>

int main () {

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

    std::cout<<"show isaac how pull requests work";
}