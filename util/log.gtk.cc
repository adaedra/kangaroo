#include "kg/util/log.hh"

#include <iostream>

kg::log::~log() {
    std::clog << _stream.str() << std::endl;
}
