#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

class Node
{
    protected:
        int nodeId;
        string nodeName;

    public:
        virtual ~Node() = default;
        Node(int nodeId, const string& nodeName);

        int getNodeId() const;
        const string& getNodeName() const;

        virtual const string type() const = 0;
        virtual void printInfo() const = 0;     		
        virtual void serializeNode(ofstream& file) const = 0;
};