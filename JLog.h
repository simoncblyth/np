#pragma once
/**
JLog.h
=======

Extracted from np/NPU.hh

**/

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <chrono>


struct J
{
    static constexpr const char* LOG_FMT = "%Y-%m-%d %H:%M:%S" ;

    static std::string Log(const char* msg=nullptr);
    static std::string Format(uint64_t t=0, const char* fmt="%FT%T.", int _wsubsec=3 );
    static uint64_t Now();
};


inline std::string J::Log(const char* msg) // static
{
    std::string line = Format(0, LOG_FMT, 3);
    if(msg)
    {
        line += " " ;
        line += msg ;
    }
    return line ;
}

inline std::string J::Format(uint64_t t, const char* fmt, int _wsubsec) // static
{
    // from opticks/sysrap/sstamp.h
    if(t == 0) t = Now() ;
    using Clock = std::chrono::system_clock;
    using Unit  = std::chrono::microseconds  ;
    std::chrono::time_point<Clock> tp{Unit{t}} ;

    std::time_t tt = Clock::to_time_t(tp);

    std::stringstream ss ;
    ss << std::put_time(std::localtime(&tt), fmt ) ;

    if(_wsubsec == 3 || _wsubsec == 6)
    {
        // extract the sub second part from the duration since epoch
        auto subsec = std::chrono::duration_cast<Unit>(tp.time_since_epoch()) % std::chrono::seconds{1};
        auto count = subsec.count() ;
        if( _wsubsec == 3 ) count /= 1000 ;
        ss << "." << std::setfill('0') << std::setw(_wsubsec) << count ;
    }

    std::string str = ss.str();
    return str ;
}

inline uint64_t J::Now() // static
{
    // from opticks/sysrap/sstamp.h
    using Clock = std::chrono::system_clock;
    using Unit  = std::chrono::microseconds ;
    std::chrono::time_point<Clock> t0 = Clock::now();
    return std::chrono::duration_cast<Unit>(t0.time_since_epoch()).count() ;
}

