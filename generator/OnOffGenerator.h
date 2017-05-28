/*
 * OnOffGenerator.h
 *
 *  Created on: 28.05.2017
 *      Author: Piotr
 */

#ifndef GENERATOR_ONOFFGENERATOR_H_
#define GENERATOR_ONOFFGENERATOR_H_

#include <omnetpp.h>
#include "BasicGenerator.h"

class OnOffGenerator: public BasicGenerator {
public:
    OnOffGenerator();
    virtual ~OnOffGenerator();
protected:
    virtual void initialize();
    virtual double getDelay();
    virtual bool canSendMessage();
private:
    double lambda;
    bool isOnModeActive;
};

#endif /* GENERATOR_ONOFFGENERATOR_H_ */
