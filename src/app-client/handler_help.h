#ifndef __CLIENT__HANDLER_HELP_H_INCLUDED__
#define __CLIENT__HANDLER_HELP_H_INCLUDED__

#include "app-client/handler.h"
#include <map>
#include <memory>

namespace client {
  class handler_help : public handler {
    public:
      handler_help(
          context &c,
          const std::map<std::string, std::unique_ptr<handler>> &handlers);

      virtual void handle(const std::string &args);

      virtual void print_description(std::ostream &os) const;

      virtual std::string summary() const;

    private:
      const std::map<std::string, std::unique_ptr<handler>> &handlers;
  };
}

#endif
