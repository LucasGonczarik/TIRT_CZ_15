/*
 * ParetoGenerator.h
 *
 *  Created on: 26.05.2017
 *      Author: dawhe
 */

#ifndef GENERATOR_PARETOGENERATOR_H_
#define GENERATOR_PARETOGENERATOR_H_

#include <omnetpp.h>
#include "BasicGenerator.h"

using namespace omnetpp;

class ParetoGenerator : public BasicGenerator {
    private:
        double a;
        double b;
        // default value of parameter can be set in *.ned representing this class instance file

    protected:
        virtual void initialize();
        virtual double getDelay();

    public:
        ParetoGenerator();
        virtual ~ParetoGenerator();
};

#endif /* GENERATOR_PARETOGENERATOR_H_ */
