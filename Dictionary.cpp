#include <fstream>
#include <iostream>
#include "DSString.h"
#include "DSVector.h"
#include "Dictionary.h"
#include <iomanip>

using namespace std;

int buffer_size = 500;
Tweet2 dataRead(ifstream& file, bool test = false) {
    int sentiment = 0;
    char* buffer = new char[buffer_size];

    if (!test) {
        file.getline(buffer, buffer_size, ',');
        sentiment = buffer[0] - '0';
    }

    file.getline(buffer, buffer_size, ','); //ID
    DSString ID(buffer);
    file.getline(buffer, buffer_size, ','); //Date
    DSString date(buffer);
    file.getline(buffer, buffer_size, ','); //Query
    DSString query(buffer);
    file.getline(buffer, buffer_size, ','); //User
    DSString user(buffer);
    file.getline(buffer, buffer_size); //Tweet
    DSString tweet(buffer);

    delete[] buffer;//Delete buffer after allocating

    //Tweet2 tweetObj(sentiment, tweet);
    Tweet2 tweetObj(ID, date, query, user, sentiment, tweet);  // passing into tweet constructor
    return tweetObj;

}

Tweet2 dataReadTest(istream& file) {// Read in the sentiment and ID for testing

    char* buffer = new char[buffer_size];//Create buffer to read data
    int sentiment = 0;

    file.getline(buffer, buffer_size, ','); // Reads in the sentiment
    sentiment = buffer[0] - '0'; // converts the ASCHI number stored in buffer and converts into int
    file.getline(buffer, buffer_size); // Reads in the ID
    DSString ID(buffer); // Set ID to contents in buffer
    delete[] buffer; //delete dynamically allocated
    Tweet2 tweetObj(ID, sentiment); //Constructing the tweetObj
    return tweetObj;//return ID and Sentiment
}


void Dictionary::doAllTheTestingHere(  //testing the data
        char* test_filename,
        char* test_sentiment_filename,
        char* prediction_output,
        char* accuracy_output
)
{
    DSVector<Tweet2> predictObj; //creates vector to store tweets
    ifstream file2, file3; //Declaraiton of ifstream to open files
    ofstream file4, file5;
    char* buffer = new char[buffer_size];
    file2.open(test_filename); // Test
    file3.open(test_sentiment_filename); //Opens test_sentiment_filename
    file4.open(prediction_output); // file open to output prediction
    file5.open(accuracy_output); //file open to output accuracy

    file2.getline(buffer, buffer_size); //header test of the data to parse
    DSString parse2(buffer); //Store buffer in parse2

    file3.getline(buffer, buffer_size); //header of test_sentiment to parse
    DSString parse3(buffer); //Store buffer in parse3

    file5 << "0.000" << endl; //output a accuracy to be then overwritten until the accuracy is calcualated


    while (!file2.eof()) { //runs till end of file
        try {
            Tweet2 test = dataRead(file2, true); //Calls data read for test, and sets bool to true
            Tweet2 test_sentiment = dataReadTest(file3);  //Calls data read for test_sentiment
            test.sentiment = test_sentiment.sentiment; //store values read from test_sentiment into test
            predictObj.push_back(test); // push_back what value into vector
            /*file4 << t.ID << ","
                << t.date << ","
                << t.query << ","
                << t.user << ","
                << t.text << endl;*/
            file4 << test.ID << ","
                  << test_sentiment.sentiment << endl;
            file5 << test_sentiment.sentiment << ","
                  << test.sentiment << ","
                  << test.ID << endl;
        }
        catch (const std::exception& ex) {
            cout << ex.what() << endl;
        }
    }
    file4.close();
    double acc = evaluatePrediction(predictObj, bias, rarity_threshold); //evaluates using a bias and threshold that will run and output accuracy
    file5.seekp(0); // will rewrite the inital percentage given above
    file5 << setprecision(3) << acc; //Sets it to 3 decimal places
    file5.close();  //close file

    delete[] buffer;
}

void Dictionary::doAllTheTrainingHere(char* train_filename) // fucntion for training the using training set
{
    char* buffer = new char[buffer_size];
    cout << "initializing" << endl;
    ifstream file;
    ifstream stopFile;
    //file.open("data/train_dataset_20k.csv");
    file.open(train_filename);

    const char* stopWordsFile = "t101_minimal.txt"; // file text that has a list of stop words that are correctly aligned
    stopFile.open(stopWordsFile);
    //Prints to terminal
    cout << "Bias: " << bias << endl; // prints out bias
    cout << "Rarity threshold: " << rarity_threshold << endl; //threshold
    cout << "Stopwords file: " << stopWordsFile << endl; //StopWords file
    vector<DSString> stopWrd; //vector for stop words

    while (stopFile.getline(buffer, buffer_size)) { //gets first line of stop word file, and stores it in buffer
        DSString word(buffer);  //stores the buffer in DSString word
        stopWrd.push_back(word); //stores the stop word into the vector
    }
    stopFile.close(); //closes the stop file
    file.getline(buffer, buffer_size); //Gets the head
    DSString parse(buffer); // parses the header

    int counter = 1; // counter is set to 1 then later incremented
    int log = 1000; // used to check if all tweets have been read
    while (!file.eof()) {
        try {
            Tweet2 t = dataRead(file); //creates object for retrieving the values from data read
            DSStringTokenizer DS(t.sentiment, t.text, stopWrd); //tokenizes
            update2(DS);
            if (counter % log == 0) //calculates a number divisible by 1000 to print counter for the number of tweets
            {
                cout << counter << " tweets used for training." << endl;
            }
            counter++;
        }
        catch (const std::exception& ex) {
            cout << ex.what() << endl;
        }
    }
    cout << "All tweets used for training." << endl;  //indicates when all data has been read for training
    delete[] buffer;
}

int Dictionary::predict(DSStringTokenizer DS) {
    return predict(DS, 0); // will run predict with the a threshold of 0
}

int Dictionary::predict(DSStringTokenizer DS, int rarity_threshold) { //calculates and returns total score
    int scoreTotal = 0;  //setting score total initially to 0

    for (int k = 0; k < DS.tokenVec.size(); ++k) {
        for (int j = 0; j < tsVec.size(); ++j) {
            if (DS.tokenVec[k] == tsVec[j].token) {
                if (tsVecCounting[j].score > rarity_threshold) // Ignoring too rare tokens
                    //scoreTotal += tsVec[j].score / tsVecCounting[j].score;
                    scoreTotal += tsVec[j].score; //adds score total if the token is greater than threshold
            }
        }
    }
    return scoreTotal;
}


double Dictionary::evaluatePrediction(DSVector<Tweet2> predictObj, float bias, int rarity_threshold) { //Calculating the accuracy(percentage), using bias, and threshold
    cout << "Starting to make predictions" << endl;
    float total;
    int sentiment;
    int counter = 0;
    double percentage;
    int TP = 0; //counter for correctly predicted postive tweets
    int FP = 0; //counter for incorrectly predicted postive tweets
    int TN = 0;//counter for correctly predicted negative tweet
    int FN = 0; //counter for incorrectly predicted false tweets

    int progress = 1; //counter for checking progress of counting tweet
    int log = 1000; //value used to print out progress
    for (const auto& t : predictObj) {
        DSStringTokenizer DS(t.sentiment, t.text); //Takes sentiment and text that is read
        total = predict(DS, rarity_threshold) + bias; //calculates the score total using bias and threshold
        if (total > 0) { //if the value of total score is bigger than 0  than it is a postive tweet and assigned with sentiment of 4
            sentiment = 4;
        }
        else {
            sentiment = 0;
        }
        if (sentiment == t.sentiment) { // if the sentiment is preducted correctly
            counter++;
            if (sentiment == 4) TP++; else TN++; // increases true positve counter if sentiment is 4, if not will increase true negative coutner
        }
        else
        {
            if (sentiment == 4) FP++; else FN++; //else increases false postive counter if equal to 4, if not increases false negative counter
        }



        if (progress % log == 0) //if the counter for prgress divisible by 1000 then output the value of tweets evaluated
        {
            std::cout << progress << " tweets evaluated" << endl;
        }
        progress++;
    }
    //percentage = ((double)counter / (predictObj.size()) * 100);
    percentage = ((double)counter / (predictObj.size()));
    std::cout << percentage << endl;
    std::cout << "TP: " << TP << " TN: " << TN << " FP: " << FP << " FN: " << FN << endl;
    return percentage;
}

void Dictionary::update2(DSStringTokenizer DS) {
    //DS contains vector of strings, sentiments
    // For each token in the DS, find token score
    // Make sure if found or not the token
    //If you find the token, depending on the sentiment increase or decreases the current score
    // If this token doens texist in the token score, then create it using the score 1 or -1

    DSString token;
    int sentiment;
    sentiment = DS.sentiment;

    for (int i = 0; i < DS.tokenVec.size(); ++i) {
        token = DS.tokenVec[i]; //Retreiving token from data
        bool found = false;
        for (int j = 0; j < tsVec.size(); j++) {

            if (tsVec[j].token == DS.tokenVec[i]) {
                found = true;
                if (sentiment == 0) { //if sentiment is negative decrement the score stored in tsVec
                    tsVec[j].score--;
                }
                else if (sentiment == 4) { // if sentiment is positive increment score
                    tsVec[j].score++;
                }
                tsVecCounting[j].score++; //increment the counter of the word
            }
        }
        if (!found) { // if the token isn't found, add to dictionary
            if (sentiment == 0) { // if the sentiment is negative add to token score list
                TokenScore a(DS.tokenVec[i], -1);
                tsVec.push_back(a);
            }
            else if (sentiment == 4) { // If sentiment is positive add to positive token score list
                TokenScore b(DS.tokenVec[i], +1);
                tsVec.push_back(b);
            }
            TokenScore c(DS.tokenVec[i], +1);
            tsVecCounting.push_back(c); //Add the token tsVecCounting
        }
    }
}