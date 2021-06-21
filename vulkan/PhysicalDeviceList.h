//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_PHYSICALDEVICELIST_H
#define VULKANTEST_PHYSICALDEVICELIST_H


#include <cstddef>
#include "PhysicalDevice.h"

namespace vulkan {
    class PhysicalDeviceList {
    public:
        PhysicalDeviceList(VkInstance h);
        std::vector<PhysicalDevice> devices;
    };
}


#endif //VULKANTEST_PHYSICALDEVICELIST_H
