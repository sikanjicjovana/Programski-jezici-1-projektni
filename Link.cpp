#include "Link.h"

Link::Link(PathNode* inNode, PathNode* outNode, double length, double maxSpeed)
    : inNode(inNode) , outNode(outNode) , length(length) , maxSpeed(maxSpeed) {}

PathNode* Link::getInNode() const 
{
    return inNode;
}

PathNode* Link::getOutNode() const 
{ 
    return outNode; 
}

double Link::getLength() const 
{ 
    return length; 
}

double Link::getMaxSpeed() const 
{ 
    return maxSpeed; 
}

bool Link::doesConnectNodes(const PathNode* sourceNode, const PathNode* targetNode) const
{
    return (inNode == sourceNode) && (outNode == targetNode);
}

void Link::serializeLink(ofstream& file) const
{
    file << getInNode()->getNodeName() << " " << getOutNode()->getNodeName() << " " << getLength() << " " << getMaxSpeed() << endl;
}