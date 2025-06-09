#pragma once
#include "PathNode.h"

class Link
{
    private:
        PathNode* inNode;
        PathNode* outNode;
        double length;
        double maxSpeed;
    
    public:
        Link(PathNode* inNode, PathNode* outNode, double length, double maxSpeed);
 
        PathNode* getInNode() const;
        PathNode* getOutNode() const;
        double getLength() const;
        double getMaxSpeed() const;

        bool doesConnectNodes(const PathNode* sourceNode, const PathNode* targetNode) const;

        void serializeLink(ofstream& file) const;
};