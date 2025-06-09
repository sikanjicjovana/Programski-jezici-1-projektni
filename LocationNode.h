#pragma once
#include "Node.h"

using namespace std;

class LocationNode : public Node
{
    private:
        string typeName;

    public:
        LocationNode(int nodeId, const string& locationName, const string& typeName);

        const string& getTypeName() const;

        const string type() const override;
         
        void printInfo() const override;
         
        void serializeNode(ofstream& file)const override;       
};