#include "TrafficGraph.h"

TrafficGraph::TrafficGraph(int size)
{
    numNodes = 0;
    capacity = size;

    nodes.resize(size);
    for(int i = 0;  i < size; i++)
        nodes[i] = NULL;

    marks.resize(size);

    int rows = size;
    int columns = size;
    ajdMatrix.resize(rows, vector<double>(columns,0.0));
}

int TrafficGraph::getNumNodes() const 
{ 
    return numNodes; 
}

const vector<Node*>& TrafficGraph::getNodes() const 
{ 
    return nodes; 
}

bool TrafficGraph::isEmpty()
{
    if(numNodes == 0)
        return true;
    else
        return false;
}

bool TrafficGraph::isFull()
{
    if(numNodes == capacity)
        return true;
    else
        return false;
}

void TrafficGraph::addNode(Node* newNode)
{
    nodes[numNodes] = newNode;
    for(int i = 0; i < capacity; i++)
    {
        ajdMatrix[numNodes][i] = NULL_EDGE;
        ajdMatrix[i][numNodes] = NULL_EDGE;
    }
    numNodes++;
}
        
bool TrafficGraph::isConnectable(Node* node1, Node* node2)
{
    string type1 = node1->type();
    string type2 = node2->type();
    if( (type1 == "LocationNode" && type2 == "LocationNode") || (type1 == "PathNode" && type2 == "PathNode") || (type1 == "IntersectionNode" && type2 == "IntersectionNode") ||
        (type1 == "LocationNode" && type2 == "IntersectionNode") || (type1 == "IntersectionNode" && type2 == "LocationNode") )
            return false;
        else
            return true;
}

void TrafficGraph::connectNodes(Node* node1, Node* node2)
{
    if(isConnectable(node1,node2))
    {
        int fromId = node1->getNodeId();
        int toId = node2->getNodeId();
        ajdMatrix[fromId][toId] = 1;
    }
}

Node* TrafficGraph::getNodeById(int idNode)
{
    for(Node* node : nodes)
    {
        if(node->getNodeId() == idNode)
            return node;
    }
    return nullptr;
}

//dfs obilazak u kom upisuje cvorove u fajl + na konzolu

void TrafficGraph::DFS(ofstream& file, Node* node)
{
    int idx, idx2;
    if(node == nullptr) return;
    node->printInfo();
    node->serializeNode(file);
    idx = node->getNodeId();
    marks[idx] = true;

    for(int i = 0; i < numNodes; i++)
    {
        idx2 = nodes[i]->getNodeId();
        if(ajdMatrix[idx][idx2] != NULL_EDGE && !marks[idx2])
        {
            DFS(file,nodes[i]);
        }
    }
}

void TrafficGraph::serializeGraph(const string& filename)
{
    ofstream file(filename);
    if(file.is_open())
    {
        file << capacity << endl;
        for(const auto& row : ajdMatrix)
        {
            for(double val : row)
            file << val << " ";
            file << "\n";
        }
        file << "\n";
        DFS(file,nodes[0]);

        vector<IntersectionNode*> intersections;
        for(const auto& node : nodes)
        {
            IntersectionNode* intersection = dynamic_cast<IntersectionNode*>(node);
            if(intersection != nullptr)
                intersections.push_back(intersection);    
        }
                
        for(const auto& intersection : intersections)
        {
            file << intersection->getNodeName() << endl;
            intersection->printLinks(file);
        }
    }
}

bool TrafficGraph::isOnlyOneWord(const string& str)
{
    bool hasSpace = false;
    for(char c : str)
    {
        if(isspace(c))
        {
            if(hasSpace)
                return false;
        }   
        hasSpace = true;
    }
    return true;
}
        
TrafficGraph TrafficGraph::deserializeGraph(const string& filename)
{
    ifstream file(filename);
    if(file.is_open())
    {
        string line;
        int numNodes;
        getline(file,line);
        istringstream iss(line);
        iss >> numNodes;

        this->numNodes = numNodes;

        vector< vector<double> > ajdMatrix;
        for(int i = 0; i < numNodes; i++)
        {
            getline(file,line);
            istringstream iss(line);
            vector<double> row;
            int val;
            while(iss >> val)
            {
                row.push_back(val);
            }
            ajdMatrix.push_back(row);
        }

        int counter = 0;
        for(int i = 0; i < ajdMatrix.size(); i++)
        {
            vector<double> newRow;
            for(int j = 0; j < ajdMatrix[i].size(); j++)
            {
                newRow.push_back(ajdMatrix[i][j]);
            }
            this->ajdMatrix[counter] = newRow;
            counter++;
        }
                
        getline(file,line);
        getline(file,line);

        vector<Node*> nodes;
                
        do
        {
            if(!isOnlyOneWord(line))
            {
                istringstream iss(line);
                string nodeType;
                int nodeId;
                iss >> nodeType >> nodeId;

                if(nodeType == "PathNode")
                {
                    string nodeName;
                    double x, y, speed;
                    iss >> nodeName >> x >> y >> speed;
                    PathNode* pathNode = new PathNode(nodeId,nodeName,x,y,speed);
                    nodes.push_back(pathNode);
                }
                else if (nodeType == "IntersectionNode")
                {
                    string nodeName;
                    int maxVeh;
                    iss >> nodeName >> maxVeh;
                    IntersectionNode* intersectionNode = new IntersectionNode(nodeId,nodeName,maxVeh);
                    nodes.push_back(intersectionNode);
                }
                else if(nodeType == "LocationNode")
                {
                    string nodeName, type;
                    iss >> nodeName >> type;
                    LocationNode* locationNode = new LocationNode(nodeId,nodeName,type);
                    nodes.push_back(locationNode);
                }            
            }
        }while(!isOnlyOneWord(line) && getline(file,line));
                
        do
        {
            stringstream iss(line);
            string name;
            iss >> name;

            vector<Link> links;
            while(getline(file,line))
            {
                if(!isOnlyOneWord(line)) //ovde mora jos neka provjera 
                {
                    istringstream iss(line);
                    string inNodeName, outNodeName;
                    double length, maxSpeed;
                    iss >> inNodeName >> outNodeName >> length >> maxSpeed;

                    PathNode* inNode = nullptr;
                    PathNode* outNode = nullptr;
                    for( const auto& node : nodes)
                    {
                        if(node->getNodeName() == inNodeName)
                            inNode = dynamic_cast<PathNode*>(node);
                        if(node->getNodeName() == outNodeName)
                            outNode = dynamic_cast<PathNode*>(node);
                    }
                    links.push_back(Link(inNode,outNode,length,maxSpeed)); 
                }
                else
                {
                    for(const auto& node : nodes)
                    {
                        if(node->getNodeName() == name)
                        {
                            for(const auto& link : links)
                            {
                                dynamic_cast<IntersectionNode*>(node)->addLink(link);
                                break;
                            }
                        }
                    }        
                    name = line;
                }    
            }
        } while(!file.eof());

        int tmp = 0;
        for(const auto& node : nodes)
        {
            this->nodes[tmp] = node;
            tmp++;
        }
    }
    return *this;
}

void TrafficGraph::initT(vector< vector<int> >& t)
{
    for(int i = 0; i <= numNodes; i++)
    {
        for(int j = 0; j <= numNodes; j++)
        {
            if( i == j || ajdMatrix[i][j] == NULL_EDGE)
            {
                t[i][j] = -1;
            }
            else
            {
                t[i][j] = i;
            }
        }
    }
}

//trebalo bi da od ajdMatrix koja je netezinska napravi tezinsku i to tako da tezina grane predstavlja duzinu puta iz te veze

void TrafficGraph::initLengthMatrix(vector< vector<double> >& lengthMatrix)
{
    for(int i = 0; i <= numNodes; i++)
    {
        for(int j = 0; j <= numNodes; j++)
        {
            if(i == j)
            {
                lengthMatrix[i][j] = 0;
            }
            else if(ajdMatrix[i][j] != 0)
            {
                double tmpLength;
                for(auto& node : nodes)
                {
                    if( node != nullptr && node->getNodeId() == i && node->type() == "PathNode")
                    {
                        tmpLength = dynamic_cast<PathNode*>(node)->getLength();
                    }
                    else if(node != nullptr && node->getNodeId() == j && node->type() == "PathNode")
                    {
                        tmpLength = dynamic_cast<PathNode*>(node)->getLength();
                    }
                }
                lengthMatrix[i][j] = tmpLength;
            }
            else
            {
                lengthMatrix[i][j] = INFINITY;
            }
        }
    }
}

void TrafficGraph::floyd(vector< vector<int> >& t, vector< vector<double> >& lengthMatrix)
{
    for(int k = 0; k <= numNodes; k++)
        for(int j = 0; j <= numNodes; j++)
            for(int i = 0; i <= numNodes; i++)
                if ( lengthMatrix[i][k] != INFINITY && lengthMatrix[k][j] != INFINITY && lengthMatrix[i][j] > lengthMatrix[i][k] + lengthMatrix[k][j])
                {
                    lengthMatrix[i][j] = lengthMatrix[i][k] + lengthMatrix[k][j];
                    t[i][j] = t[k][j];
                }   
}
    
void TrafficGraph::writePath(int i, int j, vector< vector<int> > t)
{
    if(i == j)
    {
        cout << i << " ";
        return; 
    }
    else if(t[i][j] == -1)
    {
        cout << "Nema putanje." << endl;
        return;
    }
    else
    {
        writePath(i,t[i][j],t);
        cout << j << " ";    
    }
}

//da sacuvam putanju kretanja vozila

void TrafficGraph::savePath(int i, int j, vector< vector<int> > t,vector<pair<int,int>>& path)
{
    if(i == j)
    {
        path.push_back({i,0});
        return;
    }
    else if(t[i][j] == -1)
    {
        return;
    }
    else
    {
        savePath(i,t[i][j],t,path);
        path.push_back({j,0});
    }
}