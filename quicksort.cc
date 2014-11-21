#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void printHelp(char* execName){
    cout << "Usage:" << endl;
    cout << "   " << execName << " FILENAME" << endl;
    exit(1);
}

// ---------------


int partition(vector<string>& fileContent, int lower, int upper){
    
    int pivot = upper; // Choose upper as pivot element
    int firstHigh = lower; // This is where pivot should be when run is finished
    
    for (int i = lower; i < upper; i++) {
        if ( fileContent.at(i) <= fileContent.at(pivot) ) { // If content is smaller than pivot, move it to the left
            swap(fileContent.at(i),fileContent.at(firstHigh++));
        }
    }
    
    swap(fileContent.at(pivot),fileContent.at(firstHigh)); // When checked all objets against pivot, place pivot in the right place
    
    return firstHigh; // Return position to the divider so we can work on smaller arrays.
    
}

void quickSort(vector<string>& fileContent, int lower, int upper){
    
    int pivot;  // Position of pivot element
    
    if (upper > lower) {
        pivot = partition(fileContent, lower, upper);
        quickSort(fileContent,lower,pivot-1);
        quickSort(fileContent,pivot+1,upper);
    }
}

// ---------------

int main(int argc, char* argv[]){
    
    vector<string> argVector;
    string filePath;
    vector<string> fileContent;
    char* execName = argv[0];
    
    // ---------------- Input handling
    // Read args to vector
    for (int i = 1; i < argc; i++) {
        argVector.push_back(static_cast<string>(argv[i]));
    }
    
    // Check if user needs help or has given incorrect ammount of arguments
    if (argc != 2) {
        printHelp(execName);
    }
    
    for (int i = 0; i < argVector.size(); i++) {
        if ( argVector.at(i) == "-h" || argVector.at(i) == "--help" ) {
            argVector.erase(argVector.begin()+i);
            printHelp(execName);
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
    
    quickSort(fileContent, 0, fileContent.size()-1);
    
    for (int i = 0; i < fileContent.size(); i++) {
        cout << fileContent.at(i) << endl;
    }
    
    
    return 0;
}
