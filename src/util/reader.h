#ifndef __UTIL__READER_H_INCLUDED__
#define __UTIL__READER_H_INCLUDED__

#include <iostream>
#include <string>
#include <sstream>

namespace util {
  class reader {
    public:
      reader(std::istream &is);

      std::string line();

      template<typename T>
      T typecasted_line() {
        T result;
        std::stringstream parser(line());
        parser >> result;
        return result;
      }

      std::istream &raw();

    private:
      std::istream &is;
  };
}

#endif
