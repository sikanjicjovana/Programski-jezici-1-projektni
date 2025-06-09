#pragma once
#include <iostream>
#include <unordered_map>
#include <utility>
#include <exception>
#include "TrafficGraph.h"
#include "Vehicle.h"
#include "InterfaceSimulation.h"

class TrafficSimulation : public InterfaceSimulation
{
    private:
        TrafficGraph trafficGraph;
        double durationPerStep;
        vector<Vehicle> vehicles;
        unordered_map<int, vector<pair<int,int>>> vehiclePaths;
        vector<double> tmpSimulationTimes;
    
    public:
        TrafficSimulation(const TrafficGraph& graph, double duration, const std::unordered_map<int, std::vector<std::pair<int, int>>>& paths);
        
        void addVehicle(const Vehicle& vehicle); 
        
        Vehicle findVehicleById(int id) const;

        void startSimulation();

        void printVehicleLocations();

        bool isNodeFullById(int idNode);

        void executeSimulationStep() override;

        double averageTime(const string& vehicleName,int fromID,int toID) const override;

        bool isSimulationFinished() override;

        void printCurrentLocation(const string& vehicleName) override;    
};