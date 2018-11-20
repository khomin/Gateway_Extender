#ifndef INTERFACE_SERIAL_H_
#define INTERFACE_SERIAL_H_

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include "interfaces/interfaceAbstract.h"
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>

class InterfaceSerial : public InterfaceAbstract {
  public:
    InterfaceSerial(const InterfaceAbstract::sInterfaceProperty & property);
    ~InterfaceSerial();    
    bool setProperty(const sInterfaceProperty & interface) override;
    bool openConnection() override;
    bool remove() override;
    bool writeData(uint8_t* data, uint16_t len) override;
    int readData(uint8_t* data) override;
    bool getIsConnected() override;
    std::string getStatus() override;

  private:
    sInterfaceProperty property;
    struct termios tty;
    int ioDescription;
    bool isConnected;
};

#endif