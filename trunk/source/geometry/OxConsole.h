#ifndef OXCONSOLE_H
#define OXCONSOLE_H

#include "OxGeometry.h"
#include <iostream>


namespace oxtorne {

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const point<T,D>& _p) {
        os << "(";
        for (std::size_t i = 0; i < D; ++i)
            os << std::showpoint << _p[i] << (i == D - 1 ? "" : ",");
        os << ")";
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const sphere<T,D>& _s) {
        os << "(";
        for (std::size_t i = 0; i < D; ++i)
            os << std::showpoint << _s[i] << ",";
        os << "radius:" << std::showpoint << _s.radius << ")";
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const ray<T,D>& _r) {
        os << "(" << _r.origin;
        os << "," << _r.direction << ")";
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const plane<T,D>& _p) {
        os << "(";
        for (std::size_t i = 0; i < D; ++i)
            os << std::showpoint << _p[i] << ",";
        os << "constant:" << std::showpoint << _p.constant << ")";
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const box<T,D>& _b) {
        os <<  "min:" << _b.min;
        os << ",max:" << _b.max;
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const line<T,D>& _l) {
        os << "(" << _l.a;
        os << "," << _l.b << ")";
        return os;
    }

    template<typename T, std::size_t D>
    inline std::ostream& operator<<(std::ostream& os, const triangle<T,D>& _t) {
        os << "(" << _t[0];
        os << "," << _t[1];
        os << "," << _t[2] << ")";
        return os;
    }

};

#endif
