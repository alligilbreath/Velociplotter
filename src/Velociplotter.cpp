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
#include <vector>
#include <cmath>

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
    cout << "Input file path is: " << _inputFilePath << endl;
    std::string line;
    std::string identifier;
    unsigned long time;
    double latitude;
    int latitudeDeg;
    double latMintoDeg;
    double longitude;
    int longitudeDeg;
    double longitudeMintoDeg;
    double hours = 0;
    double minutes = 0;
    int seconds = 0;
    std::string directionLat;
    std::string directionLong;
    int i = 14;
    bool isGPGGA = false;
    int newLineIndex = 0;
    int secondNewLineIndex = 0;
    while(getline(inputStream, line, ',') || !inputStream.eof())
    {
        stringstream inputSStream(line);
        //cout << "Line from " << _inputFilePath << " is: " << line << endl;
        newLineIndex = line.find('\n');
        //cout << "New line index is: " << newLineIndex << " and isGPGGA is: " << isGPGGA << " and input file Path " << _inputFilePath << endl;
        if(newLineIndex == -1 && !isGPGGA)
        {
            i = 14;
        }
        else if(newLineIndex != -1)
        {
            identifier = line.substr(newLineIndex + 1);
            secondNewLineIndex = identifier.find('\n');
           // cout << "In newLineIndex part and identifier is " << identifier << " " << _inputFilePath << endl;
            if(secondNewLineIndex != -1) //for weird input3
            {
                //cout << "Identifier was: " << identifier << endl;
                identifier = identifier.substr(secondNewLineIndex + 1);
               // cout << "New identifier is: " << identifier << endl;
            }
            
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
       // cout << "i is: " << i << " and isGPGGA value is: " << isGPGGA << " " << _inputFilePath << endl;
        if(i == 14 && !isGPGGA)
            {
                inputSStream >> identifier;
               // cout << "Identifier is: " << identifier << " " << _inputFilePath << endl;
                if(identifier.compare("$GPGGA") == 0)
                {
                    isGPGGA = true;
                    //cout << "Is GPGGA idenitifer: " << identifier << " " << _inputFilePath << endl;
                }
                else
                {
                    isGPGGA = false;
                }
            }
        else if(i == 13 && isGPGGA)
            {
                inputSStream >> time;
                hours = time / 10000;
                minutes = (time % 10000) / 100;
                seconds = time % 100;
                time = (hours * 3600) + (minutes * 60) + seconds;
                if(time == 0)
                {
                    isGPGGA = false;
                }
                
                
            }
        else if(i == 12 && isGPGGA)
            {
                inputSStream >> latitude;
              //  cout << "Latitude is: " << latitude << endl;
                latitudeDeg = latitude / 100;
              //  cout << "Latitude degree is: " << latitudeDeg << endl;
                latMintoDeg = (latitude - (latitudeDeg * 100)) / 60.0;
              //  cout << "LatMintoDeg is: " << latMintoDeg << endl;
                latitude = latitudeDeg + latMintoDeg;
               // cout << "New latitude is: " << latitude << endl;
                //degree minutes seconds
                //45.21 (.21 * 60)
               // cout << "Latitude is: " << latitude << " " << _inputFilePath << endl;
            }
        else if(i == 10 && isGPGGA)
            {
                inputSStream >> longitude;
               // cout << "Longitude is: " << longitude << endl;
                longitudeDeg = longitude / 100;
                //cout << "Longitude degree is: " << longitudeDeg << endl;
                longitudeMintoDeg = (longitude - (longitudeDeg * 100)) / 60.0;
                //cout << "LongMintoDeg is: " << longitudeMintoDeg << endl;
                longitude = longitudeDeg + longitudeMintoDeg;
               // cout << "New longitude is: " << longitude << endl;
                    //cout << "Longitude is: " << longitude << " " << _inputFilePath << endl;
                GPSPosition currGPS(latitude, longitude, time);
                _validPositions.push_back(currGPS);
                if(_validPositions.size() > 1)
                {
                    if(_validPositions.at(_validPositions.size() - 1).GetTime() < _validPositions.at(_validPositions.size() - 2).GetTime())
                    {
                        //  cout << "Found a time earlier than the previous" << " " << _inputFilePath << endl;
                        _validPositions.clear();
                        return;
                    }
                    else if(_validPositions.at(_validPositions.size() - 1).GetTime() == _validPositions.at(_validPositions.size() -2).GetTime())
                    {
                        cout << "Removed the previous position that was at the same time" << endl;
                        _validPositions.erase(_validPositions.begin() + _validPositions.size() - 2);
                    }
                }
            }
        
        i--;
     }
    cout << "Input file is: " << _inputFilePath << endl;
    for(unsigned int i = 0; i < _validPositions.size(); i++)
    {
//        cout << "Latitude: " << _validPositions.at(i).GetLatitude() << endl;
//        cout << "Longitude: " << _validPositions.at(i).GetLongitude() << endl;
//        cout << "Time: " << _validPositions.at(i).GetTime() << endl;
    }
    
    }
        


void Velociplotter::CalculateAverageVelocities(){
    //average_velocity = (x_1 - x_0)/(t_1 - t_0)
    //This is straight forward when there is a GPS sentence available at time t_0.
    //If there is not, then output the SAME average velocity until the next time where a GPS sentence appears.
    if(_validPositions.size() == 0)
    {
        cout << "No valid positions" << endl;
        return;
    }
    double currVelocity = 0;
    double distance = 0;
    unsigned long timeDiff = 0;
    unsigned int index = 1;
    unsigned long totalAmountOfTime = _validPositions.back().GetTime() - _validPositions.front().GetTime();
    for(unsigned long i = 1; (i <= totalAmountOfTime) && (index < _validPositions.size()); i++)
    {
        timeDiff = _validPositions.at(index).GetTime() - _validPositions.at(index - 1).GetTime();
        distance = _validPositions.at(index - 1).CalcDistanceKmTo(_validPositions.at(index));
      //  cout << "Time diff is: " << timeDiff << endl;
        if(timeDiff != 1) //&& _velocities.size() != 0)
        {
            currVelocity = ((distance * 1.0) / (timeDiff * 1.0)) * 3600;
            unsigned long count = timeDiff;
            while(count > 0)
            {
                _velocities.push_back(currVelocity);//_velocities.at(_velocities.size() - 1));
                count--;
            }
        }
        else
        {
//            cout << "I'm passing in Long: " << _validPositions.at(index - 1).GetLongitude() << " Lat: " << _validPositions.at(index -1).GetLatitude() << endl;
//            cout << "To Long: " << _validPositions.at(index).GetLongitude() << " Lat: " << _validPositions.at(index).GetLatitude() << endl;
          //  cout << "Distance is " << distance << endl;
            currVelocity = ((distance * 1.0) / (timeDiff * 1.0)) * 3600;
            _velocities.push_back(currVelocity);
        }
        index++;
    }
    
//    for(unsigned int i = 0; i < _velocities.size(); i++)
//    {
//        cout << "Velocity is: " << _velocities.at(i) << endl;
//    }
    
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
    ofstream outputFile;
    cout << "Opening file" << _outputFilePath << endl;
    outputFile.open(_outputFilePath);
    if (!outputFile.is_open())//check if file is open
    {
        cout << "Could not open file: " << _outputFilePath << endl;
    }
    else
    {
        if(_velocities.size() == 0 || _validPositions.size() == 0)
        {
            cout << "Velocities has size: " << _velocities.size() << " and validPositions has size: " << _validPositions.size() << endl;
            outputFile.close();
            return;
        }
        else
        {
            //cout << _validPositions.back().GetTime() << endl;
            unsigned long firstTimeVal = _validPositions.front().GetTime() + 1;
            for(unsigned int i = 0; i < _velocities.size(); i++)
            {
                unsigned long newTime = firstTimeVal + i;
                outputFile << newTime << " " << _velocities.at(i) << endl;
            }
        }
    }
    outputFile.close();
        
        
        
}
