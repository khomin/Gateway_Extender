#include "interfaceSerial.h"
#include <limits>
#define FD_NOT_OPEN     -1

InterfaceSerial::InterfaceSerial(const InterfaceAbstract::sInterfaceProperty & property)
 : isConnected(false), ioDescription(FD_NOT_OPEN)
{
    setProperty(property);
}

InterfaceSerial::~InterfaceSerial() {
    close(ioDescription);
    ioDescription = FD_NOT_OPEN;
}

bool InterfaceSerial::setProperty(const sInterfaceProperty & interface) {
    property = interface;
    if(ioDescription != FD_NOT_OPEN) {
        close(ioDescription);
    }
    ioDescription = open(interface.portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if(ioDescription != FD_NOT_OPEN) {
        cfsetispeed(&tty, B115200);    // set baud rates
        cfsetospeed(&tty, B115200);
        tty.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
        tcsetattr(ioDescription, TCSANOW, &tty);    // apply the settings to the port
        isConnected = true;
        std::cout << " open interface -ok " << interface.portName << std::endl;                
    } else {
        isConnected = false;
        std::cerr << " open interface -error " << interface.portName << std::endl;    
    }
    return isConnected;
}

bool InterfaceSerial::openConnection() {
    return setProperty(property);
}

bool InterfaceSerial::remove() {
    bool res = false;
    isConnected = false;
    if(ioDescription != FD_NOT_OPEN) {
        ioDescription = FD_NOT_OPEN;
        close(ioDescription);
    }
    return res;
}

bool InterfaceSerial::writeData(uint8_t* data, uint16_t len) {
    if(ioDescription != FD_NOT_OPEN) {
        isConnected = (bool) write(ioDescription, data, len);
    }
    return isConnected;
}

int InterfaceSerial::readData(uint8_t* data) {
    if(ioDescription != FD_NOT_OPEN) {
        return read(ioDescription, data, std::numeric_limits<uint16_t>::max());
    }
    return isConnected;
}

bool InterfaceSerial::getIsConnected() {
    return isConnected;
}

std::string InterfaceSerial::getStatus() {
    std::string status = isConnected ? "status -connected" : "status -closed";
    return status;
}