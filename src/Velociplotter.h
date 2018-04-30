//----------------------------------------------------------------------//
// Author:
// Net ID:
// Date:
//
//----------------------------------------------------------------------//

#ifndef VELOCIPLOTTER_H
#define VELOCIPLOTTER_H

#include "GPSPosition.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Velociplotter{
private:
    std::string _inputFilePath;
    std::string _outputFilePath;
    std::vector<GPSPosition> _validPositions;
    std::vector<double> _velocities;
public:
    Velociplotter(std::string inputFilePath, std::string ouputFilePath);
    void Run();
    void ReadInputsFromFile();
    void CalculateAverageVelocities();
    void WriteOutputsToFile();
};
#endif


