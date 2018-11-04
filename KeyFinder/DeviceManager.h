#ifndef _DEVICE_MANAGER_H
#define _DEVICE_MANAGER_H

#include <stdint.h>
#include <string>
#include <vector>

namespace DeviceManager {

class DeviceManagerException {

public:
    std::string msg;

    DeviceManagerException(const std::string &msg)
    {
        this->msg = msg;
    }
};

class DeviceType {
public:
    enum {
        CUDA = 0,
        OpenCL
    };
};


typedef struct {
    int type;
    int id;
    uint64_t physicalId;
    std::string name;

    uint64_t memory;

    // CUDA device info
    int cudaMajor;
    int cudaMinor;
}DeviceInfo;

std::vector<DeviceInfo> getDevices();

}


#endif