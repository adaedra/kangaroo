#pragma once
#include <sstream>
#include <string>

namespace kg {
    class log {
    public:
        ~log();

        static log debug();
        static log info();
        static log warning();
        static log error();

        template <typename T> log & operator<<(T t) {
            _stream << t;
            return *this;
        }

    private:
        log(std::string const & level);

        std::stringstream _stream;
    };

    template <typename T>
    inline T __log_traced(char const * func, char const * file, unsigned int line, char const * value_name, T t) {
        kg::log::debug() << func << "(" << file << ":" << line << ") " << value_name << " = " << t;
        return t;
    }
}

#define KG_LOG_TRACE() kg::log::debug() << __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"
#define KG_LOG_SHOW(v) kg::__log_traced(__FUNCTION__, __FILE__, __LINE__, #v, (v))
#define KG_LOG_VAR(v) #v << " = " << (v)
