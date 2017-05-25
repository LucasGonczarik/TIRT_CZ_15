/*
 * MMPPGenerator.cpp
 *
 *  Created on: May 25, 2017
 *      Author: lucas
 */

#include "MMPPGenerator.h"


MMPPGenerator::MMPPGenerator() {
    // TODO Auto-generated constructor stub
}

MMPPGenerator::~MMPPGenerator() {
    // TODO Auto-generated destructor stub
}

// register module class with OMNeT++je
Define_Module(MMPPGenerator);

void MMPPGenerator::initialize() {
    //0 -> first, ...
    actualState = 0;
    //counted 1,2,3...
    numberOfStates = 3;
    //vector 4ever FCK pointer arrays!
    matrix = vector<vector<double>>(numberOfStates, vector<double>(numberOfStates));
    lambdas = vector<double>(numberOfStates);
    generateLambdas();

}

void MMPPGenerator::generateLambdas(){
    //initialize generators lambdas
    for(int i=0; i<numberOfStates; i++) {
        lambdas[i] = uniform(0, 1);
    }
}

void MMPPGenerator::normalize(double &first, double &second, double &third){
    double sum = first + second + third;
    first /= sum;
    second /= sum;
    third /= sum;
}

void MMPPGenerator::generateMarkovMatrix(){
    for(int i=0; i < numberOfStates; i++){
        double previousPropability = uniform(0, 1);
        double stayPropability = uniform(0, 1);
        double nextPropability = uniform(0, 1);

        normalize(previousPropability, stayPropability, nextPropability);

        matrix[i][previousPropabilityIndex] = previousPropability;
        matrix[i][stayPropabilityIndex] = previousPropability;
        matrix[i][nextPropabilityIndex] = previousPropability;
        //TODO add case when first and last element
    }
}

void MMPPGenerator::printMarkovMatrix(){
    for (int i = 0; i < numberOfStates; i++){
        for (int j = 0; j < numberOfStates; j++){
            cout << matrix[i][j];
        }
        cout << "\n";
    }
}

int MMPPGenerator::getStayPropability(){
    return matrix[actualState][stayPropabilityIndex];
}

int MMPPGenerator::getGoToNextPropability(){
    return matrix[actualState][nextPropabilityIndex];
}

int MMPPGenerator::getGoToPreviousPropability(){
    return matrix[actualState][previousPropabilityIndex];
}

int MMPPGenerator::chooseNextState(){
    //check if cannot stay in state
    double actionValue =((double)rand() / (double)RAND_MAX);
    //if cannot stay
    double stayPropability = getStayPropability();
    if(actionValue > getStayPropability()){
        if(actionValue < stayPropability + getGoToNextPropability()){
            return actualState < numberOfStates ? actualState+1 : 0;
        }
        else{
            return actualState > 0 ? actualState-1 : 0;
        }
    }
    return actualState;
}

double MMPPGenerator::getDelay() {
    int delay = poisson(lambdas[actualState]);
    actualState = chooseNextState();
    cout << "Changed state to" << actualState << "\n";
    return delay;
}
