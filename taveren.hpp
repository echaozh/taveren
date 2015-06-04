/// /taveren.hpp --

/// Author: Zhang Yichao <echaozh@gmail.com>
/// Created: 2013-03-22
///

#ifndef INCLUDED_TAVEREN_HPP
#define INCLUDED_TAVEREN_HPP

#include <string>

namespace vobile {
    std::string format_string (const std::string &pattern,
                               const std::string &ctx,
                               const std::string &utils_file
                               = "format_utils.lua",
                               const std::string &init = "");
};

#endif // INCLUDED_TAVEREN_HPP
