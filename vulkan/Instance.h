//
// Created by jpc on 21/06/21.
//

#ifndef VULKANTEST_INSTANCE_H
#define VULKANTEST_INSTANCE_H

#include <vulkan/vulkan_core.h>
#include <vector>

namespace vulkan {
    class Instance {
    private:
        VkInstance handle {VK_NULL_HANDLE};
    public:
        explicit Instance(std::vector<const char *> &extensionNames);
        ~Instance();
        VkInstance instance(){ return handle; }
    };
}


#endif //VULKANTEST_INSTANCE_H
