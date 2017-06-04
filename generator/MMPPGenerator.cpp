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


    lambdas[0] = par("lambda1");
    lambdas[1] = par("lambda2");
    lambdas[2] = par("lambda3");

    double p01 = 0;
    double p11 = par("p11");
    double p12 = par("p12");
    double p21 = par("p21");
    double p22 = par("p22");
    double p23 = par("p23");
    double p32 = par("p32");
    double p33 = par("p33");
    double p4 = 0;

    normalize(p01, p11, p12);
    normalize(p21, p22, p23);
    normalize(p32, p33, p4);


    matrix[0][PREVIOUS_PROBABILITY_INDEX] = 0;
    matrix[0][STAY_PROBABILITY_INDEX] = p11;
    matrix[0][NEXT_PROBABILITY_INDEX] = p12;
    matrix[1][PREVIOUS_PROBABILITY_INDEX] = p21;
    matrix[1][STAY_PROBABILITY_INDEX] = p22;
    matrix[1][NEXT_PROBABILITY_INDEX] = p23;
    matrix[2][PREVIOUS_PROBABILITY_INDEX] = p32;
    matrix[2][STAY_PROBABILITY_INDEX] = p33;
    matrix[2][NEXT_PROBABILITY_INDEX] = 0;

    //generateLambdas();
    //generateMarkovMatrix();

    printMarkovMatrix();
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
