#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

//establishes initial variables and functions
float j, Min, T[10000000], rads[10000], times[10000], mins[100000], mids[100000], maxs[100000], iTJTemp, TC, TCMin, TCMid, TCMax, iTJTempK, lTempK, lTemp, dTime, dTemp,dTempMin, dTempMid, dTempMax, heat, sA, sAMin, sAMid, sAMax, mass, specHeat, density, volume, rad,radMin,radMid,radMax, massMin, massMid, massMax, volMin, volMid,volMax,rate,rateMin,rateMid,rateMax;
int i,b;
double pi= 3.14159265359;
float ROC(float heat, float sA, float Tl, float T, float mass, float specHeat);
string filename,filename2;
ofstream outfile,outfile2;


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
    //asks the user for the sphere specific heat and stores the input
    cout << "Please enter the sphere specific heat in J/kg*K"<< endl;
    cin >> specHeat;
    //asks the user for the time step and stores the input
    cout << "Please enter the desired time step in seconds"<< endl;
    cin >> dTime;
    cout << "Please enter what you would like to name the first text file"<< endl;
    cin >> filename;
    cout << "Please enter what you would like to name the second text file"<< endl;
    cin >> filename2;

  //  Test Variables
  /*  iTJTemp = 100.0;
    lTemp = 25.0;
    heat = 1000.0;
    density = 9400.0;
    specHeat = 190.0;
    rad = 0.0003;
    radMin = 0.0003;
    dTime = 0.001;
    filename = "CppFinalPart214txt";
    filename2 = "CppFinalPart224.txt";*/

    //calculates temperature values in Kelvin
    iTJTempK = iTJTemp + 273.15;
    lTempK = lTemp + 273.15;

    //Sets the precision of outputs
    outfile << fixed << setprecision(4)<<endl;
    cout << fixed << setprecision(4)<<endl;

    //sets filename of outfile and opens it
    outfile.open(filename, ios::out);
    outfile2.open(filename2, ios::out);

    //Data Labels
   // outfile << "Radius(m)" << setw(10) << "Time(s): " << endl;
   // cout << "Radius(m)" << setw(10) << "Time(s): " << endl;

    //Outputs first value
    outfile << dTime-dTime << setw(10) << iTJTemp << endl;

//sets counters to zero and initial temp values to inputs
i=1;
    T[0] = iTJTempK;
    rads[0] = rad;
    times[0] = 0;
    int b = 0;

    //while the time to reach liquid temp is less than 5 seconds
    while (j < 5.0) {
        //Resets initial values for inner loop counters and temp
        T[0] = iTJTempK;
        TC = T[0] - 273.15;
        Min = (lTemp + .1);
        i = 1;
        j = dTime;
        //calculates volume then mass
        volume = (4.0/3.0) * pi * pow(rad,3);
        mass = density * volume;
        //calculates surface area
        sA = 4.0*pi*pow(rad,2);

        //while the minimum temperature has not been reached
        while (TC >= Min) {

            //calls rate function with set values
            rate = ROC(heat, sA, lTempK, T[i - 1], mass, specHeat);

            //calculates change in temp from rate and timestep
            dTemp = dTime * rate;

            //adds new temp value
            T[i] = T[i - 1] + dTemp;

            //converts from kelvin
            TC = T[i] - 273.15;

            //increments counter and time elapsed
            j = dTime * i;
            i++;
        }
        //stores radius and time values in respective arrays
        rads[b] = rad;
        times[b] = j;
        //outputs radius and time values
        cout << rads[b] << setw(10) << fixed <<setprecision(5)<< times[b] << endl;
       outfile << rads[b] << setw(10) << fixed <<setprecision(5)<< times[b] << endl;
        b++;
        //increases radius every loop
        rad = rad + 0.00005;
    }

    //finds maximum and average radius from final loop value
   radMax =rad - 0.00005;
    radMid = (radMax + radMin)/2;

    //recalculates volume mass ad surface area for each radius
    volMin = (4.0/3.0) * pi * pow(radMin,3);
    massMin = density * volMin;
    sAMin = 4.0*pi*pow(radMin,2);
    volMid = (4.0/3.0) * pi * pow(radMid,3);
    massMid = density * volMid;
    sAMid = 4.0*pi*pow(radMid,2);
    volMax = (4.0/3.0) * pi * pow(radMax,3);
    massMax = density * volMax;
    sAMax = 4.0*pi*pow(radMax,2);

    //sets initial temp values for all three radii
    i=1;
    mins[0] = iTJTempK;
    mids[0] = iTJTempK;
    maxs[0] = iTJTempK;
    TCMin = mins[0] - 273.15;
    TCMid = mids[0] - 273.15;
    TCMax = maxs[0] - 273.15;

    //outputs radius values to data
    outfile2 << radMin << setw(10) << radMid << setw(10) << radMax << endl;
    cout << radMin << setw(10) << radMid << setw(10) << radMax << endl;

    //while any of the radii have not reached liquid temperature range
    while ((TCMin >= Min) || (TCMid >=Min) || (TCMax >=Min)) {

        //calls rate function, then calculates the change in temp, and current temp for all three radii
        rateMin = ROC(heat, sAMin, lTempK, mins[i - 1], massMin, specHeat);
        dTempMin = dTime * rateMin;
        //adds new temp value
        mins[i] = mins[i - 1] + dTempMin;
        TCMin = mins[i] - 273.15;

        rateMid = ROC(heat, sAMid, lTempK, mids[i - 1], massMid, specHeat);
        dTempMid = dTime * rateMid;
        //adds new temp value
        mids[i] = mids[i - 1] + dTempMid;
        TCMid = mids[i] - 273.15;

        rateMax = ROC(heat, sAMax, lTempK, maxs[i - 1], massMax, specHeat);
        dTempMax = dTime * rateMax;
        //adds new temp value
        maxs[i] = maxs[i - 1] + dTempMax;
        TCMax = maxs[i] - 273.15;
        j = dTime * i;
        i++;

        //outputs all three arrays of temperatures and times to the second output file
        outfile2 << TCMin << setw(10) << TCMid << setw(10) << TCMax << setw(10) << j << endl;
        cout << TCMin << setw(10) << TCMid << setw(10) << TCMax << setw(10) << j <<endl;

    }


    return 0;
    //ends main

}
//function
float ROC(float heatTran, float sphereSA, float liquidTK, float tJT, float sphereM, float sphereSH){
    float tJTROC; //rate of change of thermo junction temp
    tJTROC = ((heatTran * sphereSA*(liquidTK - tJT)) / (sphereM * sphereSH));
    return tJTROC;
}