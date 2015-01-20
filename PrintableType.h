//=============================================================================
//
// A printer class which will take any argument, if it can be printed it will.

#ifndef PrintableType_H
#define PrintableType_H

#include <type_traits>
#include <iostream>
#include <typeinfo>

// Note this implementation is from
// http://stackoverflow.com/a/5771273/1548429

//=============================================================================
namespace has_insertion_operator_impl {
  typedef char no;
  typedef char yes[2];

  struct any_t {
    template<typename T>
    any_t(T const& t);
    // Constructor taking any value.
  };

  no operator<<(const std::ostream& os, const any_t& any);

  yes& test(std::ostream&);
  no test(no);

  template<typename T>
  struct has_insertion_operator {
    static std::ostream &s;
    static T const &t;
    static bool const value = sizeof(test(s << t)) == sizeof(yes);
  };
}

//=============================================================================
template<typename T>
struct printable_type : has_insertion_operator_impl::has_insertion_operator<T> {
};

//=============================================================================
template <typename T, bool ENABLE=printable_type<T>::value>
struct Printer {
};

//=============================================================================
template <typename T>
struct Printer<T, false> {
  void execute(std::ostream& os, const T& t) const {
      os << "{" << typeid(T).name() << ": " << &t << "}" << std::endl;
    }
};

//=============================================================================
template <typename T>
struct Printer<T, true> {
  void execute(std::ostream& os, const T& t) const {
      os << t << std::endl;
    }
};

//=============================================================================
template <typename T>
void print(const T& t, std::ostream& os=std::cout)
{
  Printer<T>().execute(os, t);
}

#endif
