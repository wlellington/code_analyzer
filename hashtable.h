#ifndef HASHTABLE
#define HASHTABLE

#include "hash_fun.h"
#include "DSString.h"

template <class K, class V>
class hashnode{
private:
    //key value pair
    K key;
    V value;
public:

    //base constructor
    hashnode(K key, V value) {
        this->key = key;
        this->value = value;
    }

    //mutators
    K getKey() {
        return key;
    }

    void setValue(V inValue){
        this->value = inValue;
    }

    V getValue() {
        return value;
    }
};


template <class K, class V>
class hashtable {
private:

    //array of pointers to node objects
    hashnode<K,V> **table;

    //size of table
    int size;

public:

    //creates integer hash
    int hashFcn(K key);

    //default constructor
    hashtable() {
        size = 128;
        table = new hashnode<K,V>*[size];
        for (int i = 0; i < size; i++){
            table[i] = nullptr;
        }
    }

    //construct table of desired size
    hashtable(int inSize){
        size = inSize;
        table = new hashnode<K,V>*[size];
        for (int i = 0; i < size; i++){
            table[i] = nullptr;
        }
    }

    //copy constructor
    hashtable(hashtable<K,V>& intable){
        size = intable.size;
        table = new hashnode<K,V>*[size];
        for (int i = 0; i < size; i++){
            if(intable.table[i] == nullptr){
                table[i] = nullptr;
            }
            else{
                table[i] = new hashnode<K,V>(intable.table[i]->getKey(),
                                        intable.table[i]->getValue());
            }
        }
    }

    //get value from key
    V get(K key) {

        //create hash for table size
        int hash = (hashFcn(key) % size);

        //chech for exsistance, if not at location, iterate
        while (table[hash] != nullptr && table[hash]->getKey() != key){
            hash = (hash + 1) % size;
        }

        // if bucket is empty
        if (table[hash] == nullptr){
            return -1;
        }

        //return value if at location
        else{
            return table[hash]->getValue();
        }
    }

    //place new value into table
    void put(K key, V value) {

        //create initial hash
        int hash = (hashFcn(key) % size);

        //check exsistance, if not at location, iterate
        //if count exceeds number of elements in table, resize
        int count = 0;
        while (table[hash] != nullptr && table[hash]->getKey() != key){
            count++;

            if(count >= size){
                //std::cout << "RESIZE NEEDED" <<std::endl;
                resize();
                hash = (hashFcn(key) % size);
                count = 0;
            }

            else{
                hash = (hash + 1) % size;
            }

        }

        // if location is filled, clear
        if (table[hash] != nullptr){
            delete table[hash];
        }

        //set location
        table[hash] = new hashnode<K, V>(key, value);
    }

    //destructor
    ~hashtable() {

        //iterate over table
        for (int i = 0; i < size; i++){
              if (table[i] != nullptr){
                    //delete value at entry
                    delete table[i];
              }
        }

        //delete table
        delete[] table;
    }

    //upscales array if full
    void resize(){
        //create new table
        hashnode<K,V> ** tmpTable = new hashnode<K,V>*[size*2];

        //intitalize null ptrs
        for(int i = 0; i < size*2; i++){
            tmpTable[i] = nullptr;
        }

        //iterate over exsisting table, rehash every item
        for(int i = 0; i < size; i++ ){
            //creat placeholder hash
            K tmpKey = table[i]->getKey();
            int tmpHash = hashFcn(tmpKey) % (size*2);

            //assign item in hash table to location in new table
            tmpTable[tmpHash] = table[i];
        }

        //clean and update
        delete[] table;
        table = tmpTable;
        size = size*2;
    }
};


template<class K, class V>
int hashtable<K, V>::hashFcn(K key){
    return (int)std::hash<K>()(key);
}

//overloading function makes hashing much more reliable
template<>
inline int hashtable<DSString, DSString>::hashFcn(DSString key){
    int prox = 10;
    if(key.size() != 1){
        prox += key.strVal[0];
    }

    if(key.size() > 4){
        prox += key.strVal[4];
    }

    return (int)std::hash<int>()(prox);
}

template<>
inline int hashtable<DSString, DSVector<DSString>>::hashFcn(DSString key){
    int prox = 10;
    if(key.size() != 1){
        prox += key.strVal[0];
    }

    if(key.size() > 4){
        prox += key.strVal[4];
    }

    return (int)std::hash<int>()(prox);
}




#endif // HASHTABLE

