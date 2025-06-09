#include "Vehicle.h"

Vehicle::Vehicle(int vehicleID,const string& vehicleName, int startLocationID, int destinationID,  double averageSpeed ) 
    : vehicleID(vehicleID),vehicleName(vehicleName) , currentLocationID(startLocationID) , destinationID(destinationID), averageSpeed(averageSpeed) 
    {
        int rows = 16;
        int columns = 16;
        timeMatrix.resize(rows, vector<double>(columns,0.0));
    }

int Vehicle::getVehicleID() const 
{ 
    return vehicleID;
}

const string& Vehicle::getVehicleName() const 
{ 
    return vehicleName; 
}

int Vehicle::getCurrentLocation() const 
{ 
    return currentLocationID; 
}

int Vehicle::getDestination() const 
{ 
    return destinationID; 
} 

double Vehicle::getAverageSpeed() const 
{ 
    return averageSpeed; 
}

double Vehicle::getRealSpeed() const 
{ 
    return realSpeed;
} 

vector<vector<double>>& Vehicle::getTimeMatrix() 
{ 
    return timeMatrix; 
}

void Vehicle::setPath(vector<pair<int,int>>& newPath)
{
    path = newPath;
}

void Vehicle::setDestination(int newDestination)
{
    destinationID = newDestination;
}

void Vehicle::printVehicleInfo() const
{
    cout << "Ime vozila: " << vehicleName << " Pocetna lokacija ID: " << currentLocationID << " Destinacija ID: " << destinationID << " Prosjecna brzina: " << averageSpeed << endl;
}

//speedLimit je zapravo ogranicenje brzine na putu na kom je vozilo trenutno

void Vehicle::calculateRealSpeed(double speedLimit)
{
    if(averageSpeed <= speedLimit)
        realSpeed = averageSpeed;
    else
        realSpeed = speedLimit;
}

double Vehicle::calculateTravelTime(double distance)
{
    return distance/realSpeed;
}

void Vehicle::initTimeMatrix(vector< vector<double> >& lengthMatrix, TrafficGraph graph)
{
    for(int i = 0; i <= graph.getNumNodes(); i++)
    {
        for(int j = 0; j <= graph.getNumNodes(); j++)
        {
            if(i == j)
            {
                timeMatrix[i][j] = 0;
            }
            else if(lengthMatrix[i][j] != INFINITY)
            {
                double tmpSpeed;
                double tmpTravelTime;
                for(auto& node : graph.getNodes())
                {
                    if( node != nullptr && node->getNodeId() == i && node->type() == "PathNode")
                    {
                        tmpSpeed = dynamic_cast<PathNode*>(node)->getMaxSpeed();
                        calculateRealSpeed(tmpSpeed);
                    }
                    else if(node != nullptr && node->getNodeId() == j && node->type() == "PathNode")
                    {
                        tmpSpeed = dynamic_cast<PathNode*>(node)->getMaxSpeed();
                        calculateRealSpeed(tmpSpeed);
                    }
                }
                timeMatrix[i][j] = calculateTravelTime(lengthMatrix[i][j]);
            }
            else
            {
                timeMatrix[i][j] = INFINITY;
            }
        }
    }
}