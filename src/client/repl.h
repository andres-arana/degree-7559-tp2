#ifndef __CLIENT__REPL_H_INCLUDED__
#define __CLIENT__REPL_H_INCLUDED__

#include "client/context.h"
#include "client-commands/command.h"
#include "client-commands/map.h"


namespace client {
  class repl {
    public:
      explicit repl(context &c);

      void read_eval_print();

    private:
      context &c;
      commands::map commands;
  };
}

#endif
