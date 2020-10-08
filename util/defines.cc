#include "kg/util/defines.hh"

#include "kg_features.hh"

#ifdef KG_PLATFORM_WIN
std::string const kg::HELPER_BINARY { "kg.helper.exe" };
#else
std::string const kg::HELPER_BINARY { "kg.helper" };
#endif
