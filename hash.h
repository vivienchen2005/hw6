#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0}; //max length is 5
        //ex: 18 characters
        int first_group = k.length() % 6; // ex: first group - 0
        int total_groups = k.length() / 6; // ex: next groups - 3 groups of 6
        int w_index = 4 - total_groups + 1;
        //first (uneven) group
        //TO DO: case where k is empty? 
        if (first_group > 0) {
            w_index = 4 - total_groups;
            w[w_index] = letterDigitToNumber(k[0]);
            for (int i = 1; i < first_group; i++) {
                w[w_index] = w[w_index] * 36 + letterDigitToNumber(k[i]);
            }
            w_index++;
        }
        //remaining groups of 6x1
        for (int j = w_index; j <= 4; j++) {
            w[j] = letterDigitToNumber(k[first_group]);
            for (int i = first_group+1; i < first_group + 6; i++) {
                w[j] = w[j] * 36 + letterDigitToNumber(k[i]);
            }
            first_group = first_group + 6; 
        }

        return (rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lowercase_letter = tolower(letter);
        int value = (int)lowercase_letter - 97;
        if (value < 0) {
            value = value + 75;
        }
        return value;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
