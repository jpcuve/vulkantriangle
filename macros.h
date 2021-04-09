//
// Created by jpc on 9/04/21.
//

#ifndef VULKANTEST_MACROS_H
#define VULKANTEST_MACROS_H

#ifdef NDEBUG
#define DEBUG(x)
#define DEBUG1(x, y)
#else
#define DEBUG(x) do { std::cout << (x) << std::endl; } while (0)
#define DEBUG1(x, y) do { std::cout << (x) << (y) << std::endl; } while (0)
#endif

#endif //VULKANTEST_MACROS_H
