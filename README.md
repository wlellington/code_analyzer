# CodeAnalyzer
Fall 2016 Data Structures Final Project

## Contributors 
Wesley Ellington 	45487212
Seung Ki Lee      35460312

## Overview


## Design Concerns
The first issue we must deal with is parsing out the codebase in question. To do this, we will use two methods: line by line parsing and tokenization, and some sort of Abstract Syntax Tree generation. The first allows us to look into the commenting scheme of the program, as well as analyze style consistency in indentation and punctuation placement. The second, and perhaps more insightful, will grant us access to the structure of the code itself, making it easier to evaluate logic control and repeated code blocks. To do this, we will create multiple parse structures that will make certain aspects of the code more evident based on their format, giving us the power to use them individually or in concert to ascertain the impact of certain coding details.

One of our main concerns in this task will be expandability. With this in mind, we have decided to use the polymorphic capacities of C++ to our advantage. We will create an abstract base class that will serve as a placeholder and draw from it to create multiple subclasses, one for each metric we choose. The base class shall contain two attributes, a double that will represent the score of the code on that given metric, an int that represents a weighting value for use in creating a compound score, and a vector of well formatted strings to give verbose output should it be requested. Each metric will have its own member functions for creating its results and will have access to the parsed data created by the parsers.

By keeping this functionality in mind, this code system will be easily expandable and adding new tests require a one to two line edit to the code.

## Metrics
There are many types of analysis we can run, but for the sake of this project, there are two main areas of concern. The first pertains to the readability of the code in question and the style used to create it. This is important to us as it lends the codebase to better maintainability and makes it accessible to other users. Here, we look at the non-compilation-impactful aspects such as whitespace, indentation, bracket and end bracket consistency, and other like topics.


Second, we turn to the more impactful, but more complicated aspects of the code. It is our goal to analyze the high level function of the code as well, but must create much more complex metrics to do so. For example, we would like to detect repeated (or similar ) blocks of code to point out that a helper function would be of better benefit to the situation. Our hope at this point is to create a compiler-like AST (Abstract Syntax Tree) and use some fuzzy logic to match and search patterns we find in the tree.


At this moment we plan to implement the following:

### Whitespacing consistency and style
Are all indentations standard and consistent

Does the user use the same chars for spacing (tabs vs spaces)

Inline spacing between types and pointers
### Bracket consistency and style
Is the programmer using brackets on the same or next line after starting a block

Are there brackets in one line if statements
### Comment line to LoC ratio
Ratio of lines of code to lines of comment

Point out inline comments and recommend making them above line
### Repeated and Similar Block detection
If similar functionality is discovered (copy pasted blocks)

Locate blocks if they exist
### Static Function Depth analyzer
Create control tree for non recursive function calls

Find maximum function call depth
## Other Suggested Tests

### Access management
Are non-publicly needed variables/functions private

Are there functions that need protection 
### Function Parameter Complexity
Are functions readable and understandable without great explanation
### Rule of Big 3 Verification for dynamic memory
Assignment operator existence

Copy constructor existence

Constructor/destructor
### Cyclomatic Complexity

All are subject to change

## Implementation
We did a thing

## Areas of Research
Below are some of the resources that have been looked into for inclusion. If a new resource is found, please leave a link below and include a brief description.
### Elsa Parser
http://scottmcpeak.com/elkhound/sources/elsa/

A parser used to create AST’s from a code base

Very dependent on other codes for building
### CLang
http://clang.llvm.org/docs/IntroductionToTheClangAST.html

Clang (a general C++ compiler, often used in OSX)

Has a very simple and understandable AST structure that could be useful

Would require building a CLang back end and may prove not worth effort
### Boost-Spirit
http://boost-spirit.com/home/

A parser built for customization of user where all rules can be defined by the programmer, would allow for high specification and detailed searching
### g++
http://www.codesynthesis.com/~boris/blog/2010/05/03/parsing-cxx-with-gcc-plugin-part-1/

The GNU compiler, potentially useful for AST creation with help from plugins

Not much documentation on this usage, output files are unreadable to humans
