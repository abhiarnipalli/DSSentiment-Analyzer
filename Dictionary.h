#ifndef _H_DICTIONARY
#define _H_DICTIONARY
#include <iostream>
#include "DSString.h"
#include "DSTokenize.h"
#include "DSVector.h"
using namespace std;

class Tweet2{
public:
    int sentiment;
    DSString ID;
    DSString date;
    DSString query;
    DSString user;
    DSString text;
    Tweet2(){
        sentiment = 0;
        text = "";
    };
    Tweet2(int sent, DSString tweet) {
        sentiment = sent;
        text = tweet;
    };
    Tweet2(DSString ID, int sent){
        (*this).ID = ID;
        sentiment = sent;
    }

    Tweet2(DSString ID, DSString date, DSString query, DSString user, int sent, DSString tweet) {
        (*this).ID = ID;
        (*this).date = date;
        (*this).query = query;
        (*this).user = user;
        sentiment = sent;
        text = tweet;
    };
};

class TokenScore {
public:
    TokenScore() = default;
    //Token Score Constructor
    TokenScore(DSString tk, int s) {
        token = tk;
        score = s;
    }
    DSString token;
    int score;
};


class Dictionary {
public:
    //Optimal Bias
    float bias = 100;
    int rarity_threshold = 0;
    DSVector<TokenScore> tsVec;
    DSVector<TokenScore> tsVecCounting;

    //Training data function
    void doAllTheTrainingHere(char*);
    //Testing data function
    void doAllTheTestingHere(char*, char*, char*, char*);
    //Update dictionary function
    void update2(DSStringTokenizer);
    //Predict with threshold
    int predict(DSStringTokenizer DS, int rarity_threshold);
    //Load values
    int predict(DSStringTokenizer);
    double evaluatePrediction(DSVector<Tweet2>, float, int);
};

#endif