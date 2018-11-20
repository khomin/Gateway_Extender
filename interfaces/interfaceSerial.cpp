#include "interfaceSerial.h"

InterfaceSerial::InterfaceSerial(const InterfaceAbstract::sInterfaceProperty & property) : isConnected(false) {
    setProperty(property);
}

InterfaceSerial::~InterfaceSerial() {
}   

bool InterfaceSerial::setProperty(const sInterfaceProperty & interface) {
    if((property.portName != interface.portName) && (property.portType != interface.portType)) {
        property = interface;
        if(open(interface.portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY) !=-1) {
            isConnected = true;
            std::cout << " open interface -ok " << interface.portName << std::endl;                
        } else {
            isConnected = false;
            std::cerr << " open interface -error " << interface.portName << std::endl;
        }
    } else {
        // todo: close and restrore
    }
}

bool InterfaceSerial::remove() {
    bool res = false;
    isConnected = false;
    return res;
}

bool InterfaceSerial::writeData(uint8_t* data, uint16_t len) {

}

int InterfaceSerial::readData(uint8_t* data) {

}

bool InterfaceSerial::getIsConnected() {
    return isConnected;
}

std::string InterfaceSerial::getStatus() {
    std::string status = isConnected ? "status -connected" : "status -closed";
    return status;
}