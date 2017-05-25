/*
 * MMPPGenerator.h
 *
 *  Created on: May 25, 2017
 *      Author: lucas
 */

#ifndef GENERATOR_MMPPGENERATOR_H_
#define GENERATOR_MMPPGENERATOR_H_

#include <vector>
#include <omnetpp.h>
#include "BasicGenerator.h"
#include <algorithm>

using namespace std;

class MMPPGenerator : public BasicGenerator{
public:
    MMPPGenerator();
    virtual ~MMPPGenerator();
protected:
    virtual void initialize();
    virtual double getDelay();
private:
    const int STARTING_STATE = 0;
    const double MAX_LAMBDA = 1;
    const int PREVIOUS_PROBABILITY_INDEX = 0;
    const int STAY_PROBABILITY_INDEX = 1;
    const int NEXT_PROBABILITY_INDEX = 2;

    int actualState;
    int numberOfStates;
    vector<double> lambdas;
    vector<vector<double>> matrix;

    double getStayPropability();
    double getGoToNextPropability();
    double getGoToPreviousPropability();
    int chooseNextState();
    void generateLambdas();
    void normalize(double&, double&, double&);
    void generateMarkovMatrix();
    void printMarkovMatrix();
};

#endif /* GENERATOR_MMPPGENERATOR_H_ */
