#ifndef DIRECTORYITERATOR_H
#define DIRECTORYITERATOR_H

//#include "vector.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include "DSString.h"


using namespace std;

class directoryIterator{
public:

    //vector containing all filename in dir and subdir
    DSVector<DSString> fileNames;

    //base constructor, does not take argument
    directoryIterator();

    //takes directory name as arg, will populate fileNames
    directoryIterator(char* dirName);

    //EXPERIMENTAL FUNCTION
    //functor visit fucntionality
    void functorVisit();

private:

    void iterateDirectory(char*);
    void dirVisit(dirent*, char*);
    bool extensionCheck(dirent*);

};



#endif // DIRECTORYITERATOR_H

