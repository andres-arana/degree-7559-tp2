#ifndef __CLIENT__REPL_H_INCLUDED__
#define __CLIENT__REPL_H_INCLUDED__

#include "app-client/context.h"
#include "app-client/handler.h"
#include <map>
#include <string>
#include <memory>

namespace client {
  class repl {
    public:
      explicit repl(context &c);

      void read_eval_print();

    private:
      context &c;
      std::map<std::string, std::unique_ptr<handler>> handlers;

  };
}

#endif
