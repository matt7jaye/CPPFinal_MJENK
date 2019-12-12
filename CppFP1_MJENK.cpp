#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

float j, Min, T[10000000], iTJTemp, TC, iTJTempK, lTempK, lTemp, dTime, dT0, dTemp, heat, sA, mass, specHeat, density, volume, rad, rate0, rate;
int i;
double pi= 3.14159265359;
float ROC(float heat, float sA, float Tl, float T, float mass, float specHeat);
string filename;
ofstream outfile;


int main() {


    //Welcome Message
    cout << "Welcome to the thermocouple junction evaluator"<<endl;

    //asks the user for the initial thermocouple junction temp and stores the input
    cout << "Please enter the initial thermocouple junction temperature in Celsius" << endl;
    cin >> iTJTemp;
    //asks the user for the initial liquid temperature and stores the input
    cout << "Please enter the liquid temperature in Celsius"<< endl;
    cin >> lTemp;
    //asks the user for the heat transfer coefficient and stores the input
    cout << "Please enter the heat transfer coefficient"<< endl;
    cin >> heat;
    //asks the user for the sphere density and stores the input
    cout << "Please enter the sphere density in kg/m^3"<< endl;
    cin >> density;
    //asks the user for the sphere radius and stores the input
    cout << "Please enter the sphere radius in meters"<< endl;
    cin >> rad;
    //asks the user for the sphere specific heat and stores the input
    cout << "Please enter the sphere specific heat in J/kg*K"<< endl;
    cin >> specHeat;
    //asks the user for the time step and stores the input
    cout << "Please enter the desired time step in seconds"<< endl;
    cin >> dTime;

  //  Test Variables
/*    iTJTemp = 100.0;
    lTemp = 25.0;
    heat = 1000.0;
    density = 8922.0;
    specHeat = 287.0;
    rad = 0.0005;
    dTime = 0.001;*/

    //calculates temperature values in Kelvin
    iTJTempK = iTJTemp + 273.15;
    lTempK = lTemp + 273.15;

    //calculates volume then mass
    volume = (4.0/3.0) * pi * pow(rad,3);
    mass = density * volume;
    //calculates surface area
    sA = 4.0*pi*pow(rad,2);

    //Sets the precision of outputs
    outfile << fixed << setprecision(4)<<endl;
    cout << fixed << setprecision(4)<<endl;

    //sets filename of outfile and opens it
    filename = "CppFinalPart1.txt";
    outfile.open(filename, ios::out);

    //Data Labels
   // outfile << "Time(s)" << setw(10) << "Temp(C): " << endl;
    cout << "Time(s)" << setw(10) << "Temp(C): " << endl;

    //Outputs first value
    outfile << dTime-dTime << setw(10) << iTJTemp << endl;


    //Establishes initial values for loop
    T[0] = iTJTempK;
    TC = T[0] - 273.15;
    Min = (lTemp + .1);
    i = 1;
    j = dTime;
    while (TC >= Min) {

        //calls rate function with given variables
        rate = ROC(heat, sA, lTempK, T[i-1], mass, specHeat);

        //calculates change in temp with rate
        dTemp = dTime * rate;

        //adds new temp value
        T[i] = T[i-1] +dTemp;

        //converts from kelvin
        TC = T[i] - 273.15;

        //outputs time and temp values
        outfile << j << setw(10) << TC << endl;
        cout<< j << setw(10) << TC << endl;
        //increments counter and time elapsed
        i++;
        j = dTime*i;
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