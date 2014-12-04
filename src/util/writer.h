#ifndef __UTIL__WRITER_H_INCLUDED__
#define __UTIL__WRITER_H_INCLUDED__

#include <iostream>
#include <string>

namespace util {
  class writer {
    public:
      writer(std::ostream &os);

      void line(const std::string &what);

      template<typename... Ts>
      void fline(const std::string &format, const Ts&... ts) {
        line(sformat(format, ts...));
      }

      void prompt(const std::string &banner, const std::string &prompt);

      void separator();

      void field(const std::string &f);

      std::ostream &raw();

    private:
      std::ostream &os;
  };
}

#endif
