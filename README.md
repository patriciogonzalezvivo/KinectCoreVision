# MacOSX Pre-Requisit #

Macports is required to be installed. Please check http://www.macports.org/ for its own dependencies and installation procedure. It requires XCode and would need to be installed on your Mac. Then: 

```sudo port install libtool```
```sudo port install libusb-devel +universal```

# Linux Pre-Requisit #

```sudo apt-get install cmake libglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev```

# Installing need Drivers #

1- Install last unstable openNI, NITE and PrimeSense drivers
2- Install SensorKinect drivers from https://github.com/avin2/SensorKinect

# Compilling #

1- Download and install last GitHub openFramework version  
2- You can switch or improve ofxOpenNI version by downloading/uploading and installing ofxOpenNI from github.com/gameoverhack/ofxOpenNI
3- On src/ofxOpenNI you will find two subdirectories, one for windows and one for osx. copy the content inside and replace the openni directory on your bin/data one by that one.
4- Open the project that correspond to your OS
5- Compile

[CLICK HERE for more information and videos on how to setup and use it](http://patriciogonzalezvivo.com/kinectcorevision)



