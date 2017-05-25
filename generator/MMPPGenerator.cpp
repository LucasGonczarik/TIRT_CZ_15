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
    generateMarkovMatrix();
    generateLambdas();
    BasicGenerator::initialize();
}

void MMPPGenerator::generateLambdas(){
    //initialize generators lambdas
    for(int i=0; i<numberOfStates; i++) {
        lambdas[i] = uniform(0, 1);
    }
}

void MMPPGenerator::normalize(double &first, double &second, double &third){
    double sum = first + second + third;
    first = (double)first/sum;
    second = (double)second/sum;
    third = (double)third/sum;
}

void MMPPGenerator::generateMarkovMatrix(){
    for(int i=0; i < numberOfStates; i++){
        //uniform is unifrom random in omnetpp library
        double previousPropability = uniform(0,1);
        double stayPropability = uniform(0,1);
        double nextPropability = uniform(0,1);

        //first cannot go back
        if(i==0){
            previousPropability = 0;
        }
        //last cannot go further
        else if(i==numberOfStates-1){
            nextPropability = 0;
        }

        normalize(previousPropability, stayPropability, nextPropability);
        matrix[i][previousPropabilityIndex] = previousPropability;
        matrix[i][stayPropabilityIndex] = stayPropability;
        matrix[i][nextPropabilityIndex] = nextPropability;
    }
    printMarkovMatrix();
}

void MMPPGenerator::printMarkovMatrix(){
    for (int i = 0; i < numberOfStates; i++){
        for (int j = 0; j < numberOfStates; j++){
            EV << matrix[i][j] << " ";
        }
        EV << "\n";
    }
}

double MMPPGenerator::getGoToPreviousPropability(){
    return matrix[actualState][previousPropabilityIndex];
}

double MMPPGenerator::getStayPropability(){
    return matrix[actualState][stayPropabilityIndex];
}

double MMPPGenerator::getGoToNextPropability(){
    return matrix[actualState][nextPropabilityIndex];
}


int MMPPGenerator::chooseNextState(){
    //check if cannot stay in state
    double actionValue = uniform(0, 1);
    //if cannot stay
    double stayPropability = getStayPropability();
    if(actionValue > getStayPropability()){
        if(actionValue < stayPropability + getGoToNextPropability()){
            return actualState+1;
        }
        else{
            return actualState-1;
        }
    }
    return actualState;
}

double MMPPGenerator::getDelay() {
    int delay = poisson(lambdas[actualState]);
    EV << "MMPP returned: " << delay << "delay\n";
    actualState = chooseNextState();
    EV << "Next state will be: " << actualState << "\n";
    return delay;
}
