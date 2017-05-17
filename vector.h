//Wesley Ellington
//CSE 2341, Fall 2016
#ifndef DSVector_H
#define DSVector_H
#define DEBUG false

#include <iostream>
#include <cstring>
#include "DSString.h"



template <class T>

class DSVector{
    private:
        //number of elements stored in DSVector
        int size;

        //initalized to 10, uses 1.5 growth scheme
        int capacity;

        //indicates if vector is sorted
        bool sorted;

        void resize(){
            grow();
        }

    public:

        //actual array of templated type objects
        T * array;

        //default constuctor

        DSVector<T>(){
            if (DEBUG) std::cout << "Default Vector Constructor Called" << std::endl;
            size = 0;
            capacity = 10;
            //initialize to size ten, can be changed
            array = new T[capacity];
            sorted = false;
        }

        //create DSVector using type pointer to array and size
        DSVector<T>(T * inArray, int newSize){
            if (DEBUG) std::cout << "resize constructor called" << std::endl;
            this->sorted = false;
            this->size = 0;
            this->capacity = 10;
            this->array = new T[capacity];

            //grow to fit size needed
            while(newSize > this->capacity){
                this->grow();
            }

            //copy items
            for(int i = 0; i < newSize; i ++){
                this->array[i] = inArray[i];
                size++;
            }
        }
        //copy constructor for DSVector input
        DSVector<T>(const DSVector<T> & inDSVector){
            if (DEBUG) std::cout << "Copy Constructor Called" << std::endl;
            this->sorted = false;
            this->capacity = 10;
            this->size = 0;

            //initializes at cap 10, solves destructor errors.
            this->array = new T[10];
            while(inDSVector.size >= this->capacity){
                //increases capacity of DSVector's array untill large
                //enough to hold requested amo
                this->grow();
            }

            //copy over items in order
            for(int i = 0; i < inDSVector.size; i ++){
                //std::cout << i <<std::endl;
                this->array[i] = inDSVector.array[i];

                //incrament size
                size ++;
            }
        }

        //create vector of given size
        DSVector<T>(const int inInt){
            this->sorted = false;
            this->capacity = inInt;
            this->size = 0;
            this->array =  new T[inInt];
        }

        //add item to end
        void add(const T inObj){
            this->append(inObj);
        }

        //add item at index
        void add(const T inObj, int index){
            this->sorted = false;

            //resize if needed
            if(this->size + 1>= this->capacity){
                grow();
            }

            //create new array
            T * newArray = new T[this->capacity];

            //copy items upto index
            for(int i = 0; i < index; i++){
                newArray[i] = this->array[i];
            }

            //insert new item
            newArray[index] = inObj;

            //copy items after index into new
            for(int i = index + 1; i < this->size +1; i++){
                newArray[i] = this->array[i - 1];
            }

            //set size
            this->size = this->size + 1;
            //delete old array
            delete[] this->array;
            this->array = newArray;

        }

        T & get(int index){
            return this->array[index];
        }

        // sets value of a given index
        void setElement(int i, T val){
            this->sorted = false;
            this->array[i] = val;
        }

        // assignment operator
        DSVector<T> & operator=(const DSVector<T> & inDSVector){
                if (DEBUG) std::cout << "Vector Assignment Operator Called " << std::endl;

                this->sorted = false;
                this->size = inDSVector.size;
                this->capacity = inDSVector.capacity;

                if (DEBUG) std::cout << "invector cap: " <<inDSVector.capacity <<std::endl;

                //delete[] this->array; //clears old array values
                delete[] this->array;

                //initialize at size of source vec
                T * tmparray = new T[this->capacity ];

                for(int i = 0; i < inDSVector.size; i ++){
                    if (DEBUG) std::cout << "copying to dest: " << i << std::endl;
                    //if (DEBUG) std::cout << inDSVector.array[i];
                    tmparray[i] = inDSVector.array[i];
                 }

            this->array = tmparray;

            return *this;
        }

        //allows access to items by index
        T & operator[](int index){
            return this->array[index];
        }

        //equality operator
        bool operator==(const DSVector<T> & inDSVector){
           //edge case for when both DSVectors are empty
           if(inDSVector.size == 0 && this->size == 0){
               //returns true if both sizes are zero; implies empty
               return true;
           }

           //check if DSVectors are same size
           else if(inDSVector.size == this->size){
               //check if every term matches
               for(int i = 0; i < this->size; i ++){
                   if (DEBUG) std::cout << this->array[i] << " : " << inDSVector.array[i] << std::endl;
                   if(!(this->array[i] == inDSVector.array[i])){
                       return false;
                   }

               //return true only if every value is equal and length is equal
               return true;

               }
           }

           else{
               return false;
           }

           //return false if any issues occur
           return false;
        }

        bool operator!=(const DSVector<T> & inDSVector){
            if (DEBUG) std::cout << "inequality called" << std::endl;
            return !(*this == inDSVector);
        }

        // not operator
        bool operator!(){
            if(this->size != 0){
                return true;
            }

            else{
                return false;
            }
        }

        //adds item to end of vector
        DSVector<T>& operator+=(T inObj){
            this->append(inObj);
            return *this;
        }


        // allows for growth and transfer of DSVectors
        void grow(){
            if (DEBUG) std::cout << "Vector Grow Called on length of:"<< this->size <<std::endl;
            int newCapacity;
            T * newArray;

            newCapacity = int(1.5 * this->capacity);

            //creates new destination array
            newArray = new T[newCapacity];

            for(int i = 0 ; i < this->size; i++){
                if (DEBUG) std::cout << "moving index: " << i << std::endl;
                newArray[i] = this->array[i];
            }

            //clears old array allocation
            delete[] this->array;    //add last item to vector

            //assigns this pointer to new array location
            this->array = newArray;
            this->capacity = newCapacity;
        }

        //appends element onto end of array, resizes if neccesary
        void append( T  val){
            this->sorted = false;
            int newSize = this->size + 1;
            if(newSize > this->capacity){
                grow();
            }

            //sets new value
            this->array[newSize - 1] = val;
            this->size = newSize;
        }

//        //appends element onto end of array, resizes if neccesary
//        void appendStr( DSString  val){

//            if(val.size() > 1)
//            {
//                this->sorted = false;
//                int newSize = this->size + 1;
//                if(newSize > this->capacity){
//                    grow();
//                }

//                //sets new value
//                this->array[newSize - 1] = val;
//                this->size = newSize;

//            }
//        }


        //destructor
        ~DSVector(){
            delete[] this->array;
        }


        //stream insertion (UNDEFIND BEHAVIOR FOR NON OVERLOADED TMPLTS)
        std::ostream& operator<< (std::ostream& outStream){
            //outStream << this->expPrint();
            return outStream;
        }

        // returns current DSVector size
        int getSize(){
            return this->size;
        }

        //dangerous, mostly for debug
        void setSize(int newSize){
            this->size = newSize;
        }

        //returns max capacity for DSVector
        int getCapacity(){
            return this->capacity;
        }

        void sort(){

            quicksort(this->array, 0, this->size - 1);

            this->sorted = true;
        }


        //partition array for sort
        int partition (T arr[], int low, int high){
            T pivot = arr[low];
            int left = low;

            //check pivot vs element in question
            for (int j = low + 1; j <= high; j++){
                if (arr[j] < pivot || arr[j] == pivot){
                    left++;
                    swap(arr[j], arr[left]);
                }
            }
            swap (arr[left] , arr[low]);
            return left;
        }


        //sort terms
        void quicksort(T A[], int low, int high){
            int part;
            //recursively calls sorts on partitions of self
            if (low < high){
                part = partition(A, low, high);
                quicksort(A, low, part-1);
                quicksort(A, part+1, high);
            }
        }

        //swaps two element of a DSVector
        void swap(T& posone, T& postwo){
            T temp = posone;
            posone = postwo;
            postwo = temp;
        }

        bool isSorted(){
            return this->sorted;
        }

        //check exsistance of item in vector
        bool exists(T & check){
            for(int i = 0; i < this->size; i ++){
                if(array[i] == check){
                    return true;
                }
            }
            return false;
        }

        //return first index of item in vector
        int find (T check){
            for(int i = 0; i < this->size; i ++){
                if(array[i] == check){
                    return i;
                }
            }
            return -1;
        }

        //deletes element and shifts items
        void deleteElement(int index){
            for(int i = 0; i < this->size; i ++){
                if(i >= index){
                    this->array[i] = this->array[i+1];
                }
            }

            this->size = this->size - 1;
        }

};



#endif // DSVector_H

