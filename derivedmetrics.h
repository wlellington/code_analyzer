#ifndef DERIVEDMETRICS_H
#define DERIVEDMETRICS_H
#include "metric.h"
#include "directoryiterator.h"
#include "hashtable.h"
#include "linkedlist.h"
#include "stack.h"
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

//========================
// Delatation metric
//========================
class delatation : public basemetric{

public:
    //deepest route found
    int maxDepth;

    int parseErrors;

    int numFunctions;

    double averageCalls;

    int totalCalls;

    double del;

    //base construtor
    delatation();

    //constructor with file iterator, calls parser
    delatation(directoryIterator & files);

    void createScore(directoryIterator & files);

private:

    //iterative backtracking functions
    void delatate();

    //parse function body into calls
    DSVector<DSString> findInternalCalls(DSString input);


    //file parser
    void parser(directoryIterator & files);


};

//========================
// Comment Ratio Metric
//========================
class cmtRatio : public basemetric{
public:

    //totals for tracking ratio
    int totalLines;
    int totalComments;

    //constructor with file iterator
    cmtRatio(directoryIterator & files);

    //score creation implementation
    void createScore(directoryIterator & files);

};


//========================
// Comment Quality Metric
//========================
class commentQuality : public basemetric
{
public:

    int totalWordCount;
    int adjectiveCount;
    int adverbCount;
    int modifierCount;
    int fillerCount;
    int verbCount;
    int contentCount;

    //ADD FUNCTION HERE
    void peiceWiseScore(hashtable<int, int> & intable);

    //constructor with iterator
    commentQuality(directoryIterator files);

    //score creation implementation
    void createScore(directoryIterator files);
    bool verbIndicator(DSString);
    //void getRatio(DSString, AVLTree<DSString>);

    //boolean functions for type of words
    bool isAdj(DSString);
    bool isAdv(DSString);

    //boolean function for checking if the comment is content or for legibility
    bool isAlpha(char);
};

//==================================
// Variable and Function Name Metric
//==================================
class varAndFuncName : public basemetric
{
public:

    varAndFuncName(directoryIterator files);
    void createScore(directoryIterator files);

    //ADD FUNCTION HERE
    void peiceWiseScore(hashtable<int, int> & intable);

    bool hasNumber(DSString);
    bool isAbbreviated(DSString);
    bool isUpperCase(char);
    bool isConsonant(char);
    bool isNotLowerAlpha(char);
    bool isAlpha(char);
    bool hasBadNameLength(DSString);

};

//==================================
// Code Formatting Metric
//==================================
class codeFormat : public basemetric
{
public:

    void peiceWiseScore(hashtable<int, int> & intable);

    codeFormat(directoryIterator files);
    void createScore(directoryIterator files);

};

//Troubleshooting metric
class testMetric : public basemetric
{
public:
    testMetric();
    testMetric(int score, int weight);
    void setWeight();

    void createScore();
};

//comment to line number ratio


#endif // DERIVEDMETRICS_H
