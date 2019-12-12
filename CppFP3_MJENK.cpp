#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

//establish all initial variables and functions
float j, Min, heats[10000000], times[1000000], T[10000000], iTJTemp, TC, iTJTempK, lTempK, lTemp, dTime, dT0, dTemp, heat, sA, mass, specHeat, density, volume, rad, rate0, rate;
int i,a;
double pi= 3.14159265359;
float ROC(float heat, float sA, float Tl, float T, float mass, float specHeat);
string filename;
ofstream outfile;


int main() {

    //asks user for thermocouple junction temperature and stores it
    cout << "Please enter the initial thermocouple junction temperature in Celsius" << endl;
    cin >> iTJTemp;
    //asks user for liquid temperature and stores it
    cout << "Please enter the liquid temperature in Celsius" << endl;
    cin >> lTemp;
    //asks user for heat transfer coefficient and stores it
    cout << "Please enter the heat transfer coefficient" << endl;
    cin >> heat;
    //asks user for sphere density and stores it
    cout << "Please enter the sphere density in kg/m^3" << endl;
    cin >> density;
    //asks user for sphere radius and stores it
    cout << "Please enter the sphere radius in meters" << endl;
    cin >> rad;
    //asks user for specific heat and stores it
    cout << "Please enter the sphere specific heat in J/kg*K" << endl;
    cin >> specHeat;
    //asks user for time step and stores it
    cout << "Please enter the desired time step in seconds" << endl;
    cin >> dTime;

    //Test Variables
/*    iTJTemp = 100.0;
    lTemp = 25.0;
    heat = 300.0;
    density = 8922.0;
    specHeat = 287.0;
    rad = 0.0005;
    dTime = 0.001;
    iTJTempK = iTJTemp + 273.15;
    lTempK = lTemp + 273.15;*/

    //calculates volume then mass
    volume = (4.0 / 3.0) * pi * pow(rad, 3);
    mass = density * volume;
    //calculates surface area
    sA = 4.0 * pi * pow(rad, 2);

    //Sets the precision of outputs
    outfile << fixed << setprecision(4) << endl;
    cout << fixed << setprecision(4) << endl;

    //sets filename of outfile and opens it
    filename = "CppFinalPart3.txt";
    outfile.open(filename, ios::out);

    //Data Labels
    cout << "Specific Heat" << setw(10) << "Time(s): " << endl;

    //Outputs first value
    outfile << dTime - dTime << setw(10) << iTJTemp << endl;

    a=0;
    //while heat is within threshold
    while (heat <= 1000) {

        //resets counter and initial values
        T[0] = iTJTempK;
        TC = T[0] - 273.15;
        Min = (lTemp + .1);
        i = 1;
        j = dTime;

        //while thermocouple temp is greater than minimum alloted value
        while (TC >= Min) {

            //calls rate function with given variables
            rate = ROC(heat, sA, lTempK, T[i - 1], mass, specHeat);

            //calculates change in temp from rate and timestep
            dTemp = dTime * rate;

            //adds new temp value
            T[i] = T[i - 1] + dTemp;

            //converts from kelvin
            TC = T[i] - 273.15;

            //increments counter
            i++;
            //recalculates time elapsed
            j = dTime * i;
        }
       // heats[a] = heat;
        //times[a] = j;

        //outputs heat and time values
        outfile<< heat << setw(10) << j << endl;
        cout << heat << setw(10) << j<< endl;

        //increases heat
        heat = heat + 25.0;
        a++;
    }
    return 0;
    //ends main
}

//function
float ROC(float heatTran, float sphereSA, float liquidTK, float tJT, float sphereM, float sphereSH){
    float tJTROC;
    //calculates rate of change of thermo junction temp
    tJTROC = ((heatTran * sphereSA*(liquidTK - tJT)) / (sphereM * sphereSH));
    //returns rate
    return tJTROC;
}