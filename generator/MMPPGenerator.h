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
    ~MMPPGenerator();
protected:
    virtual void initialize();
    virtual double getDelay();
private:
    const int previousPropabilityIndex = 0;
    const int stayPropabilityIndex = 1;
    const int nextPropabilityIndex = 2;

    int actualState;
    int numberOfStates;
    vector<double> lambdas;
    vector<vector<double>> matrix;

    int getStayPropability();
    int getGoToNextPropability();
    int getGoToPreviousPropability();
    int chooseNextState();
    void generateLambdas();
    void normalize(double&, double&, double&);
    void generateMarkovMatrix();
    void printMarkovMatrix();
};

#endif /* GENERATOR_MMPPGENERATOR_H_ */
