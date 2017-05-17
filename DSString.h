//Wesley Ellington
//CSE 2341, Fall 2016
#ifndef DSSTRING
#define DSSTRING

#include "vector.h"
#include "linkedlist.h"
#include <iostream>
#include <cstring>

#define DEBUG false
#define VERBOSE false

class DSString{

    private:
        //length of occupied spaces in string
        int length;


    public:
        //char values held in array
        char * strVal;

        //defualt constructor
        DSString();
        //copy constructor for char*, mainly reading literals
        DSString(const char* inChars);
        //copy constructor for DSString type
        DSString(const DSString& inString);
        DSString(const int inInt);

        //assignment operator for char *
        DSString& operator= (const char* inChars);
        //assignment for DSString
        DSString& operator= (const DSString& inString);
        //concatondation operator
        DSString operator+ (const DSString& inString);

        //equality for char *
        bool operator== (const char* inChars);
        //equality for DSString type
        bool operator== (const DSString& inString);
        //inequality
        bool operator != (const DSString& inString);

        bool operator> (const DSString& inString);
        bool operator< (const DSString& inString);

        char& operator[] (const int index);

        //returns string size
        int size();
        //returns substring as string
        DSString substring(int start, int end );
        //converts to c string
        char* c_str();

        //cuts punctuation off of front and back of word
        DSString cleanPunct();

        //stream insertion
        friend std::ostream& operator<< (std::ostream& outStream, const DSString& inString);

        //Destructor
        ~DSString();

        // new lowercase string
        DSString & lower();
        // new uppercase string
        DSString & upper();

        //returns array of indexes of char locations
        int * find(char delimiter);

        //checks exsistance of char in string
        bool contains(char delimiter);

        //splits based on provided char
        DSString * split(const DSString & inString, char delimiter);
        // splits based on space
        DSString * split(const DSString & inString);

        //splits string by delimiter and places in destination array
        void split(DSVector<DSString> & destVec, char delimeter);


        //LEE

        void toLower();
        friend std::istream& operator>> (std::istream& inStream, const DSString& outString);
        bool isPunct(char inChar);
        void vmSplit(DSVector<DSString> &splitVector);
        bool isQuote(char inChar);
        bool isArticle(DSString inStr);
        bool functionCutter(char inChar);

};
#endif
