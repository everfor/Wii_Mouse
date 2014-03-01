========================================================================
    CONSOLE APPLICATION : WiiMouse Project Overview
========================================================================

This file contains a summary of what you will find in each of the files that
make up your WiiMouse application.

WiiMouse.cpp
    This is the main application source file.

InertialAndMagPacket.h, InertialAndMagPacket.cpp
QuaternionPacket.h, QuaternionPacket.cpp
DigitalIOPacket.h, DigitalIOPacket.cpp
	Classes to store data from decoded packets from Ximu

Quaternion.h, Quaternion.cpp
EulerAngles.h, EulerAngles.cpp
	Classes used to store orientation data. Contains necessary
	calculations.

XimuReceiver.h, Ximureceiver.cpp
	Reader class that reads and parses packets from Ximu

Utils.h, Utils.cpp
	Utility functions

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named WiiMouse.pch and a precompiled types file named StdAfx.obj.
