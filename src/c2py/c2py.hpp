#pragma once

#define C2PY_VERSION_MAJOR_CURRENT 0
#define C2PY_VERSION_MINOR_CURRENT 1
#ifdef C2PY_VERSION_MAJOR
#if (C2PY_VERSION_MAJOR != C2PY_VERSION_MAJOR_CURRENT) or (C2PY_VERSION_MINOR != C2PY_VERSION_MINOR_CURRENT)
#error "c2py bindings have been generated for a different version of c2py compared to the one included."
#endif
#endif

#include <Python.h>
#include <type_traits>

// The macro C2PY_INCLUDED is defined either here, when including the c2py
// or as a compiler option in the clair clang_plugin target to make
// sure it is always defined before the user's code, in case the user has not included c2py FIRST.
// TRIQS libraries will then automatically include their converters/hxx
#ifndef C2PY_INCLUDED
#define C2PY_INCLUDED
#endif

#include "module.hpp"

#include "macros.hpp"
#include "py_converter.hpp"
#include "converters/basic_types.hpp"

#include "converters/complex.hpp"
#include "converters/map.hpp"
#include "converters/optional.hpp"
#include "converters/pair.hpp"
#include "converters/set.hpp"
#include "converters/std_array.hpp"
#include "converters/string.hpp"
#include "converters/variant.hpp"
#include "converters/vector.hpp"

#include "pytypes.hpp"
#include "pycfun_kw.hpp"
#include "binaryfunc.hpp"
#include "dispatcher.hpp"

#include "specialmethods.hpp"
#include "serialization.hpp"

// some special converters
#include "enums.hpp"
#include "callable.hpp"

#include "py_range.hpp"
#include "synth_constructor.hpp"
