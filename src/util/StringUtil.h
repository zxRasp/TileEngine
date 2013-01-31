#ifndef _SRING_UTIL_H_
#define _SRING_UTIL_H_

#include <sstream>
#include <string>

template <class T>
std::string convertToString(const T& object)
{
    std::stringstream ss;
    ss << object;
    return ss.str();
}

#endif //_SRING_UTIL_H_
