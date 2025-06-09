#pragma once
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <utility>
#include "Node.h"
#include "Link.h"
#include "IntersectionNode.h"
#include "LocationNode.h"
#include "PathNode.h"

const int INFINITY = numeric_limits<int>::max();

class TrafficGraph
{
    private:
        static const int NULL_EDGE = 0;
        int numNodes;
        int capacity;
        vector<bool> marks;
        vector<Node*> nodes;
        vector< vector<double> > ajdMatrix;

    public:
        TrafficGraph(int size);

        int getNumNodes() const;

        const vector<Node*>& getNodes() const;

        bool isEmpty();

        bool isFull();

        void addNode(Node* newNode);
      
        bool isConnectable(Node* node1, Node* node2);

        void connectNodes(Node* node1, Node* node2);

        Node* getNodeById(int idNode);

        void DFS(ofstream& file, Node* node);

        void serializeGraph(const string& filename);

        bool isOnlyOneWord(const string& str);
        
        TrafficGraph deserializeGraph(const string& filename);

        void initT(vector< vector<int> >& t);

        void initLengthMatrix(vector< vector<double> >& lengthMatrix);

        void floyd(vector< vector<int> >& t, vector< vector<double> >& lengthMatrix);

        void writePath(int i, int j, vector< vector<int> > t);

        void savePath(int i, int j, vector< vector<int> > t,vector<pair<int,int>>& path);
};
