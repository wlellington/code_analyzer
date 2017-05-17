#include "metric.h"

basemetric::basemetric()
{
    this->score = 0;
    this->weight = 0;
    this->name = DSString("BASE METRIC");
    this->verboseLines.append(DSString("NO RECORDS FOR BASE"));
}

