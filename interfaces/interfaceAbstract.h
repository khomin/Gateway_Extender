#ifndef INTERFACE_ABSTR_H_
#define INTERFACE_ABSTR_H_

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <utility>

class InterfaceAbstract
{
  public:
    InterfaceAbstract();
    ~InterfaceAbstract();

  typedef struct {
    std::string portName;
    std::string portType;
    std::string portBaudrate;
  }sInterfaceProperty;

  virtual bool setProperty(const sInterfaceProperty & interface) = 0;
  virtual bool openConnection() = 0;
  virtual bool remove() = 0;
  virtual bool writeData(uint8_t* data, uint16_t len) = 0;
  virtual int readData(uint8_t * data) = 0;
  virtual bool getIsConnected() = 0;
  virtual std::string getStatus() = 0;
};

#endif