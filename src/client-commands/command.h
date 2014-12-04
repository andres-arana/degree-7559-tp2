#ifndef __CLIENT__COMMANDS__COMMAND_H_INCLUDED
#define __CLIENT__COMMANDS__COMMAND_H_INCLUDED

#include "client/context.h"
#include <string>

namespace client {
  namespace commands {
    class command {
      public:
        command(context &c);

        virtual void handle(const std::string &args) = 0;

        virtual void print_description() const = 0;

        virtual std::string summary() const = 0;

        virtual ~command();

      protected:
        context &c;
    };
  }
}

#endif
