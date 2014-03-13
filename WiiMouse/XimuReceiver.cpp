/*
    XimuReceiver.cpp
    Original Author: Seb Madgwick

    C++ library for receiving data from the x-IMU.  Modified by Alan Yang for the particular needs of this project
*/
#include "stdafx.h"
#include "XimuReceiver.h"
#include <iostream>

// Serial stream decoding
unsigned char buf[256];
unsigned char bufIndex = 0;

// Data ready flags
bool inertialAndMagGetReady = false;
bool quaternionGetReady = false;
bool digitalGetReady = false;

XimuReceiver::XimuReceiver() {
	// Decoded Packet
	QuaternionPacket quaternionPacket;
	InertialandMagPacket inertialPacket;
	DigitalIOPacket digitalIOPacket;
}

ErrorCode XimuReceiver::processNewChar(unsigned char c) {

    // Add new byte to buffer
    buf[bufIndex++] = c;

    // Process receive buffer if framing char received
    if(c & 0x80) {

        // Calculate packet size
        int packetSize = bufIndex - 1 - ((bufIndex - 1) >> 3);
        bufIndex = 0;

        // Extract packet (truncate to discard all msb)
        unsigned char packet[256];
        packet[0]  = (buf[0 ] << 1) | (buf[1 ] >> 6);
        packet[1]  = (buf[1 ] << 2) | (buf[2 ] >> 5);
        packet[2]  = (buf[2 ] << 3) | (buf[3 ] >> 4);
        packet[3]  = (buf[3 ] << 4) | (buf[4 ] >> 3);
        packet[4]  = (buf[4 ] << 5) | (buf[5 ] >> 2);
        packet[5]  = (buf[5 ] << 6) | (buf[6 ] >> 1);
        packet[6]  = (buf[6 ] << 7) | (buf[7 ] >> 0);
        packet[7]  = (buf[8 ] << 1) | (buf[9 ] >> 6);
        packet[8]  = (buf[9 ] << 2) | (buf[10] >> 5);
        packet[9]  = (buf[10] << 3) | (buf[11] >> 4);
        packet[10] = (buf[11] << 4) | (buf[12] >> 3);
        packet[11] = (buf[12] << 5) | (buf[13] >> 2);
        packet[12] = (buf[13] << 6) | (buf[14] >> 1);
        packet[13] = (buf[14] << 7) | (buf[15] >> 0);
        packet[14] = (buf[16] << 1) | (buf[17] >> 6);
        packet[15] = (buf[17] << 2) | (buf[18] >> 5);
        packet[16] = (buf[18] << 3) | (buf[19] >> 4);
        packet[17] = (buf[19] << 4) | (buf[20] >> 3);
        packet[18] = (buf[20] << 5) | (buf[21] >> 2);
        packet[19] = (buf[21] << 6) | (buf[22] >> 1);
        packet[20] = (buf[22] << 7) | (buf[23] >> 0);
        packet[21] = (buf[24] << 1) | (buf[25] >> 6);
        packet[22] = (buf[25] << 2) | (buf[26] >> 5);
        packet[23] = (buf[26] << 3) | (buf[27] >> 4);
        packet[24] = (buf[27] << 4) | (buf[28] >> 3);
        packet[25] = (buf[28] << 5) | (buf[29] >> 2);
        packet[26] = (buf[29] << 6) | (buf[30] >> 1);
        packet[27] = (buf[30] << 7) | (buf[31] >> 0);

        // Interpret packet according to header
        switch(packet[0]) {
            case(PKT_CAL_INERTIAL_AND_MAGNETIC_DATA):
                if(packetSize != LEN_CAL_INERTIAL_AND_MAGNETIC_DATA) {
                    return ERR_INVALID_NUM_BYTES_FOR_PACKET_HEADER;
                }
				inertialPacket.update(fixedToFloat(concat(packet[1], packet[2]), Q_CALIBRATED_GYROSCOPE),
									fixedToFloat(concat(packet[3], packet[4]), Q_CALIBRATED_GYROSCOPE),
									fixedToFloat(concat(packet[5], packet[6]), Q_CALIBRATED_GYROSCOPE),
									fixedToFloat(concat(packet[7], packet[8]), Q_CALIBRATED_ACCELEROEMETER),
									fixedToFloat(concat(packet[9], packet[10]), Q_CALIBRATED_ACCELEROEMETER),
									fixedToFloat(concat(packet[11], packet[12]), Q_CALIBRATED_ACCELEROEMETER),
									fixedToFloat(concat(packet[13], packet[14]), Q_CALIBRATED_MAGNETOMETER),
									fixedToFloat(concat(packet[15], packet[16]), Q_CALIBRATED_MAGNETOMETER),
									fixedToFloat(concat(packet[17], packet[18]), Q_CALIBRATED_MAGNETOMETER));
                inertialAndMagGetReady = true;
                break;

            case(PKT_QUATERNION_DATA):
                if(packetSize != LEN_QUATERNION_DATA) {
                    return ERR_INVALID_NUM_BYTES_FOR_PACKET_HEADER;
                }
				quaternionPacket.update(fixedToFloat(concat(packet[1], packet[2]), Q_QUATERNION),
										fixedToFloat(concat(packet[3], packet[4]), Q_QUATERNION),
										fixedToFloat(concat(packet[5], packet[6]), Q_QUATERNION),
										fixedToFloat(concat(packet[7], packet[8]), Q_QUATERNION));
                quaternionGetReady = true;
                break;
			
			case(PKT_DIGITAL_IO_DATA):
				if(packetSize != LEN_DIGITAL_IO_DATA) {
					return ERR_INVALID_NUM_BYTES_FOR_PACKET_HEADER;
				}
				digitalIOPacket.update(packet[1], packet[2]);
				digitalGetReady = true;
				break;

            default:
                break;
        }
    }
    return ERR_NO_ERROR;
}

float XimuReceiver::fixedToFloat(const short fixed, const unsigned char q) const {
    return (float)fixed / (float)(1 << q);
}

unsigned short XimuReceiver::concat(const unsigned char msb, const unsigned char lsb) const {
    return ((unsigned short)msb << 8) | (unsigned short)lsb;
}

bool XimuReceiver::isInertialAndMagGetReady(void) const {
    return inertialAndMagGetReady;
}

bool XimuReceiver::isQuaternionGetReady(void) const {
    return quaternionGetReady;
}

bool XimuReceiver::isDigitalGetReady(void) const {
	return digitalGetReady;
}

InertialandMagPacket XimuReceiver::getInertialAndMag(void) {
	inertialAndMagGetReady = false;
    return inertialPacket;
}

QuaternionPacket XimuReceiver::getQuaternion(void) {
	quaternionGetReady = false;
    return quaternionPacket;
}

DigitalIOPacket XimuReceiver::getDigitalReading(void) {
	digitalGetReady = false;
	return digitalIOPacket;
}

//------------------------------------------------------------------------------
// End of file