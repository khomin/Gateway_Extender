#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <iostream>
#include <string>

namespace settings {

class Settings {
    public:
    Settings();
    ~Settings();

    bool isInited() const;
    bool setInit(std::string jsonData);

    auto getInterfaceProperty() const;
};

}

#endif