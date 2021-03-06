/*
    XimuReceiver.cpp
    Original Author: Seb Madgwick

    C++ library for receiving data from the x-IMU.  Modified by Alan Yang for the particular needs of this project
*/
#ifndef XimuReceiver_h
#define XimuReceiver_h

#include "InertialAndMagPacket.h"
#include "QuaternionPacket.h"
#include "DigitalIOPacket.h"

typedef enum {
    ERR_NO_ERROR,
    ERR_FACTORY_RESET_FAILED,
    ERR_LOW_BATTERY,
    ERR_USB_RECEIVE_BUFFER_OVERRUN,
    ERR_USB_TRANSMIT_BUFFER_OVERRUN,
    ERR_BLUETOOTH_RECEIVE_BUFFER_OVERRUN,
    ERR_BLUETOOTH_TRANSMIT_BUFFER_OVERRUN,
    ERR_SD_CARD_WRITE_BUFFER_OVERRUN,
    ERR_TOO_FEW_BYTES_IN_PACKET,
    ERR_TOO_MANY_BYTES_IN_PACKET,
    ERR_INVALID_CHECKSUM,
    ERR_UNKNOWN_HEADER,
    ERR_INVALID_NUM_BYTES_FOR_PACKET_HEADER,
    ERR_INVALID_REGISTER_ADDRESS,
    ERR_REGISTER_READ_ONLY,
    ERR_INVALID_REGSITER_VALUE,
    ERR_INVALID_COMMAND,
    ERR_GYROSCOPE_AXIS_NOT_AT_200DPS,
    ERR_GYROSCOPE_NOT_STATIONARY,
    ERR_ACCELEROMETER_AXIS_NOT_AT_1G,
    ERR_MMAGNETOMETER_SATURATION,
    ERR_INCORRECT_AUXILIARY_PORT_MODE,
    ERR_UART_RECEIVE_BUFFER_OVERRUN,
    ERR_UART_TRANSMIT_BUFFER_OVERRUN,
} ErrorCode;

enum PacketHeaders {
    PKT_ERROR,
    PKT_COMMAND,
    PKT_READ_REGISTER,
    PKT_WRITE_REGISTER,
    PKT_READ_DATE_TIME,
    PKT_WRITE_DATE_TIME,
    PKT_RAW_BATTERY_AND_THERMOMETER_DATA,
    PKT_CAL_BATTERY_AND_THERMOMETER_DATA,
    PKT_RAW_INERTIAL_AND_MAGNETIC_DATA,
    PKT_CAL_INERTIAL_AND_MAGNETIC_DATA,
    PKT_QUATERNION_DATA,
    PKT_DIGITAL_IO_DATA,
    PKT_RAW_ANALOGUE_INPUT_DATA,
    PKT_CAL_ANALOGUE_INPUT_DATA,
    PKT_PWM_OUTPUT_DATA,
    PKT_RAW_DXL345_BUS_DATA,
    PKT_CAL_DXL345_BUS_DATA,
};

enum PacketLengths {
    LEN_ERROR = 4,
    LEN_COMMAND = 6,
    LEN_READ_REGISTER = 4,
    LEN_WRITE_REGISTER = 8,
    LEN_READ_DATE_TIME = 2,
    LEN_WRITE_DATE_TIME = 8,
    LEN_RAW_BATTERY_AND_THERMOMETER_DATA = 6,
    LEN_CAL_BATTERY_AND_THERMOMETER_DATA = 6,
    LEN_RAW_INERTIAL_AND_MAGNETIC_DATA = 20,
    LEN_CAL_INERTIAL_AND_MAGNETIC_DATA = 20,
    LEN_QUATERNION_DATA = 10,
    LEN_DIGITAL_IO_DATA = 4,
    LEN_RAW_ANALOGUE_INPUT_DATA = 18,
    LEN_CAL_ANALOGUE_INPUT_DATA = 18,
    LEN_PWM_OUTPUT_DATA = 10,
    LEN_RAW_DXL345_BUS_DATA = 26,
    LEN_CAL_DXL345_BUS_DATA = 26,
};


typedef enum {
    Q_CALIBRATED_BATTERY = 12,
    Q_CALIBRATED_THERMOEMTER = 8,
    Q_CALIBRATED_GYROSCOPE = 4,
    Q_CALIBRATED_ACCELEROEMETER = 11,
    Q_CALIBRATED_MAGNETOMETER = 11,
    Q_QUATERNION = 15,
    Q_BATTERY_SENSITIVITY = 5,
    Q_BATTERY_BIAS = 8,
    Q_THERMOMETER_SENSITIVITY = 6,
    Q_THERMOMETER_BIAS = 0,
    Q_GYROSCOPE_SENSITIVITY = 7,
    Q_GYROSCOPE_SAMPLED_200DPS = 0,
    Q_GYROSCOPE_BIAS_AT_25DEGC = 3,
    Q_GYROSCOPE_BIAS_TEMP_SENSITIVITY = 11,
    Q_GYROSCOPE_SAMPLED_BIAS = 3,
    Q_ACCELEROMETER_SENSITIVITY = 4,
    Q_ACCELEROMETER_BIAS = 8,
    Q_ACCELEROMETER_Sampled1g = 4,
    Q_MAGNETOMETER_SENSITIVITY = 4,
    Q_MAGNETOMETER_BIAS = 8,
    Q_MAGNETOMETER_HARD_IRON_BIAS = 11,
    Q_ALGORITHM_KP = 11,
    Q_ALGORITHM_KI = 15,
    Q_ALGORITHM_INIT_KP = 11,
    Q_ALGORITHM_INIT_PERIOD = 11,
    Q_CALIBRATED_ANALOGUE_INPUT = 12,
    Q_ANALOGUE_INPUT_SENSITIVITY = 4,
    Q_ANALOGUE_INPUT_BIAS = 8,
    Q_CALIRBATED_ADXL345 = 10,
    Q_ADXL345_BUS_SENSITIVITY = 6,
    Q_ADXL345_BUS_BIAS = 8,
} FixedQ;

class XimuReceiver {
	QuaternionPacket quaternionPacket;
	InertialandMagPacket inertialPacket;
	DigitalIOPacket digitalIOPacket;

    public:
        XimuReceiver(void);
        ErrorCode processNewChar(unsigned char c);
        bool isInertialAndMagGetReady(void) const;
        bool isQuaternionGetReady(void) const;
		bool isDigitalGetReady(void) const;
        InertialandMagPacket getInertialAndMag(void);
        QuaternionPacket getQuaternion(void);
		DigitalIOPacket getDigitalReading(void);

    private:
        unsigned char buf[256];
        unsigned char bufIndex;
        bool inertialAndMagGetReady;
        bool quaternionGetReady;
		bool digitalGetReady;
        float fixedToFloat(const short fixed, const unsigned char q) const;
        unsigned short concat(const unsigned char msb, const unsigned char lsb) const;
};

#endif