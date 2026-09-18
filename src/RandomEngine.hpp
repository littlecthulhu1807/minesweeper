#ifndef RANDOMENGINE_H
#define RANDOMENGINE_H

#include<random>

class RandomEngine{

public:
    RandomEngine(){};
    ~RandomEngine(){};

    // Function that returns true based on a percentage chance (0 to 100)
    bool randomBool(int percentage){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        // Convert integer percentage (e.g., 10) to a double probability (0.10)
        double probability = percentage / 100.0;
        
        // std::bernoulli_distribution generates true/false based on the probability
        std::bernoulli_distribution distrib(probability);
        
        return distrib(gen);
    };
};

#endif