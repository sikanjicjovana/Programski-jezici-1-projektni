#include "TrafficSimulation.h"

TrafficSimulation::TrafficSimulation(const TrafficGraph& graph, double duration, const std::unordered_map<int, std::vector<std::pair<int, int>>>& paths)
    : trafficGraph(graph), durationPerStep(duration), vehiclePaths(paths) {}

void TrafficSimulation::addVehicle(const Vehicle& vehicle) 
{
    vehicles.push_back(vehicle);
}

Vehicle TrafficSimulation::findVehicleById(int id) const
{
    for (const auto& vehicle : vehicles) 
    {
        if (vehicle.getVehicleID() == id)
        {
            return vehicle;
        }
    }
    throw runtime_error("Vozilo sa datim ID-jem nije pronadjeno.");
}

void TrafficSimulation::startSimulation()
{
    tmpSimulationTimes.assign(vehiclePaths.size(),0.0);
    for(auto& pair : vehiclePaths)
    {
        vector<std::pair<int,int>>& path = pair.second;
        if(!path.empty())
        {
            path[0].second = 1;
        }
        else
        {
            cout << "Vozilo nema definisanu putanju." << endl;
        }
    }
}

void TrafficSimulation::printVehicleLocations()
{
    for(const auto& pair : vehiclePaths)
    {
        int vehicleID = pair.first;
        Vehicle vehicle = findVehicleById(vehicleID);

        const vector<std::pair<int,int>>& path = pair.second;

        cout << "Vozilo " << vehicle.getVehicleName() << " je trenutno na poziciji ";

        if(!path.empty())
        {
            for(const auto& node : path)
            {
                if(node.second == 1)
                {
                    cout << node.first << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Nema definisanu putanju." << endl;
        }
    }
}

//provjera popunjenosti cvora

bool TrafficSimulation::isNodeFullById(int idNode)
{
    Node* node = trafficGraph.getNodeById(idNode);

    if(node != nullptr)
    {
        if(node->type() == "PathNode")
        {
            return dynamic_cast<PathNode*>(node)->isNodeFull();
        }
        else if(node->type() == "IntersectionNode")
        {
            return dynamic_cast<IntersectionNode*>(node)->isNodeFull();
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout <<"Cvor sa datim ID-jem nije pronadjen.";
        return false;
    }
}

void TrafficSimulation::executeSimulationStep()
{
    int vehicleIndex = 0;
    for(auto& pair : vehiclePaths)
    {
        int vehicleID = pair.first;
        Vehicle vehicle = findVehicleById(vehicleID);
        vector<std::pair<int,int>>& path = pair.second;

        if(!path.empty())
        {
            for(size_t i = 0; i < path.size(); ++i)
            {
                if(path[i].second == 1)
                {
                    if(i + 1 < path.size())
                    {
                        if(!isNodeFullById(path[i+1].first))
                        {
                            if(tmpSimulationTimes[vehicleIndex] + vehicle.getTimeMatrix()[path[i].first][path[i+1].first] >= durationPerStep)
                            {
                                path[i].second = 0;
                                path[i + 1].second = 1;
                                tmpSimulationTimes[vehicleIndex] = 0.0;
                                 if(trafficGraph.getNodeById(path[i].first)->type() == "PathNode")
                                        {
                                            Node* node = trafficGraph.getNodeById(path[i].first);
                                            dynamic_cast<PathNode*>(node)->decreaseNumOfCurrVeh();
                                        }
                                        else if(trafficGraph.getNodeById(path[i].first)->type() == "IntersectionNode")
                                        {
                                            Node* node = trafficGraph.getNodeById(path[i].first);
                                            dynamic_cast<IntersectionNode*>(node)->decreaseNumOfCurrVeh();
                                        }
                                        if(trafficGraph.getNodeById(path[i+1].first)->type() == "PathNode")
                                        {
                                            Node* node = trafficGraph.getNodeById(path[i+1].first);
                                            dynamic_cast<PathNode*>(node)->increaseNumOfCurrVeh();
                                        }
                                        else if(trafficGraph.getNodeById(path[i+1].first)->type() == "IntersectionNode")
                                        {
                                            Node* node = trafficGraph.getNodeById(path[i+1].first);
                                            dynamic_cast<IntersectionNode*>(node)->increaseNumOfCurrVeh();
                                        }
                                break;
                            }
                            else
                            {
                                tmpSimulationTimes[vehicleIndex] = durationPerStep;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Vozilo nema definisanu putanju." << endl;
        }
        vehicleIndex++;
    }
}

double TrafficSimulation::averageTime(const string& vehicleName,int fromID,int toID) const 
{
    for(const auto& pair : vehiclePaths)
    {
        int vehicleID = pair.first;
        Vehicle vehicle = findVehicleById(vehicleID);
        if(vehicle.getVehicleName() == vehicleName)
        {
            if(fromID < 0 || fromID >= vehicle.getTimeMatrix().size() || toID < 0 || toID >= vehicle.getTimeMatrix().size()) 
            {
                throw out_of_range("Indeks izvan opsega.");
                //return -1.0;
            }
            return vehicle.getTimeMatrix()[fromID][toID];
        }
    }
    throw invalid_argument("Vozilo nije pronadjeno.");
}

bool TrafficSimulation::isSimulationFinished() 
{
    for(const auto& pair : vehiclePaths)
    {
        const vector< std::pair<int,int> >& path = pair.second;
        if(!path.empty() && path.back().second != 1)
            return false;
    }
    return true;
}

void TrafficSimulation::printCurrentLocation(const string& vehicleName)
{
    bool found = false;
    for(const auto& pair : vehiclePaths)
    {
        int vehicleID = pair.first;
        Vehicle vehicle = findVehicleById(vehicleID);
        if(vehicle.getVehicleName() == vehicleName)
        {
            found = true;
            const vector<std::pair<int,int>>& path = pair.second;
            if(!path.empty())
            {
                for(const auto& node : path)
                {
                    if(node.second == 1)
                    {
                        cout << "Vozilo se nalazi na cvoru: " << node.first << endl;
                    }
                }
            }
            else
            {
                cout << "Vozilo nema definisanu putanju." << endl;
            }
            break;
        }
    }
    if(!found)
    {
        cout << "Vozilo sa imenom " << vehicleName << "nije pronadjeno." << endl;
    }
}
        
