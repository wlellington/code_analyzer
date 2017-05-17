# Static Code Analyzer
Fall 2016 Data Structures Final Project

## Contributors 
Wesley Ellington

Seung Ki Lee

## Overview
The main goal of this project is to help developers have a better idea what the quality of their C or C++ code is after it is completed. It generates a score based on a number of metrics we believe indicates good code quality, the details of which can be found later in this document. It can be run on entire directory and will recursivly crawl through its subdirectories and give metrics on all C and C++ files it encounters. The score will be reported to the user in a composite number where a zero is perfect and higher numbers are less good. The user can also change the verbosity of the output to see exactly how each metric is being built and see the specific instances of each item that is looked at.

This analyzer will not do any tasks regarding compilation and assumes that code is syntactically correct. It should also be noted that exsessivly large codebases may cause issues at runtime. 

## Usage
This application was built to run in the QT environment on an Ubuntu system. It uses the qmake toolchain and is reliant on
that environment to run. The .pro files define the configurations needed to properly compile and run this tool. 

Once compiled, all that is required is for the user to supply a verbosity flag  or not (-v), the name of the directory they
wish to run analysis on, and the name of a file they wish to have their results save to. Along the way, a great deal of file I/O will take place, so it is to be expected that it may take some time to finish.

## Metrics

Each metric score is calculated individialy, weighted based on importance, and averaged to create the composite score.

### Comments to Lines of Code Ratio
This is a pretty standard metric that gives the user an idea of how much commenting they have been doing. It compares the
number of comments discovered in a file to the total number of lines in the file.

### Comment Quality
To better determine the quality of the comment, some simple language analytics are run based on the type of words found in the
comments. It compares the ratio of verbs, nouns, adjectives, and other parts of speach to determine how good the language used
is, and therefore how readable it is.

### Function and Variable naming
Here, our goal is to enforce some level of meaning in the naming of functions and variables for the sake of readability. It discorages short, abreviation heavy naming schemes and rewards those that use full words that are easy to understand.

### Function Size
It is considered good practice to split large tasks up into sets of smaller functions. In this metric, we report a score based
on the length of the functions discovered in the source code. 

### Delatation
This is a metric of our own design that attempts to quantify the "fan out" of a programs function calls. It looks for function
definitions and implementations and analyzes the number of calls made within each. Due to the complexity of C++ syntax, certain implicit calls, such as the [] operator, are ignored.

More information about all metrics can be found in the report file in this repository.

## License
In our experiance, tools of this sort offer themselves as great learning tools to those new to a language or subject. With
this in mind, we invite anyone who wishes to use our codes to better their own education to do so, but cite it whenever used.

This project is reliant on some custom data structures that should be recycleable for other applications should anyone want to
use them. They have been modified very slightly to better suit the needs of the project, but are still useful learning tools
should anyone want to use them. Read both their headers and implementation to understand their inner workings.

Additionally, should anyone want to create a new metric for use with this tool, they should look into the existing ones and 
the base class they they all inherit from. One of our main concerns was scalability, and we accomplished this by making all 
tests unique objects to be iterated over to form a complete score taking all tests into account.
