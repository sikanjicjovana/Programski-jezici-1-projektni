#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "TrafficGraph.h"


using namespace std;

class Vehicle
{
    private:
        int vehicleID;
        string vehicleName;
        int currentLocationID;
        int destinationID;
        double averageSpeed;
        double realSpeed;
        vector<vector<double>> timeMatrix;
        vector<pair<int,int>> path;

    public:
        Vehicle(int vehicleID,const string& vehicleName, int startLocationID, int destinationID,  double averageSpeed ); 

        int getVehicleID() const;
        const string& getVehicleName() const;
        int getCurrentLocation() const;
        int getDestination() const;
        double getAverageSpeed() const;
        double getRealSpeed() const;
        vector<vector<double>>& getTimeMatrix();

        void setPath(vector<pair<int,int>>& newPath);

        void setDestination(int newDestination);

        void printVehicleInfo() const;

        void calculateRealSpeed(double speedLimit);

        double calculateTravelTime(double distance);

        void initTimeMatrix(vector< vector<double> >& lengthMatrix, TrafficGraph graph); 
};