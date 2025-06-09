#include "PathNode.h"

PathNode::PathNode(int nodeId, const string& nodeName, double length, double maxSpeed, int maxVehicles) 
            : Node(nodeId,nodeName) , length(length) , maxSpeed(maxSpeed) , maxVehicles(maxVehicles) { currentNumOfVehicles = 0; }

double PathNode::getLength() const 
{ 
    return length;
}

double PathNode::getMaxSpeed() const 
{
    return maxSpeed; 
}

int PathNode::getMaxVehicles() const 
{ 
    return maxVehicles; 
}

int PathNode::getCurrentNumOfVehicles() const 
{
    return currentNumOfVehicles; 
}

const string PathNode::type() const 
{
    return "PathNode";
}

void PathNode::printInfo() const 
{
    cout << "  Tip cvora:  " << type() << "  Ime:  " << getNodeName() << "  Duzina:  " << getLength() << "  Maksimalna brzina:  " << getMaxSpeed() << "  Maksimalno vozila:  " << getMaxVehicles() << endl;
}

void PathNode::serializeNode(ofstream& file) const 
{
    file << "PathNode " << getNodeId() << " " << getNodeName() << " " << getLength() <<  " " << getMaxSpeed() << " " << getMaxVehicles() << endl;
}

bool PathNode::isNodeFull()
{
    return currentNumOfVehicles >= maxVehicles;
}

void PathNode::decreaseNumOfCurrVeh()
{
    if(currentNumOfVehicles > 0)
        currentNumOfVehicles--;
}

void PathNode::increaseNumOfCurrVeh()
{
    currentNumOfVehicles++;
}