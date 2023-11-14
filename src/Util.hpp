#ifndef Util_H
#define Util_H

#include <string>

namespace bsdpNode {
#ifdef _WIN32
    std::string Utf8ToAnsi(const std::string& utf8str);
#endif
}

#endif  // Util_H