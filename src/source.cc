/*
 * source.cc
 *
 *  Created on: Apr 22, 2012
 *      Author: Mithileysh
 */
#include <omnetpp.h>


namespace drr {

/**
 * Generates messages or jobs; see NED file for more info.
 */
class Source : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent;
    long srcAddress;

  public:
     Source();
     virtual ~Source();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    //virtual void cMessage::setKind();
};

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = NULL;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
	srcAddress = par("srcAddress").longValue();
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
}

void Source::handleMessage(cMessage *msg)
{
	//int sourceAddress = gate("input")->getIndex();
//int source;
//int destination;
//	int getId();
//	int getIndex();

	ASSERT(msg==sendMessageEvent);
	//msg->getKind();
	//msg->setKind();
	cMessage *job = new cMessage("job");
	job->setKind(srcAddress);
	//void setKind(short k);
	//msg->getId();
	//short getKind() const;
	send(job, "out");
	//cMessage *msg = sendMessageEvent;
	//msg->getId() << endl;
	//send(msg, "out");
	//}

	scheduleAt(simTime() + par("sendIaTime").doubleValue(), sendMessageEvent);
}

}; //namespace







