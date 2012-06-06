/*
 * cdrr.h
 *
 *  Created on: May 22, 2012
 *      Author: Mithileysh
 */

#ifndef CDRR_H_
#define CDRR_H_

#include <omnetpp.h>
#include <vector>

namespace drr {


class Cdrr : public cSimpleModule
{
	typedef std::vector<cQueue *> QueueVector;

protected:

    int frameCapacity;
    int numQueues;
    double meanRate;
    double peakRate;
    int quantum;
    int deficitcounter;
    int flowcount;

    int currentQueueIndex;

    QueueVector queues;

    cGate *outGate;

    cMessage *msgServiced;
    cMessage *endServiceMsg;

  public:
    Cdrr();
    virtual ~Cdrr();

  protected:
    virtual void initialize();

    virtual void handleMessage(cMessage *msg);

    virtual void arrival(cMessage *msg) {}

    virtual void finish();

    virtual bool enqueue(cMessage *msg);

    virtual cMessage *dequeue();

    virtual void sendOut(cMessage *msg);

};

}; //namespace


#endif /* CDRR_H_ */

