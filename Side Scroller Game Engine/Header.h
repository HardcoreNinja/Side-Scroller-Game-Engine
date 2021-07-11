#ifndef HEADER_H
#define HEADER_H
//Input/output library
#include <iosfwd>	          // forward declarations of all classes in the input / output library
#include <ios>	              // std::ios_base class, std::basic_ios class templateand several typedefs
#include <istream>	          // std::basic_istream class templateand several typedefs
#include <ostream>	          // std::basic_ostream, std::basic_iostream class templatesand several typedefs
#include <iostream>	          // several standard stream objects
#include <fstream>	          // std::basic_fstream, std::basic_ifstream, std::basic_ofstream class templatesand several typedefs
#include <sstream>	          // std::basic_stringstream, std::basic_istringstream, std::basic_ostringstream class templatesand several typedefs
//#include <strstream>          // std::strstream, std::istrstream, std::ostrstream(deprecated)
#include <iomanip >           // Helper functions to control the format or input and output
#include <streambuf>          // std::basic_streambuf class template
#include <cstdio>             // C-style input-output functions

//Containers library
#include <array >             // (since C++11) std::array container
#include <vector>	          // std::vector container
#include <deque>	          // std::deque container
#include <list>	              // std::list container
#include <forward_list>       // (since C++11) std::forward_list container
#include <set>	              // std::setand std::multiset associative containers
#include <map>	              // std::mapand std::multimap associative containers
#include <unordered_set>      // (since C++11) std::unordered_setand std::unordered_multiset unordered associative containers
#include <unordered_map>      // (since C++11) std::unordered_mapand std::unordered_multimap unordered associative containers
#include <stack>	          // std::stack container adaptor
#include <queue>	          // std::queueand std::priority_queue container adaptors

//Strings library
#include <cctype >            // functions to determine the type contained in character data
#include <cwctype>            // functions for determining the type of wide character data
#include <cstring>	          // various narrow character string handling functions
#include <cwchar>	          // various wideand multibyte string handling functions
#include <cuchar>             // (since C++11) C - style Unicode character conversion functions
#include <string>	          // std::basic_string class template

//Utilities library
#include <cstdlib>	          // General purpose utilities : program control, dynamic memory allocation, random numbers, sortand search
#include <csignal>	          // Functionsand macro constants for signal management
#include <csetjmp>	          // Macro(and function) that saves(and jumps) to an execution context
#include <cstdarg>	          // Handling of variable length argument lists
#include <typeinfo>	          // Runtime type information utilities
#include <typeindex>          // (since C++11) std::type_index
#include <type_traits>        // (since C++11) Compile - time type information
#include <bitset>	          // std::bitset class template
#include <functional>         // Function objects, designed for use with the standard algorithms
#include <utility>	          // Various utility components
#include <ctime>	          // C - style time / date utilites
#include <chrono>             // (since C++11) C++ time utilites
#include <cstddef>	          // typedefs for types such as size_t, NULLand others
#include <initializer_list>   // (since C++11) std::initializer_list class template
#include <tuple>              // (since C++11) std::tuple class template

//Dynamic memory management
#include <new>	              // Low - level memory management utilities
#include <memory>	          // Higher level memory management utilities
#include <scoped_allocator>   // (since C++11)	Nested allocator class

//Numeric limits
#include <climits>	          // limits of integral types
#include <cfloat>	          // limits of float types
#include <cstdint>            // (since C++11) fixed - size types and limits of other types
#include <cinttypes>          // (since C++11) formatting macros, intmax_tand uintmax_t mathand conversions
#include <limits>	          // standardized way to query properties of fundamental types

//Error handling
#include <exception>	      // Exception handling utilities
#include <stdexcept>	      // Standard exception objects
#include <cassert>	          // Conditionally compiled macro that compares its argument to zero
#include <system_error>       // (since C++11) defines std::error_code, a platform - dependent error code
#include <cerrno>	          // Macro containing the last error number

//Localization library
#include <locale>	          // Localization utilities
#include <clocale>	          // C localization utilities
#include <codecvt>            // (since C++11) Unicode conversion facilities

//Regular Expressions library
#include <regex>              // (since C++11) Classes, algorithmsand iterators to support regular expression processing

//Atomic Operations library
#include <atomic>             // (since C++11) Atomic operations library

//Thread support library
#include <thread>             // (since C++11) std::thread classand supporting functions
#include <mutex>              // (since C++11) mutual exclusion primitives
#include <shared_mutex>       // (since C++14) shared mutual exclusion primitives
#include <future>             // (since C++11) primitives for asynchronous computations
#include <condition_variable> // (since C++11) thread waiting conditions

//C compatibility headers
#include <ciso646>	          // empty header. The macros that appear in iso646.h in C are keywords in C++
//#include <ccomplex>           // (since C++11) simply includes the header <complex>
//#include <ctgmath>            // (since C++11) simply includes the headers <ccomplex>and <cmath>: the overloads equivalent to the contents of the C header tgmath.h are already provided by <cmath>and <complex>
//#include <cstdalign>          // (since C++11) defines one compatibility macro constant
//#include <cstdbool>           // (since C++11) defines one compatibility macro constant

/*SFML Libs*/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#endif
