Course Name: ece275 <br>
Author: <br>
NetID: <br>
Date: <br>
Project Name: project_10

# Description:
## Velociplotter
In this extra credit assignment, you will create a C++ application that analyzes a log of GPS coordinates to calculate the average velocity for every second within the recorded time period.

## Classes
You will be given **two** class to begin with. It is up to you to create other classes to analyze the GPS data.

The first class is called **GPSPosition** and it represents a GPS position that has parsed from a GPS sentence.

The second class is called **Velociplotter** and represents the entire program that you intend to run. The purpose of this class is similar to CarSimulator and Chars in previous projects except that it has only one function called *Run* which takes in only file paths. In this function, you need to call all of the functions you need to run the program from beginning to end. A good program design would be evident by this function calling only a few other select functions that do the bulk of the work of the program just as the endToEnd tests did in the past.

The reason you are given this kind of class is mostly for the sake of grading your projects based on the end-to-end functionality. Since you are now given the freedom to write any functions or classes you choose, it is necessary for the grader to have a common function to call for all submissions in order to grade your project. So, you can think of this function, **Run** as your *main* function.

# Important Requirements
First and foremost, your project will be graded only on the end-to-end functionality. Writing unit tests are optional, but testing and developing your program in smaller steps will save you, and instructors, loads of time. You have been shown examples on how to do this until now.

Second, your program must finish in 5 seconds or less **on the server**. This has actually always been a requirement until now, but in this project, you will be handling substantially larger files at times. Therefore, having efficient algorithms actually becomes important. It is up to you to find the most computationally complex part of this assignment. My suggestion is that you make your program work first, then find the ineffeciencies later through debugging.

# Input File
## Formatting
The *inputFilePath* is formatted according to the following specifications:

1. Each line consists of longitude, latitude, and time using the National Marine Electronics Association (NMEA) GPS sentence definitions. Information on the GPS sentence structure can be found at http://aprs.gids.nl/nmea/. There are also other websites that have the same information.
2. It is not necessary to validate each line with the final value in the GPS sentence called the checksum. In fact, doing so will cause problems.
3. Any other data besides the time, longitude, and latitude information does not need to be validated.
4. The input GPS logs following this format may consist of many different sentence types.

## Processing
The following error checking for the input file should be performed:

1. Any sentence in the input GPS file that does not match the NMEA *$GPGGA* format, should be ignored.
2. The time values read from the file should be increasing. If a time value for a validly formatted *$GPGGA* sentence is earlier than or equal to the time value for a previously read validly formatted line, **your program should report an error and exit immediately.**


# Output File
## Formatting
The *outputFilePath* is the file used to hold the second-by-second average speed.

```
TIME SPEED
```

1. TIME should be output as an integer value (**in seconds**)
2. The two values should be separated by exactly one single space character
3. SPEED should be output as double value using the default precision representing the average speed (**in kilometers per hour**) to be calculated
4. This should be done for **every second** from the first entry in *inputFilePath* to the last entry.
5. Even if a GPS sentence does not exist for a specified second, you must fill in the missing data.
6. The speed at the time of the first GPS reading from the input GPS log cannot be determined as there is no previous GPS location information. Thus, the first output for the GPS plot data file should start **one second after the time of the first GPS reading in the input log file.**

## Calculating Speed
To calculate average speed at the current GPSPosition (x_0) and time (t_0), it is necessary to use the **proceeding** position (x_1) and time (t_1). Average speed in kilometers per hour is calculated according to:

```
average_velocity = (x_1 - x_0)/(t_1 - t_0)
```

This is straight forward when there is a GPS sentence available at time t_0. If there is not, then output the SAME average velocity until the next time where a GPS sentence appears. The following provides an example output for the GPS plot data file. Notice 6, 7, and 8 are repeated because a GPS sentence does not exist for those times.

```
1 34.5434
2 34.2345
3 30.2344
4 27.5434
5 20.12
6 18.22
7 18.22
8 18.22
9 15.3169
10 14.345
```
