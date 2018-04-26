//----------------------------------------------------------------------//
// Author:
// Net ID:
// Date:
//
//----------------------------------------------------------------------//

#include "Velociplotter.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Velociplotter::Velociplotter(string inputFilePath, string outputFilePath){
    _inputFilePath = inputFilePath;
    _outputFilePath = outputFilePath;
}

void Velociplotter::Run(){
    ReadInputsFromFile();
    CalculateAverageVelocities();
    WriteOutputsToFile();
}

void Velociplotter::ReadInputsFromFile()
{
    //Any sentence in the input GPS file that does not match the NMEA $GPGGA format, should be ignored.
    //The time values read from the file should be increasing.
    //If a time value for a validly formatted $GPGGA sentence is earlier than or equal to the
    //time value for a previously read validly formatted line
    //your program should report an error and exit immediately
    ifstream inputStream;
    inputStream.open(_inputFilePath);
    if(!inputStream.is_open())
    {
        cout << "Could not open: " << _inputFilePath << endl;
    }
    std::string line;
    std::string identifier;
    float time;
    float latitude;
    float longitude;
    
    while(getline(inputStream, line))
    {
        stringstream inputSStream(line);
        inputSStream >> identifier >> time >> latitude >> longitude;
        cout << "Identifier is: " << identifier << endl;
        cout << "Time is: " << time << endl;
        cout << "Latitude is: " << latitude << endl;
        cout << "Longitude is: " << longitude << endl;
        if(identifier.compare("$GPGGA") == 0)
        {
            
        }
        
        
    }


    
}

void Velociplotter::CalculateAverageVelocities(){
    //average_velocity = (x_1 - x_0)/(t_1 - t_0)
    //This is straight forward when there is a GPS sentence available at time t_0.
    //If there is not, then output the SAME average velocity until the next time where a GPS sentence appears.
    
}

void Velociplotter::WriteOutputsToFile(){
    //TIME SPEED
    //TIME should be output as an integer value (in seconds)
    //The two values should be separated by exactly one single space character
    //SPEED should be output as double value using the default precision representing the average speed (in kilometers per hour) to be calculated
    //This should be done for every second from the first entry in inputFilePath to the last entry.
    //Even if a GPS sentence does not exist for a specified second, you must fill in the missing data.
    //The speed at the time of the first GPS reading from the input GPS log cannot be determined as there is no previous GPS location information.
    //Thus, the first output for the GPS plot data file should start one second after the time of the first GPS reading in the input log file.
        
        
        
        
}
