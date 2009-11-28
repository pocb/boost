// Boost uuid.hpp header file  ----------------------------------------------//

// Copyright 2006 Andy Tompkins.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Revision History
//  06 Feb 2006 - Initial Revision
//  09 Nov 2006 - fixed variant and version bits for v4 guids
//  13 Nov 2006 - added serialization
//  17 Nov 2006 - added name-based guid creation
//  20 Nov 2006 - add fixes for gcc (from Tim Blechmann)
//  07 Mar 2007 - converted to header only
//  10 May 2007 - removed need for Boost.Thread
//              - added better seed - thanks Peter Dimov
//              - removed null()
//              - replaced byte_count() and output_bytes() with size() and begin() and end()
//  11 May 2007 - fixed guid(ByteInputIterator first, ByteInputIterator last)
//              - optimized operator>>
//  14 May 2007 - converted from guid to uuid
//  29 May 2007 - uses new implementation of sha1
//  01 Jun 2007 - removed using namespace directives
//  09 Nov 2007 - moved implementation to uuid.ipp file
//  12 Nov 2007 - moved serialize code to uuid_serialize.hpp file
//  25 Feb 2008 - moved to namespace boost::uuids
//  19 Mar 2009 - changed to a POD, reorganized files

#ifndef BOOST_UUID_HPP
#define BOOST_UUID_HPP

#include <boost/config.hpp>
#include <stddef.h>
#include <boost/cstdint.hpp>
#include <algorithm>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_pod.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
    using ::size_t
    using ::ptrdiff_t
} //namespace std
#endif //BOOST_NO_STDC_NAMESPACE

namespace boost {
namespace uuids {

struct uuid
{
public:
    typedef uint8_t value_type;
    typedef uint8_t& reference;
    typedef uint8_t const& const_reference;
    typedef uint8_t* iterator;
    typedef uint8_t const* const_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    enum { static_size = 16 };

public:
    iterator begin() { return data; } /* throw() */
    const_iterator begin() const { return data; } /* throw() */
    iterator end() { return data+size(); } /* throw() */
    const_iterator end() const { return data+size(); } /* throw() */

    size_type size() const { return static_size; } /* throw() */

    bool is_nil() const /* throw() */
    {
        // could be more efficient by stopping at the firt
        // non zero
        return (std::count(begin(), end(), 0) == static_size);
    }

    enum variant_type
    {
        variant_ncs, // NCS backward compatibility
        variant_rfc_4122, // defined in RFC 4122 document
        variant_microsoft, // Microsoft Corporation backward compatibility
        variant_future // future definition
    };
    variant_type variant() const /* throw() */
    {
        // variant is stored in octet 7
        // which is index 8, since indexes count backwards
        unsigned char octet7 = data[8]; // octet 7 is array index 8
        if ( (octet7 & 0x80) == 0x00 ) { // 0b0xxxxxxx
            return variant_ncs;
        } else if ( (octet7 & 0xC0) == 0x80 ) { // 0b10xxxxxx
            return variant_rfc_4122;
        } else if ( (octet7 & 0xE0) == 0xC0 ) { // 0b110xxxxx
            return variant_microsoft;
        } else {
            //assert( (octet7 & 0xE0) == 0xE0 ) // 0b111xxxx
            return variant_future;
        }
    }
    
    enum version_type 
    {
        version_unknown = -1,
        version_time_based = 1,
        version_dce_security = 2,
        version_name_based_md5 = 3,
        version_random_number_based = 4,
        version_name_based_sha1 = 5
    };
    version_type version() const /* throw() */
    {
        //version is stored in octet 9
        // which is index 6, since indexes count backwards
        unsigned char octet9 = data[6];
        if ( (octet9 & 0xF0) == 0x10 ) {
            return version_time_based;
        } else if ( (octet9 & 0xF0) == 0x20 ) {
            return version_dce_security;
        } else if ( (octet9 & 0xF0) == 0x30 ) {
            return version_name_based_md5;
        } else if ( (octet9 & 0xF0) == 0x40 ) {
            return version_random_number_based;
        } else if ( (octet9 & 0xF0) == 0x50 ) {
            return version_name_based_sha1;
        } else {
            return version_unknown;
        }
    }

    // note: linear complexity
    void swap(uuid& rhs) /* throw() */
    {
        std::swap_ranges(begin(), end(), rhs.begin());
    }

public:
    // or should it be array<uint8_t, 16>
    uint8_t data[static_size];
};

inline bool operator==(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline bool operator!=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(lhs == rhs);
}

inline bool operator<(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

inline bool operator>(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return rhs < lhs;
}
inline bool operator<=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(rhs < lhs);
}

inline bool operator>=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(lhs < rhs);
}

inline void swap(uuid& lhs, uuid& rhs) /* throw() */
{
    lhs.swap(rhs);
}

// This is equivalent to boost::hash_range(u.begin(), u.end());
inline std::size_t hash_value(uuid const& u) /* throw() */
{
    std::size_t seed = 0;
    for(uuid::const_iterator i=u.begin(); i != u.end(); ++i)
    {
        seed ^= static_cast<std::size_t>(*i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
}

}} //namespace boost::uuids

// type traits specializations
namespace boost {

template <>
struct is_pod<uuids::uuid> : mpl::true_
{};

} // namespace boost

#endif // BOOST_UUID_HPP
