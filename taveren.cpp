/// /taveren.cpp --

/// Author: Zhang Yichao <echaozh@gmail.com>
/// Created: 2013-03-21
///

#include "taveren.hpp"

#include <luapp/luapp.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using namespace luapp;
using namespace std;

static pair<string, size_t> extract_script (const string &pattern, size_t nc) {
    string script;
    for (size_t i = nc; i < pattern.size (); ++i) {
        auto c = pattern[i];
        switch (c) {
        case '\\':
            script += pattern[++i];
            break;
        case '}':
            return make_pair (script, i + 1);
        default:
            script += c;
        }
    }
    throw runtime_error (string ("embedded script not properly closed")
                         + pattern);
}

static tuple<string, string, size_t>
parse_pattern (const string &pattern, size_t nc) {
    string lit;
    for (size_t i = nc; i < pattern.size (); ++i) {
        auto c = pattern[i];
        switch (c) {
        case '\\':
            lit += pattern[++i];
            break;
        case '#':
            if (pattern[i + 1] == '{') {
                auto r = extract_script (pattern, i + 2);
                return make_tuple (lit, r.first, r.second);
            }
            // FALLTHROUGH
        default:
            lit += c;
        }
    }
    return make_tuple (lit, string (""), pattern.size ());
}

namespace vobile {
    string format_string (const string &pattern, const string &ctx,
                          const string &utils_file, const string &init) {
        lua l;
        l.load_safe_libs ();
        // set ctx string into lua
        value<string> (l, "__ctxstr__").set (ctx);
        // parse the ctx as json, as merge into global scope
        l.load ("print(__ctxstr__)\njson = require ('json')\n"
                "for k, v in pairs (json.decode (__ctxstr__)) do\n"
                "  _G[k] = v\n"
                "end\n"
                "__ctxstr__ = nil");

        if (!utils_file.empty ()) {
            ifstream in (utils_file.c_str ());
            if (!in.is_open ()) {
                throw runtime_error (string ("utils file not found")
                                     + utils_file);
            }
            in.seekg (0, ios::end);
            vector<char> buf ((size_t) in.tellg () + 1);
            in.seekg (0, ios::beg);
            in.read (&buf[0], buf.size () - 1);
            buf[buf.size () - 1] = 0;
            l.load (&buf[0]);
        }
        if (!init.empty ())
            l.load (init.c_str ());

        string fh = "__res__ = (function ()\n  return ", ff = "\nend) ()";
        ostringstream s;
        size_t nc = 0;
        while (nc < pattern.size ()) {
            auto r = parse_pattern (pattern, nc);
            l.load ((fh + get<1> (r) + ff).c_str ());
            s << get<0> (r) << value<string> (l, "__res__").get ();
            nc = get<2> (r);
        }

        return s.str ();
    }
}
