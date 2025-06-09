#pragma once
#include "Node.h"

class PathNode : public Node
{
    private:
        double length;
        double maxSpeed;
        int maxVehicles;
        int currentNumOfVehicles;
    
    public:
        PathNode(int nodeId, const string& nodeName, double length, double maxSpeed, int maxVehicles);

        double getLength() const;
        double getMaxSpeed() const;
        int getMaxVehicles() const;
        int getCurrentNumOfVehicles() const;

        const string type() const override;
        
        void printInfo() const override;
        
        void serializeNode(ofstream& file) const override;
        
        bool isNodeFull(); 

        void decreaseNumOfCurrVeh();
        
        void increaseNumOfCurrVeh();
             
};