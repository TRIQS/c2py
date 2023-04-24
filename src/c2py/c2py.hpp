#pragma once
#include <Python.h>
#include <type_traits>

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

// FIXME include explicitly ??
#include "h5.hpp"
