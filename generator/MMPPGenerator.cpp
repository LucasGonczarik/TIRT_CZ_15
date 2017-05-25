/*
 * MMPPGenerator.cpp
 *
 *  Created on: May 25, 2017
 *      Author: lucas
 */

#include "MMPPGenerator.h"


MMPPGenerator::MMPPGenerator() {

}

MMPPGenerator::~MMPPGenerator() {

}

// register module class with OMNeT++je
Define_Module(MMPPGenerator);

void MMPPGenerator::initialize() {
    actualState = STARTING_STATE;
    numberOfStates = 3;
    matrix = vector<vector<double>>(numberOfStates, vector<double>(numberOfStates));
    lambdas = vector<double>(numberOfStates);

    generateLambdas();
    //uncomment to use static values
    //lambdas = {0.23, 1, 3};

    generateMarkovMatrix();
    //uncomment to use static values
    //matrix = {{0, 0.6, 0.4},{0.2, 0.4, 0.4},{0.4, 0.6, 0}};

    BasicGenerator::initialize();
}

void MMPPGenerator::generateLambdas(){
    //initialize generators lambdas
    for(int iterator=0; iterator<numberOfStates; iterator++) {
        lambdas[iterator] = uniform(0, MAX_LAMBDA);
        EV << "State " << iterator+1 << " lambda is: " << lambdas[iterator] << endl;
    }
}

void MMPPGenerator::normalize(double &first, double &second, double &third){
    double sum = first + second + third;
    first = (double)first/sum;
    second = (double)second/sum;
    third = (double)third/sum;
}

void MMPPGenerator::generateMarkovMatrix(){
    for(int iterator=0; iterator < numberOfStates; iterator++){
        //uniform is unifrom random in omnetpp library
        double previousPropability = uniform(0,1);
        double stayPropability = uniform(0,1);
        double nextPropability = uniform(0,1);

        //first cannot go back
        if(iterator==0){
            previousPropability = 0;
        }
        //last cannot go further
        else if(iterator==numberOfStates-1){
            nextPropability = 0;
        }

        normalize(previousPropability, stayPropability, nextPropability);
        matrix[iterator][PREVIOUS_PROBABILITY_INDEX] = previousPropability;
        matrix[iterator][STAY_PROBABILITY_INDEX] = stayPropability;
        matrix[iterator][NEXT_PROBABILITY_INDEX] = nextPropability;
    }
    printMarkovMatrix();
}

void MMPPGenerator::printMarkovMatrix(){
    for (int rowNumber = 0; rowNumber < numberOfStates; rowNumber++){
        EV << "[";
        for (int columnNumber = 0; columnNumber < numberOfStates; columnNumber++){
            EV << matrix[rowNumber][columnNumber] << " ";
        }
        EV << "]\n";
    }
}

double MMPPGenerator::getGoToPreviousPropability(){
    return matrix[actualState][PREVIOUS_PROBABILITY_INDEX];
}

double MMPPGenerator::getStayPropability(){
    return matrix[actualState][STAY_PROBABILITY_INDEX];
}

double MMPPGenerator::getGoToNextPropability(){
    return matrix[actualState][NEXT_PROBABILITY_INDEX];
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
    EV << "Actual state number is: " << actualState << "\n";
    EV << "MMPP returned: " << delay << "delay\n";
    actualState = chooseNextState();

    return delay;
}
