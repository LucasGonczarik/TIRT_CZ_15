/*
 * ParetoGenerator.cpp
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#include "ParetoGenerator.h"

ParetoGenerator::ParetoGenerator() {
}

ParetoGenerator::~ParetoGenerator() {
}

// register module class with OMNeT++
Define_Module(ParetoGenerator);

void ParetoGenerator::initialize() {
    a = par("a");
    b = par("b");
    BasicGenerator::initialize();
}

double ParetoGenerator::getDelay() {
    return pareto_shifted(5, 5, 5, 0);
}

