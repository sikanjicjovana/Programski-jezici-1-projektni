#include "IntersectionNode.h"

IntersectionNode::IntersectionNode( int nodeId, const string& nodeName, int maxVehicles)
    : Node(nodeId,nodeName) , maxVehicles(maxVehicles) { currentNumOfVehicles = 0;}

int IntersectionNode::getMaxVehicles() const 
{ 
    return maxVehicles; 
}

int IntersectionNode::getCurrentNumOfVehicles() const 
{
    return currentNumOfVehicles;
}

const vector<Link>& IntersectionNode::getLinks() const 
{ 
    return links; 
}
        
void IntersectionNode::printLinks(ofstream& file) const
{
    for(const auto& link : links)
    {
        link.serializeLink(file);
    }
}

void IntersectionNode::addLink(const Link& link)
{
    links.push_back(link);
}

bool IntersectionNode::doesLinkExist(const PathNode& sourceNode, const PathNode& targetNode) const
{
    for(const Link& link : links)
    {
        if(link.doesConnectNodes(&sourceNode, &targetNode))
            return true;
    }
    return false;
}
        
const string IntersectionNode::type() const 
{
    return "IntersectionNode";
}

void IntersectionNode::printInfo() const 
{
    cout << "  Tip cvora:  " << type() << "  Ime raskrsnice:  " << getNodeName() << "  Maksimalno vozila:  " << getMaxVehicles() << endl;
} 

void IntersectionNode::serializeNode(ofstream& file) const 
{
    file << "IntersectionNode " << getNodeId() << " " << getNodeName() << " " << getMaxVehicles() << endl;
}

bool IntersectionNode::isNodeFull()
{
    return currentNumOfVehicles >= maxVehicles;
}

void IntersectionNode::decreaseNumOfCurrVeh()
{
    if(currentNumOfVehicles > 0)
        currentNumOfVehicles--;
}

void IntersectionNode::increaseNumOfCurrVeh()
{
    currentNumOfVehicles++;
}