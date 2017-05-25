/*
 * PoisonGenerator.cpp
 *
 *  Created on: May 19, 2017
 *      Author: Marsel
 */

#include "PoissonGenerator.h"

PoissonGenerator::PoissonGenerator() {
    // TODO Auto-generated constructor stub

}

PoissonGenerator::~PoissonGenerator() {
    // TODO Auto-generated destructor stub
}

// register module class with OMNeT++
Define_Module(PoissonGenerator);

void PoissonGenerator::initialize() {
    lambda = par("lambda");
    BasicGenerator::initialize();
}

double PoissonGenerator::getDelay() {
    return poisson(lambda);
}
