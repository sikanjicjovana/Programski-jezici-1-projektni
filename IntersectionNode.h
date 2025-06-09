#pragma once
#include <vector>
#include "Link.h"

class IntersectionNode : public Node
{
    private:
        int maxVehicles;
        int currentNumOfVehicles;
        vector<Link> links;

    public:
        IntersectionNode( int nodeId, const string& nodeName, int maxVehicles);

        int getMaxVehicles() const;
        int getCurrentNumOfVehicles() const;
        const vector<Link>& getLinks() const;
        
        void printLinks(ofstream& file) const;

        void addLink(const Link& link);

        bool doesLinkExist(const PathNode& sourceNode, const PathNode& targetNode) const;
        
        const string type() const override;

        void printInfo() const override;

        void serializeNode(ofstream& file) const override;

        bool isNodeFull();

        void decreaseNumOfCurrVeh();
        
        void increaseNumOfCurrVeh();
};