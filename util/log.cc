#include "kg/util/log.hh"

kg::log kg::log::debug() {
    return kg::log { "DEBUG" };
}

kg::log kg::log::info() {
    return kg::log { " INFO" };
}

kg::log kg::log::warning() {
    return kg::log { " WARN" };
}

kg::log kg::log::error() {
    return kg::log { "ERROR" };
}

kg::log::log(std::string const & level) : _stream {} {
    _stream << "[" << level << "] ";
}
