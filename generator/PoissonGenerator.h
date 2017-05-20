/*
 * PoissonGenerator.h
 *
 *  Created on: May 19, 2017
 *      Author: Marsel
 */

#ifndef GENERATOR_POISSONGENERATOR_H_
#define GENERATOR_POISSONGENERATOR_H_

#include <omnetpp.h>
#include "BasicGenerator.h"

using namespace omnetpp;

class PoissonGenerator : public BasicGenerator {
    private:
        double lambda;

    protected:
        virtual void initialize();
        virtual double getDelay();

    public:
        PoissonGenerator();
        virtual ~PoissonGenerator();
};

#endif /* GENERATOR_POISSONGENERATOR_H_ */
