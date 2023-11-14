#ifndef Uitl_H
#define Uitl_H

#include <string>

namespace bsdpNode {
#ifdef WIN32
    std::string Utf8ToAnsi(const std::string& utf8str);
#endif
}

#endif  // Uitl_H