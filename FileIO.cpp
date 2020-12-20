# include <iostream>
# include "FileIO.h"
# include <fstream>


using namespace std;

// default constructor
FileIO::FileIO(){
    fileName = "";
    sumLine = 0;
    currLine = 0;
}

// overloaded constructor
FileIO::FileIO(string name){
    fileName = name;
    sumLine = 0;
    currLine = 0;
    check();
    // cout << getSumLines() << endl;
}

FileIO::~FileIO(){

}

// set file name
void FileIO::setName(string name){
    fileName = name;
    check();
}

// check if file is valid, if not then prompt user until valid.
void FileIO::check(){
    ifstream file;
    file.open(fileName);
    while(file.fail()){
        cout << "file could not be found. Enter file name(xxx.txt): " << endl;
        cin >> fileName;
        file.open(fileName);
    }
    file.close();
}

// get total lines
int FileIO::getSumLines(){
    string temp = "";

    ifstream file(fileName);

    while(getline(file, temp)){
        ++sumLine;
    }

    return sumLine;
}

// get double value from individual lines
double FileIO::getLine(){
    ifstream file(fileName);

    string inD = "";
    double outD = 0.0;

    int marker = 0;

    while(getline(file, inD)){
        if(marker == currLine){
            outD = stod(inD);
            ++currLine;
            break;
        }
        else {
            ++marker;
        }
    }

    return outD;
}
