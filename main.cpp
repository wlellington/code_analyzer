#include <iostream>
#include <fstream>
#include "directoryiterator.h"
#include "metric.h"
#include "derivedmetrics.h"

void test();
void printResults(DSVector<basemetric> &tests, bool verbose);
void writeResults(DSVector<basemetric> &tests, bool verbose, DSString outFile);
double calculateScore(DSVector<basemetric>& tests);

int main(int argc, char* const argv[]){

    bool isVerbose = false;

    //verify parameters are valid
    if(argc <= 1){
        std::cout << "Invalid Parameters" <<std::endl;
        return -1;
    }

    if(DSString(argv[2]) == DSString("-v")){
        isVerbose = true;
    }

    //print status message
    std::cout << "Executing Analyzer on: " << argv[1] << std::endl;
    std::cout << "Running in";
    if(isVerbose){
        std::cout << " Verbose";
    }
    else{
        std::cout << " Brief";
    }
    std::cout << " mode" << std::endl;
    std::cout << "Output file: " << argv[3] <<std::endl;


    //assign members
    DSString outFile(argv[3]);

    //create file iterator
    directoryIterator dirTree(argv[1]);


    //create tests
    DSVector<basemetric> metricVector;
    metricVector.append(cmtRatio(dirTree));
    metricVector.append(delatation(dirTree));
    metricVector.append(commentQuality(dirTree));
    metricVector.append(varAndFuncName(dirTree));
    metricVector.append(codeFormat(dirTree));


    //save results
    writeResults(metricVector, isVerbose, outFile);


    std::cout << "Done!" << std::endl;
    return 0;
}

//===========================
//    Score Functionality
//===========================

//calculate total score for all tests run
double calculateScore(DSVector<basemetric>& tests)
{
    int totalWeight = 0;
    double totalScore = 0;

    //find total for percentage breakdown
    for(int i = 0; i < tests.getSize(); i++){
        totalWeight += tests[i].weight;
    }
    for(int i = 0; i < tests.getSize(); i++){
        totalScore += tests[i].score *
                    ((double)tests[i].weight / (double)totalWeight);
    }

    return totalScore;
}

//print results to console
void printResults(DSVector<basemetric>& tests, bool verbose){

    std::cout << "Total Score: " << calculateScore(tests) <<std::endl;
    //iterate over tests
    for(int i =0; i < tests.getSize(); i++){
        //print test and scores
        std::cout << "\t" << tests[i].name << std::endl;
        std::cout << "\t\tScore: " << tests[i].score << " Weight: "
                  << tests[i].weight << std::endl;
    }

    //print out records if verbose mode is on
    if(verbose){
        std::cout << "Details" << std::endl;

        //iterate over tests
        for(int i =0; i < tests.getSize(); i++){

            std::cout << "\t" << tests[i].name << std::endl;

            //print records
            for(int j = 0; j < tests[i].verboseLines.getSize(); j++){
                std::cout << "\t\tRecord " << j << ": "<<
                             tests[i].verboseLines[j] <<std::endl;
            }
        }
    }
}

//write results to file
void writeResults(DSVector<basemetric>& tests, bool verbose, DSString file){

    std::cout << "Writing to File" <<std::endl;

    ofstream output(file.c_str());

    output << "Total Score: " << calculateScore(tests) <<std::endl;
    //iterate over tests
    for(int i =0; i < tests.getSize(); i++){
        //print test and scores
        output << "\t" << tests[i].name << std::endl;
        output << "\t\tScore: " << tests[i].score << " Weight: "
                  << tests[i].weight << std::endl;
    }

    //print out records if verbose mode is on
    if(verbose){
        output << "Details" << std::endl;

        //iterate over tests
        for(int i =0; i < tests.getSize(); i++){

            output << "\t" << tests[i].name << std::endl;

            //print records
            for(int j = 0; j < tests[i].verboseLines.getSize(); j++){
                output << "\t\tRecord " << j << ": "<<
                          tests[i].verboseLines[j] <<std::endl;
            }
        }
    }

    output.close();

}
