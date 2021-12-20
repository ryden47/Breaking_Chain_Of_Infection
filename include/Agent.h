#ifndef AGENT_H_
#define AGENT_H_

#include "Session.h"

class Session;

class Agent{
public:
    Agent();

    virtual Agent * clone() const = 0;
    virtual void act(Session& session)=0;
    virtual ~Agent() = default;
};

class ContactTracer : public Agent{
public:
    ContactTracer();

    virtual Agent* clone() const;
    virtual void act(Session& session);
    virtual ~ContactTracer() = default;
};


class Virus : public Agent{
public:
    Virus(int nodeInd);

    virtual Agent* clone() const;
    virtual void act(Session& session);
    virtual ~Virus() = default;
private:
    const int nodeInd;
};

#endif