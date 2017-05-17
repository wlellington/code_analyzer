//Wesley Elington
//CSE 2341
//Sprint 02

#include "DSString.h"
#include "vector.h"

//defualt constructor
DSString::DSString(){
    if (VERBOSE) std::cout << "DSString default constructor called" << std::endl;
    length = 0;
    strVal = nullptr;
    if (DEBUG) std::cout << "Default string!" <<std::endl;
}

//copy constructor for char*, mainly reading literals
DSString::DSString(const char* inChars){
    if (VERBOSE) std::cout << "DSString char* constuctor called" << std::endl;

    //assign member vars
    length = std::strlen(inChars);

    //allocate space for C string, allow space for terminator
    strVal = new char [length + 1];

    strcpy(strVal, inChars);

    //appends terminator
    strVal[length] = '\0';

}

//copy constructor for DSString type
DSString::DSString(const DSString& inString){
    if (VERBOSE) std::cout << "DSString copy constructor called" << std::endl;

    //allocate new array
    this->strVal = new char [inString.length + 1];

    //copy data members
    this->length = inString.length;

    strcpy(this->strVal, inString.strVal);

}

//create string of int
DSString::DSString(const int inInt){
    if (VERBOSE) std::cout << "DSString integer cast called" << std::endl;

    this->strVal = new char [20];
    this->length = sprintf(this->strVal, "%d", inInt);

}

//assignment operator for char *
DSString& DSString::operator= (const char* inChars){
    if (VERBOSE) std::cout << "DSString assignment operator for char * called" << std::endl;

    //assign member vars
    this->length = strlen(inChars);

    delete[] this->strVal;

    //allocate space for C string, allow space for terminator
    this->strVal = new char [length + 1];
    strcpy(this->strVal, inChars);

    //appends terminator
    this->strVal[length] = '\0';
    return *this;

}

//assignment for DSString
DSString& DSString::operator= (const DSString& inString){
    if (VERBOSE) std::cout << "DSString assignment operator for DSString called" << std::endl;
    if(this != &inString){
        //clear old array
        if(strVal){
            delete[] this->strVal;
        }
        //allocate new array
        this->strVal = new char [inString.length + 1];
        this->length = inString.length;

        //copy data members
        if (this != nullptr && inString.strVal != nullptr){
            strcpy(this->strVal, inString.strVal);
        }
    }
    return *this;


}

//concatonation operator
DSString DSString::operator+ (const DSString& inString){
    if (VERBOSE) std::cout << "DSString concatonation operator called" << std::endl;
    int newLen = this->length + inString.length + 1;
    DSString newString;
    newString.strVal = new char[newLen];
    strcpy(newString.strVal, this->strVal);
    strcat(newString.strVal, inString.strVal);
    newString.length = newLen -1;
    return newString;
}

//equality for char *
bool DSString::operator== (const char* inChars){
    if (VERBOSE) std::cout << "DSString equality for char* called" << std::endl;
    if(strcmp(inChars, this->strVal) == 0){
       return true;
   }

   else{
       return false;
   }
}

//equality for DSString type
bool DSString::operator == (const DSString& inString){
    if (VERBOSE) std::cout << "DSString equality for DSString called" << std::endl;
    if(strcmp(inString.strVal, this->strVal) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool DSString::operator> (const DSString& inString){
    if (VERBOSE) std::cout << "DSString greater than operator called" << std::endl;

    if (this->length == 0)
        return false;
    if (std::strcmp(this->strVal, inString.strVal) > 0)
        return true;

    return false;
}

bool DSString::operator< (const DSString& inString){
    if (VERBOSE) std::cout << "DSString less than operator called" << std::endl;

    if (this->length == 0)
        return true;
    if (std::strcmp(this->strVal, inString.strVal) < 0)
        return true;

    return false;
}

//get value at index array
char& DSString::operator[] (const int index){
    if (VERBOSE) std::cout << "DSString subscript operator called" << std::endl;

    char * charPtr;
    if(index >=0){
        charPtr = &(this->strVal[index]);
    }

    else{
        charPtr = &(this->strVal[this->length + index]);
    }
    return *charPtr;
}

//create substring using int indexes
DSString DSString::substring(int start, int end ){
    if (VERBOSE) std::cout << "DSString substring called" << std::endl;

    char * newStr;
    DSString substring;
    if(end < 0 && start < 0){


        start = strlen(this->strVal) + start + 1 ;
        end = strlen(this->strVal) + end  ;
        newStr = new char[(end - start) + 2];

        for(unsigned i = 0; i < strlen(newStr) + 2; i++){
            //assign substring
            newStr[i] = this->strVal[start + i];
        }
        newStr[strlen(newStr)] = '\0';
    }

    else if (end < 0 && start >= 0){

        end = strlen(this->strVal) + end;
        newStr = new char[end - start];

        for(int i = 0; i < (end - start + 1); i++){
            //assign substring
            newStr[i] = this->strVal[start + i];
        }
        newStr[end - start + 1] = '\0';
    }

    else{
        //create new char * of length of substring + 1
        newStr  = new char [(end - start) + 1];

        for(int i = 0; i < end - start; i++){
            //assign substring
            newStr[i] = this->strVal[start + i];
        }

        newStr[end - start] = '\0';
    }


    if (DEBUG) std::cout << newStr <<std::endl;

    //assign to string
    substring = DSString(newStr);

    //free tmp
    delete[] newStr;

    if (DEBUG) std::cout << "Substring returned: "<< substring <<std::endl;
    return substring;
}

 //returns length of full array
int DSString::size(){
    if (VERBOSE) std::cout << "DSString size called" << std::endl;

    return this->length;

}

//stream insertion
std::ostream& operator<< (std::ostream& outStream, const DSString& inString){
    if (VERBOSE) std::cout << "DSString stream insertion operator called" << std::endl;

    if(inString.length > 0){
        outStream << inString.strVal;
    }
    else{
        outStream << "Empty String!";
    }
    return outStream;
}

//returns pointer to strVal
char* DSString::c_str(){
    char * c_ptr;
    c_ptr = (this->strVal);
    return c_ptr;
}

//Destructor
DSString::~DSString(){
    if (VERBOSE) std::cout << "DSString destructor called" << std::endl;

    //free array
    delete[] this->strVal;

    if (DEBUG) std::cout << *this <<std::endl;
}

// new lowercase string
DSString & DSString::lower(){
    if (VERBOSE) std::cout << "DSString lower called" << std::endl;

    char * newStr = new char[this->length + 1];
    for(int i = 0; i < this->length ; i ++){
        //move all values to lowercase
        newStr[i] = tolower(this->strVal[i]);
    }
    //terminate
    newStr[this->length] = '\0';
    strcpy(this->strVal, newStr);
    delete[] newStr;
    return * this;
}

// new uppercase string
DSString & DSString::upper(){
    if (VERBOSE) std::cout << "DSString upper called" << std::endl;

    char * newStr = new char[this->length + 1];
    for(int i = 0; i < this->length ; i ++){
        //move all values to uppercase
        newStr[i] = toupper(this->strVal[i]);
    }

    //terminaate
    newStr[this->length] = '\0';
    strcpy(this->strVal, newStr);
    //free tmp
    delete[] newStr;
    return * this;
}


void DSString::split(DSVector<DSString> & destVec, char delimeter){
    if (VERBOSE) std::cout << "DSString split called" << std::endl;

    DSString tmp;
    int lastSplit = 0;
    for(int i = 0; i < this->length; i++){
        if (DEBUG) std::cout << "Current Split char index: " << i <<std::endl;
        if(this->strVal[i] == delimeter){

            //create item to place from split
            tmp = this->substring(lastSplit, i);
            if (DEBUG) std::cout << "String to add: " << tmp <<std::endl;

            // add item to destination vec
            destVec.append(tmp);
            if (DEBUG) std::cout << "append element!" << std::endl;

            lastSplit = i + 1;
        }
    }

    tmp = this->substring(lastSplit, this->length);

    //add last item to vector
    destVec.append(tmp);

}

//cleans punctuation off of ends of words
DSString DSString::cleanPunct(){
    DSString tmp(this->strVal);


    if((tmp.strVal[0] > 122 || tmp.strVal[0] < 97)&& tmp.size() >= 2){
        tmp = tmp.substring(1, -1);

    }

    if((tmp.strVal[tmp.size() - 1] > 122 || tmp.strVal[tmp.size() - 1] < 97) && tmp.size() >= 2){
        tmp = tmp.substring(0, -2);
    }
    return tmp;

}

bool DSString::operator != (const DSString& inString){
    if(*this == inString){
        return false;
    }
    return true;
}


bool DSString::contains(char delimeter){
    bool tmp = false;
    if(this->strVal != nullptr){
        for(int i = 0; i < length; i++){
            if(strVal[i] == delimeter){
                tmp = true;
            }
        }
    }

    return tmp;
}

//LEE

void DSString::toLower()
{
    if(this->size()>0)
    {
        for(int i=0;i<length;i++)
        {
            if(strVal[i]>= 'A' && strVal[i]<= 'Z')
            {
                strVal[i]+=32;
            }
        }
    }
}

//stream extraction
std::istream& operator>> (std::istream& inStream, const DSString& outString){
    if (VERBOSE) std::cout << "DSString stream extraction operator called" << std::endl;

    if(outString.length > 0){
        inStream >> outString.strVal;
    }
    else{
        inStream >> "Empty String!";
    }
    return inStream;
}

bool DSString::isArticle(DSString inStr)
{
    if(inStr.size() > 1)
    {
        if(inStr == "an" || inStr == "the")
            return true;
        else
            return false;
    }
    return true;
}

bool DSString::isPunct(char inChar)
{
    if(inChar == '(' ||  inChar == '.' || inChar == '[' || inChar == ' ' ||
       inChar == ';' ||  inChar == '<' ||  inChar == '#' || inChar == '+' ||
       inChar == '\t' ||  inChar == '*' || ((inChar > '0') &&(inChar < '9'))||
       inChar == ')' || inChar == ',' || inChar == ']' || inChar == ':' ||
       inChar == '\\' || inChar == '\n' || inChar == 47 || inChar == '>' ||
       inChar == '=' || inChar == '^' || inChar == '|' || inChar == '-' ||
       inChar == '_' || inChar == '&' || inChar == '~')
    {
        return true;
    }
    else
        return false;
}

bool DSString::functionCutter(char inChar)
{
    if(inChar == '(' ||  inChar == '.' || inChar == '[' || inChar == ' ' ||
       inChar == ';' ||  inChar == '<' ||  inChar == '#' || inChar == '+' ||
       inChar == '\t' ||  inChar == '*' || ((inChar > '0') &&(inChar < '9'))||
       inChar == ')' || inChar == ',' || inChar == ']' || inChar == ':' ||
       inChar == '\\' || inChar == '\n' || inChar == 47 || inChar == '>' ||
       inChar == '=' || inChar == '^' || inChar == '|' || inChar == '-' ||
       inChar == '_' || inChar == '&' || inChar == '~')
    {
        return true;
    }
    else
        return false;
}


bool DSString::isQuote(char inChar)
{
    if(inChar == '"')
        return true;
    else
        return false;
}

void DSString::vmSplit(DSVector<DSString> & splitVector){

    if (VERBOSE) std::cout << "DSString split called" << std::endl;

    DSString tmp;
    int lastSplit = 0;
    for(int i = 0; i < this->length; i++){
        if (DEBUG) std::cout << "Current Split char index: " << i <<std::endl;
        if(isPunct(this->strVal[i]) == true){

            //create item to place from split
            tmp = this->substring(lastSplit, i);
            if (DEBUG) std::cout << "String to add: " << tmp <<std::endl;

            if(tmp.size() > 3)
            {
                if(isPunct(tmp[3]) == false)
                {
                    splitVector.append(tmp);
                }
            }
            else if(tmp.size() > 1)
            {
                if(isPunct(tmp[0]) == false)
                {
                    splitVector.append(tmp);
                }
            }

            if (DEBUG) std::cout << "append element!" << std::endl;

            lastSplit = i + 1;
        }

    }

    tmp = this->substring(lastSplit, this->length);

    if(tmp.size() > 3)
    {
        if(isPunct(tmp[3]) == false)
        {
            splitVector.append(tmp);
        }
    }
    else if(tmp.size() > 1)
    {
        if(isPunct(tmp[0]) == false)
        {
            splitVector.append(tmp);
        }
    }

}
