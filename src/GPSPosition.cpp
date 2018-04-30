//----------------------------------------------------------------------//
// Author:
// Net ID:
// Date:
//
//----------------------------------------------------------------------//

#include "GPSPosition.h"
#include <cmath>

using namespace std;

GPSPosition::GPSPosition()
{
    _latitude = 0;
    _longitude = 0;
    _timeSeconds = 0;
    
}

GPSPosition::GPSPosition(double latitude, double longitude, unsigned long timeSeconds)
{
    _latitude = latitude;
    _longitude = longitude;
    _timeSeconds = timeSeconds;
}

double GPSPosition::CalcDistanceKmTo(GPSPosition toPosition){
    const double EarthRadiusKm = 6371.0;
    const double PI = 3.14159265358979323846;
    
    double fromLatitudeRad;
    double fromLongitudeRad;
    double toLatitudeRad;
    double toLongitudeRad;
    double deltaLatitude;
    
    double deltaLongitude;
    double a;
    double c;
    
    // Convert to radians
    fromLatitudeRad = PI * this->GetLatitude() / 180.0;
    fromLongitudeRad = PI * this->GetLongitude() / 180.0;
    toLatitudeRad = PI * toPosition.GetLatitude() / 180.0;
    toLongitudeRad = PI * toPosition.GetLongitude() / 180.0;
    
    // Calculate delta for latitude and longitude
    deltaLatitude = toLatitudeRad - fromLatitudeRad;
    deltaLongitude = toLongitudeRad - fromLongitudeRad;
    
    // Calculate great-circle distance using haversine formula
    a = ( sin(deltaLatitude / 2) * sin(deltaLatitude / 2) ) +
    ( sin(deltaLongitude / 2) * sin(deltaLongitude / 2) *
     cos(fromLatitudeRad) * cos(toLatitudeRad) );
    c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EarthRadiusKm * c;
}

