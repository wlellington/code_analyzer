#include "directoryiterator.h"
#define VERBOSE false

//base constructor

directoryIterator::directoryIterator(){
    fileNames.append("VOID");
}

//constructor with dir name

directoryIterator::directoryIterator(char* dirName){
    std::cout << "Creating Directory Iterator" << std::endl;
    iterateDirectory(dirName);
}

//check if the file type is of certain type (c/c++ extensions)
bool directoryIterator::extensionCheck(dirent* entry)
{
    string fileName = entry->d_name;
    if(fileName.length() <= 4){
        fileName = "@@@" + fileName;
    }

    if(fileName.substr(fileName.length()-4, fileName.length()) == ".cpp")
        return true;

    else if(fileName.substr(fileName.length()-4, fileName.length()) == ".hpp")
        return true;

    else if(fileName.substr(fileName.length()-2, fileName.length()) == ".h")
        return true;

    else if(fileName.substr(fileName.length()-2, fileName.length()) == ".c")
        return true;

    else
        return false;
}

//Utility function for iterator.
void directoryIterator::dirVisit(dirent* entry, char* pPath)
{
    char actualPath[PATH_MAX+1];
    char* correctPath;

    if (VERBOSE) cout<<"File Name: "<< entry->d_name <<endl;

    correctPath = realpath(pPath, actualPath);
    //buffer string for reading in the opened file
    DSString buffer = correctPath;
    //append the file name to the path
    buffer  =  buffer + DSString("/");
    buffer = buffer + DSString(entry->d_name);
    if (VERBOSE) cout<<"File Path: "<< buffer <<endl;


    //open each file in the directory
    ifstream fin(buffer.c_str());

    //Get sample from a file
    if(fin.is_open())
    {
        if(VERBOSE){
            cout<<"FILE OPENED"<<endl;
            cout<<endl;
        }

    }
    else
    {
        cout<<"FILE FAILED TO OPEN: " << buffer.c_str() <<endl;
    }

    fin.close();

    //save filename to vector
    fileNames.append(buffer);

}

//File iterator using dirent.h
void directoryIterator::iterateDirectory(char* filePath)
{
    //create a DIR*, the pointer to directory
    DIR* dirPtr = nullptr;

    //struct dirent* for readdir()
    dirent* dirEntry = nullptr;

    char actualPath[PATH_MAX+1];
    char* correctPath;

    //open directory from input (command line argument)
    dirPtr = opendir(filePath);

    //check if the directory was open correctly.
    if(dirPtr == nullptr)
    {
        cout<<"The directory was not opened correctly. Please check the directory name: " << filePath <<endl;
        exit(1);
    }

    if(VERBOSE){
        cout<<"DIR OPENED"<<endl;
        cout<<endl;
    }

    //read directory
    while((dirEntry = readdir(dirPtr)))
    {
        //if the entry is another directory
        if(dirEntry->d_type == DT_DIR)
        {
            //make sure the directory is not itself or parent directory
            if((strcmp(dirEntry->d_name, ".") != 0) && (strcmp(dirEntry->d_name, "..") != 0))
            {
                if(VERBOSE) cout<<"Directory Name: "<<dirEntry->d_name<<endl;
                //recursively go down to the subdirectory
                correctPath = realpath(filePath, actualPath);
                //store the path in a string for appending
                DSString temp = correctPath;
                //add the next directory name
                temp = temp + DSString("/");
                temp = temp + DSString(dirEntry->d_name);
                //turn string.c_str() into char*
                const char* cc = temp.c_str();
                char* c = (char*) cc;
                if(VERBOSE) cout<<"Directory Path: "<<temp<<endl;
                iterateDirectory(c);
            }
        }

        //if the entry is regular file
        else if(dirEntry->d_type == DT_REG)
        {
            //and the file is c/c++ file
            if(extensionCheck(dirEntry) == true)
            {
                //perform visit
                dirVisit(dirEntry, filePath);
            }
        }
    }

    //close the directory when all are read.
    closedir(dirPtr);
}
