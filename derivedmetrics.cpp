#include "derivedmetrics.h"

#include "avltree.h"
//#include <stdio.h>
//#include <stdlib.h>

//===========================
//       Test Metric
//===========================

testMetric::testMetric()
{
    this->name = DSString("TEST METRIC");
    this->verboseLines.deleteElement(0);
    createScore();
    setWeight();
}
testMetric::testMetric(int score, int weight)
{
    this->name = DSString ("TEST METRIC ++");
    this->verboseLines.deleteElement(0);
    this->score = score;
    this->weight = weight;
    for(int i = 0; i < score * weight; i++){
        this->verboseLines.append(DSString("This is a Test!"));
    }

}

void testMetric::createScore()
{
    this->score = 1;
}

void testMetric::setWeight()
{
    this->weight = 1;
}

//===============================
//      Comment Ratio
//===============================

cmtRatio::cmtRatio(directoryIterator &files){
    //std::cout << "Creating Comment Ratio Metric" <<std::endl;
    name = DSString("Comment to Line of File Ratio");
    std::cout << "Running: " << name <<std::endl;
    verboseLines.deleteElement(0);
    totalComments = 0;
    totalLines = 0;
    weight = 7;
    createScore(files);
}

//calculate score
void cmtRatio::createScore(directoryIterator &files){
    int allComments = 0;
    int allLines = 0;
    //iterate over files in directory and all sub dirs
    for(int i = 0; i < files.fileNames.getSize(); i++){

        //open file for evaluation
        ifstream input;
        input.open(files.fileNames[i].c_str());

        if(!input){
            std::cout << "Could not open File!" <<std::endl;
            break;
        }

        int lineCount = 0;
        int commentCount = 0;

        //define expressions for search

        //grabs all single line comments not includeing commented #includes

        string singleLine("\\s*(\\/\\/.*)");

        //grabs first line of multi line comments
        string multiLine("\\s*\\/\\*.*");

        string newLine("\\n");

        regex expr1(singleLine);
        regex expr2(multiLine);
        regex expr3(newLine);


        std::string fileContents((std::istreambuf_iterator<char>(input)),
                                    std::istreambuf_iterator<char>());

        //count single line comments
        sregex_iterator fileitr(fileContents.begin(),
                                fileContents.end(), expr1);
        sregex_iterator fileitr_end;

        //count single lines comments
        while(fileitr != fileitr_end) {

             std::smatch match = *fileitr;

             //incrament only on valid return
             if(match.size() >= 2){
                 commentCount++;
             }

             ++fileitr;
        }

        //count multi line comments
        sregex_iterator fileitr2(fileContents.begin(),
                                 fileContents.end(), expr2);
        sregex_iterator fileitr2_end;

        //count multi line comments
        while(fileitr2 != fileitr2_end) {

            std::smatch match = *fileitr2;

            //incrament only on valid return
            if(match.size() >= 2){
                commentCount++;
                //std::cout << match.str() <<std::endl;
            }

             ++fileitr2;
        }

        //count lines in file

        sregex_iterator fileitr3(fileContents.begin(),
                                 fileContents.end(), expr3);
        sregex_iterator fileitr3_end;

        //count newline chars
        while(fileitr3 != fileitr3_end) {
             lineCount++;
             ++fileitr3;
        }

        //close file
        input.close();

        totalComments += commentCount;
        totalLines += lineCount;

        //create record for reference
        DSString tmpRecord("File: ");
        tmpRecord = tmpRecord + files.fileNames[i] +
                DSString("\n\t\t\tLines Sampled: ") +
                lineCount + DSString("\n\t\t\tComments found: ") +
                commentCount;

        //update counters
        allComments += commentCount;
        allLines += lineCount;

        //add to verbose output
        verboseLines.append(tmpRecord);

    }

    //add final record with line totals
    DSString genRecord("Line Totals");
    genRecord = genRecord + DSString("\n\t\t\tTotal Lines Sampled: ")
            + DSString(allLines);
    genRecord = genRecord + DSString("\n\t\t\tTotal Comments Found: ")
            + DSString(allComments);
    verboseLines.append(genRecord);

    double ratio = (double)totalComments / (double)totalLines;
    score = 100 * abs(ratio - .10);
}

//========================
//   Delatation
//========================

//constructor
delatation::delatation(directoryIterator & files){
    name = DSString("Delatation");
    std::cout << "Running: " << name <<std::endl;
    weight = 10;

    averageCalls = 0;
    totalCalls = 0;
    numFunctions = 0;

    verboseLines.deleteElement(0);

    createScore(files);
}

//create score and set weight value
void delatation::createScore(directoryIterator & files){
    parser(files);

    delatate();
    weight = (int)((double)8.0 * (log((double)parseErrors)/ log((double)numFunctions)));
    score = abs(del - 50);
}

void delatation::parser(directoryIterator &files){


    //patterns for funciton declairation
    string functionDec("([^\\s]+)\\s*\\(.*\\)\\s*");
    string functionCall("([^\\s]+)\\s*\\(.*\\)\\s*;");

    regex funcDec(functionDec);
    regex funcCall(functionCall);

    //iterate over file
    for(int j = 0; j < files.fileNames.getSize(); j++){

        //open file
        ifstream input;

        //open file
        input.open(files.fileNames[j].c_str());

        //current working function name and calls
        DSVector<DSString> inCalls;
        DSString currFunc("");
        DSString currImpl("");

        //loop over file
        std::string fileContents((std::istreambuf_iterator<char>(input)),
                                    std::istreambuf_iterator<char>());

        //string containing entire file
        DSString fileString(fileContents.c_str());

        int lead = 0;
        int chase = 0;

        Stack<char> braces;

        for(int i = 0; i < fileString.size(); i++){

            //begin spaghetti parser

            if(fileString[i] == '{'){
                //set lead if first set


                //flag to check for class keyword
                bool push = true;

                if(braces.isEmpty()){
                    //set index of beginning of function
                    int tmpchase = i;

                    //grab location of class keyword when present
                    while(fileString[tmpchase] != ' '){
                        tmpchase --;
                    }

                    //check if class keyword is present
                    if(fileString.substring(tmpchase -5, tmpchase)
                            == DSString("class")){
                        push = false;
                    }

                    //update chase index
                    else{
                        chase = i;
                    }

                }

                //add to stack
                if(push){
                    braces.push('{');
                }
            }

            //if end of block
            else if(fileString[i] == '}'){
                //pop from stack
                if(!braces.isEmpty()){
                    braces.pop();
                }

                else{
                    parseErrors += 1;
                }

                //check if end of dec
                if(braces.isEmpty()){
                    //record number of errors for comparason
                    int errNo = parseErrors;

                    //set index of end of function
                    lead = i;

                    //read backward to open parenthesis
                    int reverseCount1 = chase;

                    //find 9
                    while(fileString[reverseCount1] != '('){
                        -- reverseCount1;
                        if(reverseCount1 < 0){
                            break;
                        }
                    }

                    //once ( is found, find name of function

                    int reverseCount2 = reverseCount1;
                    bool pastSpace = 0;
                    while(fileString[reverseCount2] != ' ' ||
                          pastSpace == true){
                        //change white space protection flag
                        if(fileString[reverseCount2] != ' '){
                            pastSpace = false;
                        }

                        reverseCount2 --;
                    }

                    //get function name and create list of function calls
                    currFunc = fileString.substring(reverseCount2, reverseCount1);
                    currImpl = fileString.substring(chase, lead + 1);
                    inCalls = findInternalCalls(currImpl);

                    if(currFunc.contains(' ')){
                        DSVector<DSString> plzno;
                        currFunc.split(plzno, ' ');
                        currFunc = plzno[1];
                    }

                    //check for odd format lines
                    if(currFunc.contains('\n')){
                        parseErrors += 1;
                    }

                    //clean extra case words
                    if(currFunc == DSString("") || currFunc == DSString("if")
                            || currFunc == DSString("while")
                            || currFunc == DSString("for")){
                        parseErrors += 1;
                    }



                    //add to table if no parse errors occured
                    if(errNo == parseErrors ){
                        DSString tmpRecord = DSString("Found Function: ");
                        tmpRecord = tmpRecord + currFunc + DSString("\n\t\t\tFile: ");
                        tmpRecord =  tmpRecord + files.fileNames[j];
                        tmpRecord = tmpRecord + DSString("\n\t\t\t")
                                + DSString("Internal Calls: ")
                                + DSString(inCalls.getSize());

                        verboseLines.append(tmpRecord);

                        totalCalls += inCalls.getSize();
                        numFunctions += 1;
                    }
                }
            }
        }
    }

    averageCalls = (double)totalCalls / (double)numFunctions;
    //create general error and function number record
    //append statistics
    DSString genRecord("Statistics");
    genRecord = genRecord + DSString("\n\t\t\tFunctions found: ")
            + numFunctions;
    genRecord = genRecord + DSString("\n\t\t\tAverage in Function Calls: ")
            + DSString(averageCalls);
    genRecord = genRecord + DSString("\n\t\t\tParsing Errors: ")
            + DSString(parseErrors);
    verboseLines.append(genRecord);
}

void delatation::delatate(){
    //calculate area of log triangle
    del = 15 * (.5 * (log((double)numFunctions) * (log((double)averageCalls)
                    * log((double)averageCalls))));
}


//search for internal function calls
DSVector<DSString> delatation::findInternalCalls(DSString input){
    DSVector<DSString> tmpCalls;

    //expressions to find function calls
    string ignorekeys("\\b(for|while|do|if|else)\\b");
    string functionDef("([^\\s]+)\\s*\\(.*\\)\\s*;");

    regex expr1(functionDef);

    //string of all of function implementation
    string functionContents(input.c_str());

    //count single line comments
    sregex_iterator functitr(functionContents.begin(),
                            functionContents.end(), expr1);
    sregex_iterator functitr_end;

    //iterate until no more matches are found
    while(functitr != functitr_end) {

         smatch innermatch = *functitr;
         DSVector<DSString> tokens;
         DSString(innermatch.str().c_str()).split(tokens, '(');

         tmpCalls.append(tokens[0]);
         ++functitr;
    }

    return tmpCalls;

}


//==============================
// Comment Quality Metric START
//==============================

//construcor
commentQuality::commentQuality(directoryIterator files){
    name = DSString("Comment Quality");
    std::cout << "Running: " << name <<std::endl;
    verboseLines.deleteElement(0);
    totalWordCount = adjectiveCount = adverbCount = verbCount = fillerCount = contentCount = 1;
    weight = 10;
    createScore(files);
}

//create score table
void commentQuality::peiceWiseScore(hashtable<int, int> & intable){
    int value = 0;

    for(int i = 0; i < 127; i++){
        //go easy on people with small portion of error
        if(i < 30){
            int squareRoot = double(2*i);
            double tempValue = sqrt(squareRoot);
            value = int(tempValue);
        }
        //punish people for having higher percentage of bad conventions
        else if (i < 95){
            value = i;
        }
        //reduce the harshness when the mistakes are repeated
        else{
            value = sqrt(i) + 95;
        }

        intable.put(i, value);
    }
}

//check to see if a word indirectly incidates verb usage
bool commentQuality::verbIndicator(DSString ending)
{
    if(ending == "is" || ending == "are" || ending == "be" || ending == "were" || ending == "can")
        return true;
    else if ((ending.substring(ending.size()-2, ending.size()) == "ze"))
        return true;
    else if ((ending.substring(ending.size()-2, ending.size()) == "se"))
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "ed")
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "te")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ing")
        return true;
    else if(ending == "shall" || ending == "will" || ending == "would" || ending == "should")
        return true;
    else if(ending == "has" ||ending == "had" ||ending == "have" ||ending == "must")
        return true;
    else
        return false;
}

//check if word is adjective
bool commentQuality::isAdj(DSString ending)
{
    if(ending.substring(ending.size()-3, ending.size()) == "ble")
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "al")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ful")
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "ic")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ive")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ous")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ish")
        return true;
    else if (ending == "all" || ending == "some" || ending =="most" || ending =="none" ||
             ending == "any" || ending == "enough" || ending =="every")
        return true;
    else
        return false;
}

//check if word is adverb
bool commentQuality::isAdv(DSString ending)
{
    if(ending.substring(ending.size()-2, ending.size()) == "ly")
        return true;
    else if(ending.substring(ending.size()-4, ending.size()) == "ward")
        return true;
    else
        return false;
}

//check if char is letter
bool commentQuality::isAlpha(char firstChar)
{
    if(firstChar >='a' && firstChar <= 'z')
        return true;
    else if(firstChar >='A' && firstChar <= 'Z')
        return true;
    else
        return false;
}

//=========
//COMPILES
//=========

void commentQuality::createScore(directoryIterator files)
{

    //AVL Tree of filler word list
    AVLTree<DSString> fillerTree;
    fillerTree.addNode(DSString("about"));
    fillerTree.addNode(DSString("above"));
    fillerTree.addNode(DSString("across"));
    fillerTree.addNode(DSString("adjacent"));
    fillerTree.addNode(DSString("after"));
    fillerTree.addNode(DSString("against"));
    fillerTree.addNode(DSString("along"));
    fillerTree.addNode(DSString("among"));
    fillerTree.addNode(DSString("around"));
    fillerTree.addNode(DSString("as"));
    fillerTree.addNode(DSString("at"));
    fillerTree.addNode(DSString("before"));
    fillerTree.addNode(DSString("behind"));
    fillerTree.addNode(DSString("below"));
    fillerTree.addNode(DSString("beneath"));
    fillerTree.addNode(DSString("beside"));
    fillerTree.addNode(DSString("between"));
    fillerTree.addNode(DSString("but"));
    fillerTree.addNode(DSString("by"));
    fillerTree.addNode(DSString("except"));
    fillerTree.addNode(DSString("for"));
    fillerTree.addNode(DSString("from"));
    fillerTree.addNode(DSString("in"));
    fillerTree.addNode(DSString("inside"));
    fillerTree.addNode(DSString("into"));
    fillerTree.addNode(DSString("less"));
    fillerTree.addNode(DSString("like"));
    fillerTree.addNode(DSString("near"));
    fillerTree.addNode(DSString("of"));
    fillerTree.addNode(DSString("on"));
    fillerTree.addNode(DSString("onto"));
    fillerTree.addNode(DSString("out"));
    fillerTree.addNode(DSString("outside"));
    fillerTree.addNode(DSString("over"));
    fillerTree.addNode(DSString("since"));
    fillerTree.addNode(DSString("than"));
    fillerTree.addNode(DSString("through"));
    fillerTree.addNode(DSString("throughout"));
    fillerTree.addNode(DSString("under"));
    fillerTree.addNode(DSString("until"));
    fillerTree.addNode(DSString("up"));
    fillerTree.addNode(DSString("within"));
    fillerTree.addNode(DSString("without"));
    fillerTree.addNode(DSString("and"));
    fillerTree.addNode(DSString("nor"));
    fillerTree.addNode(DSString("or"));
    fillerTree.addNode(DSString("yet"));
    fillerTree.addNode(DSString("so"));
    fillerTree.addNode(DSString("though"));
    fillerTree.addNode(DSString("unless"));
    fillerTree.addNode(DSString("rather"));
    fillerTree.addNode(DSString("whether"));
    fillerTree.addNode(DSString("when"));
    fillerTree.addNode(DSString("because"));
    fillerTree.addNode(DSString("what"));
    fillerTree.addNode(DSString("who"));
    fillerTree.addNode(DSString("which"));
    fillerTree.addNode(DSString("how"));
    fillerTree.addNode(DSString("where"));
    fillerTree.addNode(DSString("while"));


    string commentLine("\\s*(\\/\\/.*)|\\/\\*.*\\s*(.*\\s*)\\**\\*\\/"
                       "|\\*.*\\s*(\\**)\\**\\*|\\/(.*)");


    regex expr1(commentLine);

    smatch Match1;


    string lineString;

    for(int i=0; i<files.fileNames.getSize();i++)
    {

        //vector for ratio calculation
        DSVector<DSString> wordsInComment;

        //vector to hold string dumps
        DSVector<DSString> stringDump;

        DSVector<int> betweenComment;

        fstream input;
        input.open(files.fileNames[i].c_str());

        char* buffer = new char[200];

        int limitCount=0;
        int lineBtwnComment = 0;

        //To prevent from breaking, sample small number of lines.
        while(!input.eof() && limitCount < 500)
        {
            input.getline(buffer,200);
            lineString = buffer;
            DSString lineDS = DSString(buffer);

            if(lineDS != "")
            {
                limitCount++;
                //if comment line is found, store the lines between comments into vector and reset
                if(std::regex_match(lineString, Match1, expr1))
                {
                    stringDump.append(lineDS);
                }
            }

        }//end of iteration whileloop

        delete [] buffer;
        input.close();

        //get the string out of dump and into ratio calculating vector
        for(int i=0; i<stringDump.getSize(); i++)
        {
            stringDump[i].vmSplit(wordsInComment);
        }

        for(int j=0; j<wordsInComment.getSize();j++)
        {
            wordsInComment[j].toLower();

            //read in the words, increment total counter
            totalWordCount += 1;

            //increment according counters
            if(isAdj(wordsInComment[j]) == true)
                adjectiveCount +=1;

            else if(isAdv(wordsInComment[j]) == true)
                adverbCount += 1;

            //if the word is found in the fillerTree, increment filler counter
            else if(fillerTree.findValue(wordsInComment[j]) != nullptr)
                fillerCount += 1;

            //if a verb form is found, increment verb counter
            else if(verbIndicator(wordsInComment[j]) == true)
                verbCount +=1;
            //if all else are false, increment noun
            else
            {
                contentCount += 1;
            }

        }//end of ratio calculation forloop


        //Ratio Delcaraiton
        int adjDiv, advDiv, filDiv, filMod, contDiv, contMod, verbDiv, verbMod, modDiv, modMod = 1;

        modifierCount = adjectiveCount+adverbCount;

        totalWordCount +=1;
        //get Div value and Mod value for precise expresison of int -> double conversion.

        if(totalWordCount <2)
        {
            adjDiv = (100*adjectiveCount)/(totalWordCount);
            advDiv = (100*adverbCount)/totalWordCount;
            filDiv = (100*fillerCount)/totalWordCount;
            filMod = ((10000*fillerCount)/totalWordCount)%100;
            verbDiv = (100*verbCount)/totalWordCount;
            verbMod = ((10000*verbCount)/totalWordCount)%100;
            contDiv = (100*contentCount)/totalWordCount;
            contMod = ((10000*contentCount)/totalWordCount)%100;
            modDiv = (100*modifierCount)/totalWordCount;
            modMod = ((10000*modifierCount)/totalWordCount)%100;
            totalWordCount -=1;
        }

        else
        {
            //ADDED -> subtract wordscount for non zero words
            totalWordCount -=1;
            adjDiv = (100*adjectiveCount)/(totalWordCount);
            advDiv = (100*adverbCount)/(totalWordCount);
            filDiv = (100*fillerCount)/(totalWordCount);
            filMod = ((10000*fillerCount)/(totalWordCount))%100;
            contDiv = (100*contentCount)/(totalWordCount);
            contMod = ((10000*contentCount)/totalWordCount)%100;
            verbDiv = (100*verbCount)/totalWordCount;
            verbMod = ((10000*verbCount)/totalWordCount)%100;
            modDiv = (100*modifierCount)/totalWordCount;
            modMod = ((10000*modifierCount)/totalWordCount)%100;
        }

         //set scoring rubric
         if((adjDiv + advDiv) < 10)
         {
             score += 5.0;
         }
         else if((adjDiv+advDiv) > 20)
         {
             score += 9.0;
         }

         if(verbDiv < 15)
         {
             score += 5.0;
         }
         else if(verbDiv > 40)
         {
             score += 3;
         }

         if(contDiv<50)
         {
             score += 3.0;
         }

         //
         else if(contDiv>70)
         {
             score += 10.0;
         }

         //long and complexed sentences. Uninformative
         if(filDiv>10)
         {
             score += 10.0;
         }

         //long and complexed sentences, often short overall comment.
         if(verbDiv > contDiv)
         {
             score += 10.0;
         }
         //no comments
         if(totalWordCount < 2)
         {
             score += 10;
         }

        //create record for reference
        DSString tmpRecord("File: ");
        tmpRecord = tmpRecord + files.fileNames[i]
                + DSString("\n\t\t\t Total Words in Comment: ") + totalWordCount
                + DSString("\n\t\t\t Content Ratio:              ") + contDiv +DSString(".") + contMod + DSString("%")
                + DSString(" | ") + DSString("Nouns and Pronouns: ") + contentCount
                + DSString("\n\t\t\t Verb Ratio:                 ") + verbDiv +DSString(".") + verbMod + DSString("%")
                + DSString(" | ") + DSString("Verbs: ") + verbCount
                + DSString("\n\t\t\t Filler Ratio:               ") + filDiv +DSString(".") + filMod + DSString("%")
                + DSString(" | ") + DSString("Conjunction and Preposition: ") + fillerCount
                + DSString("\n\t\t\t Modifier Ratio:             ") + modDiv +DSString(".") + modMod + DSString("%")
                + DSString(" | ") + DSString("Adjective and Adverb: ") + modifierCount;

                //add to verbose output
                verboseLines.append(tmpRecord);

                //reset counters
                totalWordCount = contentCount = fillerCount = verbCount = adjectiveCount = adverbCount = modifierCount = limitCount = lineBtwnComment = 0;

    }//end of iteration forloop - end of file


    //Use hashtable to plot piecewise fucntion of Key Values.
    //Make sure that scores are adjusted according to piecewise function that will be linient on
    //lower frequency mistakes and harsher on repeated mistakes.
    hashtable<int, int> distributionTable;
    peiceWiseScore(distributionTable);
    double rawScore = score/files.fileNames.getSize();
    score = distributionTable.get(rawScore);

    //reset the counter values
    totalWordCount = adverbCount = fillerCount = contentCount = adjectiveCount = modifierCount = 0;
}//end of function



//==================================
// Variable and Function Name Metric
//==================================

//For scoring of multiple parameters, utilize built hashtable functionality for forming a piecewise function.
void varAndFuncName::peiceWiseScore(hashtable<int, int> & intable){
    int value = 0;

    for(int i = 0; i < 127; i++){
        //go easy on people with small portion of error
        if(i < 30){
            int squareRoot = double(2*i);
            double tempValue = sqrt(squareRoot);
            value = int(tempValue);
        }
        //punish people for having higher percentage of bad conventions
        else if (i < 95){
            value = i;
        }
        //reduce the harshness when the mistakes are repeated
        else{
            value = sqrt(i) + 95;
        }

        intable.put(i, value);
    }
}

//constructor
varAndFuncName::varAndFuncName(directoryIterator files)
{
    name = DSString("Variable and Function Naming");
    std::cout << "Running: " << name <<std::endl;
    verboseLines.deleteElement(0);
    weight = 7;
    createScore(files);
}

void varAndFuncName::createScore(directoryIterator files)
{
    //AVL tree holding type names and known nonNames
    AVLTree<DSString> fundamentalType;
    fundamentalType.addNode(DSString("int"));
    fundamentalType.addNode(DSString("char"));
    fundamentalType.addNode(DSString("double"));
    fundamentalType.addNode(DSString("int*"));
    fundamentalType.addNode(DSString("char*"));
    fundamentalType.addNode(DSString("double*"));
    fundamentalType.addNode(DSString("signed"));
    fundamentalType.addNode(DSString("unsigned"));
    fundamentalType.addNode(DSString("long"));
    fundamentalType.addNode(DSString("short"));
    fundamentalType.addNode(DSString("float"));
    fundamentalType.addNode(DSString("float*"));
    fundamentalType.addNode(DSString("wchar_t"));
    fundamentalType.addNode(DSString("enum"));
    fundamentalType.addNode(DSString("bool"));
    fundamentalType.addNode(DSString("void"));
    fundamentalType.addNode(DSString("std"));
    fundamentalType.addNode(DSString("string"));
    fundamentalType.addNode(DSString("vector"));
    fundamentalType.addNode(DSString("list"));
    fundamentalType.addNode(DSString("typedef"));
    fundamentalType.addNode(DSString("return"));
    fundamentalType.addNode(DSString("class"));
    fundamentalType.addNode(DSString("struct"));
    fundamentalType.addNode(DSString("using"));
    fundamentalType.addNode(DSString("namespace"));
    fundamentalType.addNode(DSString("std"));


    //for, if, else if, while, do, class names, struct names, single line comment, multiline comments are not included as they are outliers
    // :: & : as for class declaration of funciton, assume it will be called in the program
    string notName("(.*for.*)|(.*if.*)|(.*else if.*)|(.*while.*)|(.*do.*)"); //(.*:.*) -> : or class dec||(.*\".*) -> string assign, |(.*class.*)|(.*struct.*) -> for special case
    string commentLines("\\s*(\\/\\/.*)|\\/\\*.*\\s*(.*\\s*)\\**\\*\\/|\\\\.*");

    //variable name: line with = sign must have variable. ; also may variable name.
    string variable("(.*\\=\\.*).*\\;|(.*\\;)");
    //function names: given that notName parameter is on, lines with ( must have function name.
    string function("(.*\\(.*)");

    regex varName(variable);
    regex nonName(notName);
    regex funcName(function);
    regex comments(commentLines);
    smatch Match1;
    smatch Match2;
    smatch Match3;

    for(int i=0; i<files.fileNames.getSize(); i++)
    {
        //containers for parsing for funtion and variable names
        DSVector<DSString> stringDump;
        DSVector<DSString> nameVector;
        DSVector<DSString> processVector;
        AVLTree<DSString> processTree;

        int shortened = 1;
        int numbered = 1;
        int badName = 1;
        int shortenedRatio = 1;
        int numberedRatio =1;
        int badNameRatio = 1;
        int totalName = 1;

        int shortLength = 1;
        int longLength = 1;
        int badLength = 1;
        int shortLengthRatio =1;
        int longLengthRatio =1;
        int badLengthRatio = 1;
        int totalLength =1;

        //open files
        fstream input;
        input.open(files.fileNames[i].c_str());

        //break condition if the file can't be openned
        if(!input)
        {
            std::cout<<"File can't be openned"<<std::endl;
            break;
        }

        //Counter for sampling
        int limitCount = 0;

        char* buffer = new char[200];
        string lineString;

        //read in until end of file
        while(!input.eof() && limitCount < 500)
        {
            input.getline(buffer,200);
            lineString = buffer;
            DSString lineDS = DSString(buffer);

            //if the string is part of nonVariable or nonFunction
            if(std::regex_match(lineString, Match1, nonName) ||
               std::regex_match(lineString, Match2, comments))
            {
                //bool notName = true;

            }
            //if not, make sure the nonName flag is on and check
            else
            {
                if((std::regex_match(lineString, Match2, varName) ||
                     std::regex_match(lineString, Match3, funcName)))
                {
                    stringDump.append(lineDS);
                    limitCount++;
                }
            }
        }//end of file iteration while loop

        delete [] buffer;
        input.close();

        //split the line of strings
        for(int l=0; l<stringDump.getSize(); l++)
        {
            stringDump[l].vmSplit(nameVector);
        }

        //add words to vector for processing
        for(int j=0; j<nameVector.getSize(); j++)
        {
            //only add if split string is greater than 3, for no variable of size 3 is informative
            if(nameVector[j].size() > 3)
            {
                //if the word is in not fundamentalType
                if(fundamentalType.findValue(nameVector[j]) == nullptr)
                {
                    //if the word is not already in tre
                    if(processTree.findValue(nameVector[j]) == nullptr)
                    {
                        processTree.addNode(nameVector[j]);
                        processVector.append(nameVector[j]);
                    }
                }
            }
            //if the variable is size 3 or smaller, increase counter for bad naming.
            else
            {
                //if the string is not empty && (starts with alphabet) it is a name -> change the score.
                if((!isNotLowerAlpha(nameVector[j][0]) || isUpperCase(nameVector[j][0])) && nameVector[j] != "")
                {
                    totalLength++;
                    shortLength++;
                }
            }
        }

        //increment variables for scoring
        for(int x=0; x<processVector.getSize(); x++)
        {
            totalLength++;
            totalName++;

            if(hasNumber(processVector[x]))
            {
                numbered ++;
            }
            else if (isAbbreviated(processVector[x]))
            {
                shortened++;
            }

            if(hasBadNameLength(processVector[x] == true))
            {
                longLength++;
            }
        }

        //get ratio and numbers for results
        badName = numbered + shortened;
        badNameRatio = (100*badName)/(totalName);
        shortenedRatio = (100*shortened)/(totalName);
        numberedRatio = (100*numberedRatio)/totalName;
        longLengthRatio = (100* longLength)/totalLength;
        shortLengthRatio = (100*shortLength)/totalLength;

        //std::cout<<"BNratioCalc: "<<badNameRatio<<std::endl;

        if(((100*badName)%(totalName)) > badNameRatio/2)
            badNameRatio +=1;

        badLength = longLength + shortLength;
        badLengthRatio = (100*badLength)/(totalLength);

        //std::cout<<"BLratioCalc: "<<badLengthRatio<<std::endl;

        if(((100*badLength)%(totalLength) > badLengthRatio/2))
            badLengthRatio +=1;

        //depending on the severety of scores, increment or decrement different points.
        if(badNameRatio > 70)
        {
            score+=30;
        }
        else if(badNameRatio > 50 && badNameRatio < 69)
        {
            score+=20;
        }
        else if(badNameRatio < 30)
        {
            score-=10;
        }

        if(badLengthRatio > 30 || badLengthRatio <51)
        {
            score+=10;
        }
        else if(badLengthRatio >50)
        {
            score+=25;
        }

        //create record for reference
        DSString tmpRecord("File: ");
        tmpRecord = tmpRecord + files.fileNames[i]
                + DSString("\n\t\t\t Variable And Function Name:")
                + DSString("\n\t\t\t Abbreviated Name Ratio    : ") + shortenedRatio + DSString("%")
                + DSString("\n\t\t\t Numbered Name Ratio       : ") + numberedRatio + DSString("%")
                + DSString("\n\t\t\t Short Name Ratio          : ") + shortLengthRatio + DSString("%")
                + DSString("\n\t\t\t Long Name Ratio           : ") + longLengthRatio + DSString("%")
                + DSString("\n\t\t\t Ineffective Name Ratio    : ") + badLengthRatio + DSString("%");

                //add to verbose output
                verboseLines.append(tmpRecord);

    }//end of iterator forloop -> end of a file

    //Use hashtable to plot piecewise fucntion of Key Values.
    //Make sure that scores are adjusted according to piecewise function that will be linient on
    //lower frequency mistakes and harsher on repeated mistakes.
    hashtable<int, int> distributionTable;
    peiceWiseScore(distributionTable);
    double rawScore = score/files.fileNames.getSize();
    score = distributionTable.get(rawScore);

}//end of function

bool varAndFuncName::hasBadNameLength(DSString nameStr)
{
    return (nameStr.size() > 25);
}

//checks if string has numerals
bool varAndFuncName::hasNumber(DSString nameString)
{
        if(isAlpha(nameString[nameString.size()]) == false ||
           isAlpha(nameString[0]) == false)
            return true;
    return false;
}

//checks if char is letter
bool varAndFuncName::isAlpha(char checkChar)
{
    if(checkChar >='a' && checkChar <= 'z')
        return true;
    else if(checkChar >='A' && checkChar <= 'Z')
        return true;
    else if(checkChar == '_')
        return true;
    else
        return false;
}

//checks for uppercase
bool varAndFuncName::isUpperCase(char checkChar)
{
    //if char is within bounds of uppercase letters, return true
    return(checkChar >= 65 && (checkChar <= 90 || checkChar == '_'));
}

//determines if string is abreviation
bool varAndFuncName::isAbbreviated(DSString nameString)
{
    //counter for consecutive consonants
    int consecCount = 0;

    //loop through chars in a given string
    for(int i=0;i<nameString.size();i++)
    {
        if(consecCount < 4)
        {
            //check for consonants
            if(isConsonant(nameString[i]) == true)
            {
                if(isUpperCase(nameString[i]) == true)
                    consecCount = 0;
                else
                    consecCount ++;
            }

            //for vowels
            else
                consecCount = 0;
        }
        else
            //if the consecutive consonant count is over 3, it is most likely abbreviated
            return true;
    }
        //if all checks out, it is most likely not abbreviated and following good convention
        return false;

}

//checks if letter is consonant
bool varAndFuncName::isConsonant(char checkChar)
{
    //check if a char is lowerCase Vowel.
    if(checkChar == 'a' || checkChar == 'e' || checkChar == 'i' || checkChar == 'o' || checkChar == 'u' || checkChar == 'y')
        return false;
    //check if a char is upperCase Vowel
    else if(checkChar == 'A' || checkChar == 'E' || checkChar == 'I' || checkChar == 'O' || checkChar == 'U' || checkChar == 'Y')
        return false;
    //check for special characters used in naming
    else if(checkChar == ':' ||checkChar == '_' ||checkChar == '[')
            return false;
    //if not any, it is consonant
    else
        return true;
}

//checks if not lower letter
bool varAndFuncName::isNotLowerAlpha(char firstChar)
{
    if((firstChar >='a' && firstChar <= 'z')||firstChar == '_')
        return false;
    else
        return true;
}

//==================================
// Code Format Metric
//==================================

codeFormat::codeFormat(directoryIterator files)
{
    name = DSString("Code Format");
    std::cout << "Running: " << name <<std::endl;
    verboseLines.deleteElement(0);
    weight = 5;
    createScore(files);
}

void codeFormat::peiceWiseScore(hashtable<int, int> & intable){
    int value = 0;

    for(int i = 0; i < 127; i++){
        //go easy on people with small portion of error
        if(i < 30){
            int squareRoot = double(2*i);
            double tempValue = sqrt(squareRoot);
            value = int(tempValue);
        }
        //punish people for having higher percentage of bad conventions
        else if (i < 95){
            value = i;
        }
        //reduce the harshness when the mistakes are repeated
        else{
            value = sqrt(i) + 95;
        }

        intable.put(i, value);
    }
}

void codeFormat::createScore(directoryIterator files)
{

    string lineString;
    //iterate through file
    for(int i=0; i<files.fileNames.getSize(); i++)
    {
        //containers for parsing function names
        DSVector<DSString> stringDump;

        int totalLineLength = 1;
        int longLineCount = 1;
        int avgLineLength = 1;

        fstream input;
        input.open(files.fileNames[i].c_str());

        char* buffer = new char[200];
        int limitCount=0;

        while(!input.eof() && limitCount < 300)
        {
            input.getline(buffer,200);
            lineString = buffer;
            DSString lineDS = DSString(buffer);

            //store the line for processing
            if(strlen(lineDS.c_str()) > 2)
            {
                limitCount++;
                stringDump.append(lineDS);
            }

        } //end of per file while loop

        delete [] buffer;
        input.close();

        for(int i=0; i<stringDump.getSize(); i++)
        {
            //add up all lengths
            totalLineLength += stringDump[i].size();

            //count the longer lines
            if(stringDump[i].size() > 80)
                longLineCount++;
        }


        //get average length
        avgLineLength = totalLineLength/stringDump.getSize();

        if(avgLineLength < 15 || avgLineLength > 75)
        {
            score += 30;
        }
        else if (avgLineLength > 30 && avgLineLength < 60)
        {
            score += 0;
        }
        else
        {
            score += 10;
        }

        //create record for reference
        DSString tmpRecord("File: ");
        tmpRecord = tmpRecord + files.fileNames[i]
                + DSString("\n\t\t\t Code Format:")
                + DSString("\n\t\t\t Average Line Lengt          ") + avgLineLength
                + DSString("\n\t\t\t Lines over 80 chars:        ") + longLineCount;

                //add to verbose output
                verboseLines.append(tmpRecord);

    }//end of iterate file forloop
    
    //Use hashtable to plot piecewise fucntion of Key Values.
    //Make sure that scores are adjusted according to piecewise function that will be linient on
    //lower frequency mistakes and harsher on repeated mistakes.
    hashtable<int, int> distributionTable;
    peiceWiseScore(distributionTable);
    double rawScore = score/files.fileNames.getSize();
    score = distributionTable.get(rawScore);
}
