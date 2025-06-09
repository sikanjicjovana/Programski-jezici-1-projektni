#pragma once
#include <iostream>
#include "Vehicle.h"

class InterfaceSimulation
{
    public:
        virtual void executeSimulationStep() = 0;
        virtual void printCurrentLocation(const string& vehicleName) = 0;
        virtual bool isSimulationFinished() = 0;
        virtual double averageTime( const string& vehicleName,int fromID,int toID) const = 0;

};