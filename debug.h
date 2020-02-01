#ifndef _debug_h
#define _debug_h

#include <iostream>

#define MX_STRLOG(x) std::cout << x
#define MX_LOG(x) MX_STRLOG(x << '\n')

#endif /* _debug_h */