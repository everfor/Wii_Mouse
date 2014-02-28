#ifndef XimuReceiver_h
#define XimuReceiver_h

#include "InertialAndMagPacket.h"
#include "QuaternionPacket.h"
#include "DigitalIOPacket.h"

//------------------------------------------------------------------------------
// Definitions

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

//------------------------------------------------------------------------------
// Class declaration

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

//------------------------------------------------------------------------------
// End of file