#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void printHelp(char* scriptName){
    cout << "Usage:" << endl;
    cout << "   " << scriptName << " FILENAME" << endl;
    exit(1);
}

// --------------- Recursive mergesort

void merge(vector<string>& fileContent,int first,int median,int last){
    
    vector<string> lowerBuffer;
    vector<string> upperBuffer;
    
    for (int i = first; i <= median; i++) {
        lowerBuffer.push_back(fileContent.at(i));
    }
    for (int i = median+1; i < last; i++) {
        upperBuffer.push_back(fileContent.at(i));
    }
    
    int i = 0;
    while ( !(lowerBuffer.empty() || upperBuffer.empty()) ) {
        if ( lowerBuffer.front() <= upperBuffer.front() ) {
            fileContent.at(i) = lowerBuffer.front();
            lowerBuffer.erase(lowerBuffer.begin()+0);
        }
        else{
            fileContent.at(i) = upperBuffer.front();
            upperBuffer.erase(upperBuffer.begin()+0);
        }
    }
    
}

void mergeSort(vector<string>& fileContent,int first,int last) {
    
    int median = (first+last)/2;
    
    if ( first < last ) {
        mergeSort(fileContent,first,median);
        mergeSort(fileContent,median+1,last);
        merge(fileContent,first,median,last);
    }
}

// --------------- Recursive mergesort

int main(int argc, char* argv[]) {
    
    vector<string> argVector;
    string filePath;
    vector<string> fileContent;
    char* scriptName = argv[0];
    
    // ---------------- Input handling
    // Read args to vector
    for (int i = 1; i < argc; i++) {
        argVector.push_back(static_cast<string>(argv[i]));
    }
    
    // Check if user needs help or has given incorrect ammount of arguments
    if (argc != 2) {
        printHelp(scriptName);
    }
    
    for (int i = 0; i < argVector.size(); i++) {
        if ( argVector.at(i) == "-h" || argVector.at(i) == "--help" ) {
            argVector.erase(argVector.begin()+i);
            printHelp(scriptName);
        }
    }
    
    // Remaining arg is a filepath, read the contents.
    filePath = argVector[0];
    ifstream readStream(filePath.c_str());
    string line;
    
    if ( readStream.is_open() ) {
        while ( getline(readStream,line) ) {
            fileContent.push_back(line);
        }
    }
    
    // --------------------------
    
    mergeSort(fileContent,0,fileContent.size()-1);
    
    for (int i = 0; i < fileContent.size(); i++) {
        cout << fileContent.at(i) << endl;
    }
    
    
    return 0;
}
