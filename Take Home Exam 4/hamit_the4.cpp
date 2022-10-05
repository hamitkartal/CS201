#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
using namespace std;



string decisionMaker (ifstream& file, const string& word){
    file.clear();
    file.seekg(0);
    string line, poolWord;
    double max = double(word.length())/2;
    int compatibility;
    while (getline(file, line)){
        istringstream file(line);
        while (file >> poolWord){
            ToLower(poolWord);
            
            if (poolWord == word){
                return word;
            }
            else if (poolWord.length() == word.length()){
                compatibility = 0;
                for (int i=0; i < word.length(); i++){
                    if (word.at(i) == poolWord.at(i)){
                        compatibility++;
                    }
                }
                if (compatibility > max){
                    max = compatibility;
                }
            }
        }
    } 
    file.clear();
    file.seekg(0);
    string ret = "";
    int count = 0;
    while (getline(file, line)){
        istringstream file(line);
        while (file >> poolWord){
            ToLower(poolWord);
            if (poolWord.length() == word.length()){
                compatibility = 0;
                for (int i=0; i < word.length(); i++){
                    if (word.at(i) == poolWord.at(i)){
                        compatibility++;
                    }
                }
                if (compatibility == max){
                    ret += "," + poolWord;
                    count++;
                }
            }
        }
    }
    
    if (count == 0){
        return "{" + word + "}";
    }
    else if (count == 1){
        return ret.substr(1);
    }
    else{
        return "(" + ret.substr(1) + ")";
    }
}

int main (){
    string poolFilename, mainFilename;
    cout << "Please enter a filename for the word pool: ";
    cin >> poolFilename;

    ifstream poolinput;
    poolinput.open (poolFilename.c_str ());
    while (poolinput.fail ()){
        cout << "Cannot open the word pool file." << endl << "Please enter a filename for the word pool: ";
        cin >> poolFilename;
        poolinput.open (poolFilename.c_str ());
    }

    cout << "Please enter a filename for the main text: ";
    cin >> mainFilename;
    ifstream maininput;
    maininput.open (mainFilename.c_str ());
    while (maininput.fail()){
        cout << "Cannot open the main text file." << endl << "Please enter a filename for the main text: ";
        cin >> mainFilename;
        maininput.open (mainFilename.c_str ());
    }

    string line1, word1, output;
    while (getline (maininput, line1)){
        istringstream maininput (line1);
        while (maininput >> word1){
            ToLower(word1);
	        output += decisionMaker(poolinput, word1) + " ";
	    }
        if (output.at (output.length () - 1) == ' '){
	        output.at (output.length () - 1) = '\n';
	    }
        else{
	        output += '\n';
        }
    }
    cout << "You may find the results below:" << endl << endl << output;
    maininput.close ();
    poolinput.close ();

    return 0;
}
