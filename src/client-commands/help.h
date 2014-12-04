#ifndef __CLIENT__COMMANDS__HELP_H_INCLUDED__
#define __CLIENT__COMMANDS__HELP_H_INCLUDED__

#include "client-commands/command.h"
#include "client-commands/map.h"

namespace client {
  namespace commands {
    class help : public command {
      public:
        help(
            context &c,
            const map &cmds);

        virtual void handle(const std::string &args);

        virtual void print_description() const;

        virtual std::string summary() const;

      private:
        const map &commands;
    };
  }
}

#endif
