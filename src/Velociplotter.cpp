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
    std::string directionLat;
    std::string directionLong;
    int i = 14;
    bool isGPGGA = false;
    int newLineIndex = 0;
    
    while(getline(inputStream, line, ','))
    {
        stringstream inputSStream(line);
        cout << "Line is: " << line << endl;
        newLineIndex = line.find('\n');
       // cout << "New line index is: " << newLineIndex << endl;
        if(newLineIndex == -1 && !isGPGGA)
        {
            i = 14;
        }
        else if(newLineIndex != -1)
        {
            identifier = line.substr(newLineIndex + 1);
            cout << "In newLineIndex part and identifier is " << identifier << endl;
            if(identifier.compare("$GPGGA") == 0)
            {
                isGPGGA = true;
            }
            else
            {
                isGPGGA = false;
            }
            i = 14;
        }
       // cout << "i is: " << i << " and isGPGGA value is: " << isGPGGA << endl;
        if(i == 14 && !isGPGGA)
            {
                inputSStream >> identifier;
                cout << "Identifier is: " << identifier << endl;
                if(identifier.compare("$GPGGA") == 0)
                {
                    isGPGGA = true;
                    cout << "Is GPGGA idenitifer: " << identifier << endl;
                }
                else
                {
                    isGPGGA = false;
                }
            }
        else if(i == 13 && isGPGGA)
            {
                inputSStream >> time;
                cout << "Time is: " << time << endl;
            }
        else if(i == 12 && isGPGGA)
            {
                inputSStream >> latitude;
                cout << "Latitude is: " << latitude << endl;
            }
        else if(i == 10 && isGPGGA)
            {
                inputSStream >> longitude;
                cout << "Longitude is: " << longitude << endl;
            }
        
        i--;
     }
    
    }
//        inputSStream >> identifier >> comma >> time >> comma >> latitude >> comma >> directionLat >> comma >> longitude >> comma >> directionLong;
//        cout << "Identifier is: " << identifier << endl;
//        cout << "Time is: " << time << endl;
//        cout << "Latitude is: " << latitude << endl;
//        cout << "Longitude is: " << longitude << endl;
//        cout << "i is: " << i << endl;
//        if(i == 14)
//        {
//            inputSStream >> identifier;
//            cout << "Identifier is: " << identifier << endl;
//            if(identifier.compare("$GPGGA") == 0)
//            {
//                isGPGGA = true;
//                i--;
//            }
//        }
//        else if(i == 13 && isGPGGA)
//        {
//            inputSStream >> time;
//            cout << "Time is: " << time << endl;
//            i--;
//        }
//        else if(i == 12 && isGPGGA)
//        {
//            inputSStream >> latitude;
//            cout << "Latitude is: " << latitude << endl;
//            i--;
//        }
//        else if(i == 10 && isGPGGA)
//        {
//            inputSStream >> longitude;
//            cout << "Longitude is: " << longitude << endl;
//            i--;
//        }
////        stringstream inputSStream(line);
////        cout << "Line is: " << line << endl;
////        inputSStream >> identifier >> comma >> time >> comma >> latitude >> comma >> directionLat >> comma >> longitude >> comma >> directionLong;
////        cout << "Identifier is: " << identifier << endl;
////        cout << "Time is: " << time << endl;
////        cout << "Latitude is: " << latitude << endl;
////        cout << "Longitude is: " << longitude << endl;
//        if(identifier.compare("$GPGGA") == 0)
//        {
//
//        }
        


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
