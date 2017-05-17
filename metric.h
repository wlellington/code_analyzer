#ifndef METRIC_H
#define METRIC_H
#include "DSString.h"
#include "vector.h"

//Abstract and base class for metric generation.
//See derived classes to implement new metrics


class absmetric
{
public:
    //name of Metric used
    DSString name;

    //score of specific metric
    double score;

    //weighting value for composite score output
    int weight;

    //vector of instances of score impactful values
    DSVector<DSString> verboseLines;

    //virtual score creation funtion
    virtual void createScore();

    absmetric();
};

class basemetric
{
public:
    //name of Metric used
    DSString name;

    //score of specific metric
    double score;

    //weighting value for composite score output
    int weight;

    //vector of instances of score impactful values
    DSVector<DSString> verboseLines;

    //virtual score creation funtion
    virtual void createScore(){
        this->name = DSString("BASE CLASS");
    }

    basemetric();
};


#endif // METRIC_H
