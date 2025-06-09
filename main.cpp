#include <iostream>
#include "IntersectionNode.h"
#include "LocationNode.h"
#include "TrafficGraph.h"
#include "Vehicle.h"
#include "TrafficSimulation.h"

int main()
{
    TrafficGraph graph(16);

    LocationNode* location1;
    location1 = new LocationNode(1, "A" , "parking");
    LocationNode* location2;
    location2 = new LocationNode(2, "B" , "grad");
    LocationNode* location3;
    location3 = new LocationNode(3, "C","grad2");
    LocationNode* location4;
    location4 = new LocationNode(4, "D" , "park");

    PathNode* path1;
    path1 = new PathNode(5,"Path1", 20.0, 60.0, 3);
    PathNode* path2;
    path2 = new PathNode(6,"Path2", 21.0, 50.0, 2);
    PathNode* path3;
    path3 = new PathNode(7,"Path3", 80.0, 70.0, 9);
    PathNode* path4;
    path4 = new PathNode(8,"Path4", 18.0, 30.0, 2);
    PathNode* path5;
    path5 = new PathNode(9,"Path5", 98.0, 20.0, 12);
    PathNode* path6;
    path6 = new PathNode(10,"Path6", 43.0, 80.0, 5);
    PathNode* path7;
    path7 = new PathNode(11,"Path7", 56.0, 100.0, 7);
    PathNode* path8;
    path8 = new PathNode(12,"Path8", 71.0, 50.0, 6);
    PathNode* path9;
    path9 = new PathNode(13,"Path9", 89.0, 80.0, 4);

    IntersectionNode* intersection1;
    intersection1 = new IntersectionNode(14, "Intersection1", 8);
    IntersectionNode* intersection2;
    intersection2 = new IntersectionNode(15, "Intersection2", 5);

    Link link1(path9, path7, 5.0, 40.0);
    Link link2(path6, path7, 2.0, 45.0);
    Link link3(path2, path3, 1.0, 50.0);
    Link link4(path4, path3, 3.0, 30.0);
    Link link5(path4, path5, 1.0, 20.0);
    Link link6(path7, path4, 2.0, 40.0);
    Link link7(path7, path8, 3.0, 60.0);
    Link link8(path2, path8, 2.0, 45.0);
    Link link9(path4, path1, 1.0, 35.0);
    Link link10(path7, path1, 3.0, 45.0);
    Link link11(path4, path8, 4.0, 20.0);
    Link link12(path2, path5, 5.0, 30.0);
    Link link13(path7, path2, 6.0, 50.0);

    intersection1->addLink(link1);
    intersection1->addLink(link2);
    intersection2->addLink(link3);
    intersection2->addLink(link4);
    intersection2->addLink(link5);
    intersection2->addLink(link6);
    intersection2->addLink(link7);
    intersection2->addLink(link8);
    intersection2->addLink(link9);
    intersection2->addLink(link10);
    intersection2->addLink(link11);
    intersection2->addLink(link12);
    intersection2->addLink(link13);

    graph.addNode(location1);
    graph.addNode(location2);
    graph.addNode(location3);
    graph.addNode(location4);
    graph.addNode(path1);
    graph.addNode(path2);
    graph.addNode(path3);
    graph.addNode(path4);
    graph.addNode(path5);
    graph.addNode(path6);
    graph.addNode(path7);
    graph.addNode(path8);
    graph.addNode(path9);
    graph.addNode(intersection1);
    graph.addNode(intersection2);

    graph.connectNodes(path1,location1);
    graph.connectNodes(location1,path2);
    graph.connectNodes(path2,intersection1);
    graph.connectNodes(intersection1,path3);
    graph.connectNodes(path3,location3);
    graph.connectNodes(location3,path4);
    graph.connectNodes(path4,intersection1);
    graph.connectNodes(intersection1,path5);
    graph.connectNodes(path5,location2);
    graph.connectNodes(location2,path6);
    graph.connectNodes(path6,intersection2);
    graph.connectNodes(intersection2,path7);
    graph.connectNodes(path7,intersection1);
    graph.connectNodes(intersection1,path1);
    graph.connectNodes(intersection1,path8);
    graph.connectNodes(path8,location4);
    graph.connectNodes(location4,path9);
    graph.connectNodes(path9,intersection2);

    string filename = "graph.txt";

    graph.serializeGraph(filename);

    TrafficGraph graph2(16);
    graph2 = graph2.deserializeGraph(filename);

    //za duzinu
    vector< vector<int> > t(graph.getNumNodes()+1, vector<int>(graph.getNumNodes()+1,-1));
    vector< vector<double> > lengthMatrix(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));

    //za vrijeme
    vector< vector<int> > t1(graph.getNumNodes()+1, vector<int>(graph.getNumNodes()+1,-1));
    vector< vector<double> > lengthMatrixTmp1(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));

    vector< vector<int> > t2(graph.getNumNodes()+1, vector<int>(graph.getNumNodes()+1,-1));
    vector< vector<double> > lengthMatrixTmp2(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));

    vector< vector<int> > t3(graph.getNumNodes()+1, vector<int>(graph.getNumNodes()+1,-1));
    vector< vector<double> > lengthMatrixTmp3(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));

    //vector< vector<double> > timeMatrix1(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));
    //vector< vector<double> > timeMatrix2(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));
    //vector< vector<double> > timeMatrix3(graph.getNumNodes()+1, vector<double>(graph.getNumNodes()+1,0));
    
    graph.initT(t);
    graph.initLengthMatrix(lengthMatrix);
    graph.floyd(t,lengthMatrix);
    
    cout << endl;

    Vehicle vehicle1(0,"vozilo1",1,4,50.0);
    Vehicle vehicle2(1,"vozilo2",3,1,60.0);
    Vehicle vehicle3(2,"vozilo3",1,3,40.0);

    vehicle1.printVehicleInfo();
    vehicle2.printVehicleInfo();
    vehicle3.printVehicleInfo();

    cout << endl;

    graph.initT(t1);
    graph.initLengthMatrix(lengthMatrixTmp1);
    vehicle1.initTimeMatrix(lengthMatrixTmp1,graph);
    graph.floyd(t1,vehicle1.getTimeMatrix());
    cout << "Putanja prvog vozila: (minimizuje vrijeme):" << endl;
    graph.writePath(vehicle1.getCurrentLocation(),vehicle1.getDestination(),t1);
    vector<pair<int,int>> bestPath1;
    graph.savePath(vehicle1.getCurrentLocation(),vehicle1.getDestination(),t1,bestPath1);
    vehicle1.setPath(bestPath1);

    cout << endl;

    graph.initT(t2);
    graph.initLengthMatrix(lengthMatrixTmp2);
    vehicle2.initTimeMatrix(lengthMatrixTmp2,graph);
    graph.floyd(t2,vehicle2.getTimeMatrix());
    cout << "Putanja drugog vozila: (minimizuje vrijeme):" << endl;
    graph.writePath(vehicle2.getCurrentLocation(),vehicle2.getDestination(),t2);
    vector<pair<int,int>> bestPath2;
    graph.savePath(vehicle2.getCurrentLocation(),vehicle2.getDestination(),t2,bestPath2);
    vehicle2.setPath(bestPath2);

    cout << endl;

    graph.initT(t3);
    graph.initLengthMatrix(lengthMatrixTmp3);
    vehicle3.initTimeMatrix(lengthMatrixTmp3,graph);
    graph.floyd(t3,vehicle3.getTimeMatrix());
    cout << "Putanja treceg vozila: (minimizuje vrijeme):" << endl;
    graph.writePath(vehicle3.getCurrentLocation(),vehicle3.getDestination(),t3);
    vector<pair<int,int>> bestPath3;
    graph.savePath(vehicle3.getCurrentLocation(),vehicle3.getDestination(),t3,bestPath3);
    vehicle3.setPath(bestPath3);

    cout << endl;

    cout << "Minimizuje putanju" << endl;
    cout << "Putanja prvog vozila:" << endl;
    graph.writePath(vehicle1.getCurrentLocation(),vehicle1.getDestination(),t); 
    cout << endl;
    cout << "Putanja drugog vozila:" << endl;
    graph.writePath(vehicle2.getCurrentLocation(),vehicle2.getDestination(),t); 
    cout << endl;
    cout << "Putanja treceg vozila:" << endl;
    graph.writePath(vehicle3.getCurrentLocation(),vehicle3.getDestination(),t); 
    cout << endl;

    unordered_map<int,vector<pair<int,int>>> paths = {{vehicle1.getVehicleID(),bestPath1},{vehicle2.getVehicleID(),bestPath2},{vehicle3.getVehicleID(),bestPath3}};
    TrafficSimulation simulation(graph,30.0,paths);
    simulation.addVehicle(vehicle1);
    simulation.addVehicle(vehicle2);
    simulation.addVehicle(vehicle3);

    string selector;
    string selector1;
    
    cout << "Da li zelite da pokrenete simulaciju?[DA/NE]" << endl;
    cin >> selector1;  
    if(selector1 == "DA")
    {
        simulation.startSimulation();
        simulation.printVehicleLocations();
        do
        {
            cout << "Izaberite opciju:" << endl;
            cout <<" _______________________________________ " << endl;
            cout <<"|                                       |" << endl;
            cout <<"|  [1] Izvrsi korak simulacije          |" << endl;
            cout <<"|  [2] Da li je simulacija zavrsena?    |" << endl;
            cout <<"|  [3] Provjeri trenutno stanje vozila  |" << endl;
            cout <<"|  [4] Prosjecno vrijeme putovanja      |" << endl;
            cout <<"|  [5] Zavrsi simulaciju                |" << endl;
            cout <<"|_______________________________________|" << endl;

            cin >> selector;
            if(selector == "1")
            {
                simulation.executeSimulationStep();
                simulation.printVehicleLocations();
            }
            else if(selector == "2")
            {
                if(simulation.isSimulationFinished())
                    cout << "Simulacija je zavrsena." << endl;
                else
                    cout << "Simulacija nije zavrsena." << endl;
            }
            else if(selector == "3")
            {
                string inputVehicleName;
                cout << "Unesite ime vozila: " << endl;
                getline(cin >> ws, inputVehicleName);
                simulation.printCurrentLocation(inputVehicleName);
            }
            else if(selector == "4")
            {
                string inputVehicleName;
                cout << "Unesite ime vozila: " << endl;
                getline(cin >> ws, inputVehicleName);
                int startId;
                cout << "Unestite ID startnog cvora:" << endl;
                cin >> startId;
                int finishId;
                cout << "Unesite ID finalnog cvora:" << endl;
                cin >> finishId;
                double time;
                time = simulation.averageTime(inputVehicleName,startId,finishId);
                cout << "Prosjecno vrijeme putovanje izmedju zadata dva cvora je : " << time << endl;
                
            }
        }while(selector != "5");
    }
    else if(selector == "NE")
    {
        cout <<"Niste pokrenuli simulaciju." << endl;
    }
    else
    {
        cout << "Nepoznata opcija." << endl;
    }

    //system("pause");

    //file.close();   
    return 0;
}
