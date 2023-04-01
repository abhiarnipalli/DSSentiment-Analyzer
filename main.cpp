#include <iostream>
#include "dictionary.h"
using namespace std;

int main(int argc, char* argv[]){

    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;
    cout << argv[4] << endl;
    Dictionary userDictionary;
    userDictionary.doAllTheTrainingHere(argv[1]);// function to train
    userDictionary.doAllTheTestingHere(//function to test
        argv[2],
        argv[3],
        argv[4],
        argv[5]
    );
}