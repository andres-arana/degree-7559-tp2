#ifndef __CLIENT__COMMANDS__UPSERT_H_INCLUDED__
#define __CLIENT__COMMANDS__UPSERT_H_INCLUDED__

#include "client-commands/command.h"
#include "client-commands/remote_db.h"

namespace client {
  namespace commands {
    class upsert : public command {
      public:
        upsert(context &c);

        virtual void handle(const std::string &args);

        virtual void print_description() const;

        virtual std::string summary() const;
      private:
        remote_db db;
    };
  }
}

#endif
