#ifndef __UTIL__APP_H_INCLUDED__
#define __UTIL__APP_H_INCLUDED__

#include "util/sync_log.h"
#include "raii/signal.h"
#include "tclap/CmdLine.h"
#include <string>

#define DEFINE_MAIN(class)\
  int main(int argc, char** argv) {\
    class app;\
    return app.run(argc, argv);\
  }

namespace util {
  class app {
    public:
      explicit app(const std::string &name);

      int run(int argc, char **argv);

      virtual ~app() {};

    protected:

      bool is_halted() const;

      sync_log log;

      TCLAP::CmdLine args;

      virtual void do_run() = 0;

    private:
      sig_atomic_t halt;
      raii::signal sigint;
      TCLAP::ValueArg<int> log_level;
  };
}

#endif
