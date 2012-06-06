/*
 * Drr.cc
 *
 *  Created on: May 12, 2012
 *      Author: Mithileysh
 */

#include "cdrr.h"

namespace drr {

Define_Module(Cdrr);

Cdrr::Cdrr()
{
//    queues = NULL;
//    numQueues = NULL;
}

Cdrr::~Cdrr()
{
    for (int i=0; i<numQueues; i++)
    {
        delete queues[i];
    }
}

void Cdrr::initialize()
{

    frameCapacity = par("frameCapacity");
    numQueues = par("numQueues");
    meanRate = par("meanRate"); // in bps
    peakRate = par("peakRate"); // in bps
    quantum = 500;
    deficitcounter = 0;
    flowcount = 0;

    outGate = gate("out");

    for (int i=0; i<numQueues; i++)
    {
        char buf[32];
        sprintf(buf, "queue-%d", i);
        queues[i] = new cQueue(buf);
    }

    // state: CDRR scheduler
    currentQueueIndex = 0;
}

void Cdrr::handleMessage(cMessage *msg)
{
    for (int i = 0; i < numQueues; i++) {
		queues[i]->getLength(); // take into account the frames/packets already in queues
	}

        //int queueIndex = msg->getKind();    // message kind carries a queue index

        int pktLength = (check_and_cast<cPacket *>(msg))->getBitLength();

        if (deficitcounter <= pktLength)
        {
            cMessage *msg = dequeue();
            if (msg != NULL)
            {
                sendOut(msg);
            }
            else
            {
                error("%s::handleMessage: Error in deficit round-robin scheduling", getFullPath().c_str());
            }
    }
    else
    {   // a frame arrives
        int queueIndex;
       cQueue *queue = queues[queueIndex];

// DEBUG
        ASSERT(pktLength > 0);
// DEBUG
        if (queue->isEmpty())
          {
            currentQueueIndex = queueIndex;
            sendOut(msg);
           }
                else
                {
 //                 cMessage *msg = enqueue();
                	bool enqueue (cMessage*);
                 }
    }
}

bool Cdrr::enqueue(cMessage *msg)
{
    int queueIndex;
    cQueue *queue = queues[queueIndex];

    if (frameCapacity && queue->length() >= frameCapacity)
    {
        EV << "Queue " << queueIndex << " full, dropping packet.\n";
        delete msg;
        return true;
    }
    else
    {
        queue->insert(msg);
        return false;
    }
}

cMessage *Cdrr::dequeue()
 {
	bool found = false;
	int startQueueIndex = (currentQueueIndex + 1) % numQueues; // search from the next queue for a frame to transmit
	for (int i = 0; i < numQueues; i++) {
		currentQueueIndex = (i + startQueueIndex) % numQueues;
		found = true;

		cMessage *msg = (cMessage *) queues[currentQueueIndex]->pop();

		// TO DO: update statistics

		// conformity processing for the HOL frame
		if (queues[i]->isEmpty()) {
			msgServiced = NULL;
			deficitcounter = 0;
		} else {
			deficitcounter = quantum + deficitcounter;
			int pktLength = (check_and_cast<cPacket *>(
					queues[currentQueueIndex]->front()))->getBitLength();

			while (deficitcounter > 0) {
				if (pktLength <= deficitcounter) {
					msgServiced = msg;
					deficitcounter = deficitcounter - pktLength;
					EV << "Completed Service of" << msg->getName() << endl;
					send(msg, "out", msg->getKind());
					break;
					if (found == false) {
						found = true;
						currentQueueIndex = true;
					}
				}
			}
		}
	}
}

void Cdrr::sendOut(cMessage *msg)
{
	send(msg, outGate);
}

void Cdrr::finish()
{
}

};

