#include "LocationNode.h"

LocationNode::LocationNode(int nodeId, const string& locationName, const string& typeName) : Node(nodeId,locationName) , typeName(typeName) {}

const string& LocationNode::getTypeName() const 
{ 
    return typeName; 
}

const string LocationNode::type() const 
{
    return "LocationNode";
} 

void LocationNode::printInfo() const
{
    cout << "  Tip cvora:  " << type() << "  Ime lokacije:  " << getNodeName() << endl;
} 

void LocationNode::serializeNode(ofstream& file)const
{
    file << "LocationNode " << getNodeId() << " " << getNodeName() << " "<< getTypeName() << endl;
}