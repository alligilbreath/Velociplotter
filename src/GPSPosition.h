//----------------------------------------------------------------------//
// Author:
// Net ID:
// Date:
//
//----------------------------------------------------------------------//

#ifndef GPSPOSITION_H
#define GPSPOSITION_H

class GPSPosition {
private:
    double _latitude;
    double _longitude;
    unsigned long _timeSeconds;
public:
    GPSPosition(double latitude, double longitude, unsigned long timeSeconds);
    double GetLatitude() const { return _latitude; };
    double GetLongitude() const { return _longitude; };
    unsigned long GetTime() const { return _timeSeconds; };
    void SetLatitude(double latitude) { _latitude = latitude; };
    void SetLongitude(double longitude) { _longitude = longitude; };
    void SetTime(double timeSeconds) { _timeSeconds = timeSeconds; };
    double CalcDistanceKmTo(GPSPosition toPosition);
};
#endif
