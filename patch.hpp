#ifndef PATCH_HPP_INCLUDED
#define PATCH_HPP_INCLUDED
#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
#endif // PATCH_HPP_INCLUDED
