#ifndef _H_DSSTRINGTOKENIZER
#define _H_DSSTRINGTOKENIZER
#include <iostream>
#include <vector>
#include "DSString.h"
using namespace std;

class DSStringTokenizer{
public:
    int sentiment;
    vector<DSString> tokenVec;

    // Accuracy Constructor
    DSStringTokenizer(int sent, DSString text) {
        sentiment = sent;
        tokenVec = Tokenization(text);
    }

    //Tokenizes stop words
    DSStringTokenizer(int sent, DSString text, vector<DSString> stpWrd) {
        sentiment = sent;
        tokenVec = Tokenization(text, stpWrd);
    }

    //Empty constructor
    vector<DSString>  Tokenization(DSString Tweet) {
        vector<DSString> empty;
        return Tokenization(Tweet, empty);
    }

    //Checking if the stop word exists or not.
    vector<DSString> Tokenization(DSString tweet, vector<DSString> stopwrd) {
        vector<DSString> tokenVec;
        int i;
        int j;
        i = tweet.find(' ');
        j = 0;
        bool flag = false;
        while (i != -1) {
            flag = false;
            // Reads the stopword
            DSString token(tweet.substring(j, i - j));
            // Goes through every stop word and checks if it exists
            for (int k = 0; k < stopwrd.size(); k++) {
                if (token == stopwrd[k]) {
                    flag = true;
                    break;
                }
            }
            //find the next stop word
            j = i + 1;
            i = tweet.find(' ', j);
            // Continue if true
            if (flag) {
                continue;
            }
            tokenVec.push_back(token);
        }
        return tokenVec;
    }
private:
};
#endif