// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool wordleSolve(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers,
    int n);

bool validWord(
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string word);

int getNumFloatInWord(
		const std::string& floating, 
		std::string word);

int getNumBlanks(const std::string& in);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<string> answers;

		if(floating.size() == 0){
			if(validWord(floating, dict, in)){
				answers.insert(in);
			}
		}

		wordleSolve(in, floating, dict, answers, 0);
    
    return answers;
}

// Define any helper functions here

bool wordleSolve(    
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers,
    int pos)
{
	if (pos == (int)in.length()){
		return true;
	} 
	std::string word = in;
	if (in[pos] == '-'){
		for (int i = 0; i < 26; i++){
			char change = i + 97;
				word[pos] = change;
				if (wordleSolve(word, floating, dict, answers, pos+1)){
					if (validWord(floating, dict, word)){
						answers.insert(word);
					} 
				}	
		}		
	}
	else {
		if (wordleSolve(word, floating, dict, answers, pos+1)) return true;
	}
	return false;
}

bool validWord(
    const std::string& floating,
    const std::set<std::string>& dict,
    std::string word
){
	int numFloat = floating.length(); //number of floating letters
	int numFloatInWord = getNumFloatInWord(floating, word); //number of floating letters in word

		if (dict.find(word) != dict.end() && numFloatInWord >= numFloat){
			return true;
		}
		else {
			return false;
		}
}

int getNumFloatInWord(
		const std::string& floating, 
		std::string word)
{
	int numFloatInWord = 0;
	for (int i = 0; i < (int)floating.length(); i++){
		for (int j = 0; j < (int)word.length(); j++){
			if (word[j] == floating[i]) {
				numFloatInWord++;
				word[j] = '-';
				j = (int)word.length(); 
			}
		}
	}
	return numFloatInWord;
}

int getNumBlanks(const std::string& in)
{
	int numBlanks = 0;
	for (int i = 0; i < (int)in.length(); i++){
		if (in[i] == '-'){
			numBlanks++;
		}
	}
	return numBlanks;
}
