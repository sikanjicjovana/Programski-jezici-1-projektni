#include "Node.h"

Node::Node(int nodeId, const string& nodeName) : nodeId(nodeId) , nodeName(nodeName) {}

int Node::getNodeId() const 
{
    return nodeId; 
}

const string& Node::getNodeName() const 
{
    return nodeName; 
}