#include "kg/util/defines.hh"

#ifdef _WIN32
std::string const kg::HELPER_BINARY { "kg.helper.exe" };
#else
std::string const kg::HELPER_BINARY { "kg.helper" };
#endif
