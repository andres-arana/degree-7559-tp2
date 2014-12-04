#ifndef __CLIENT__COMMANDS__MAP_H_INCLUDED__
#define __CLIENT__COMMANDS__MAP_H_INCLUDED__

#include "client-commands/command.h"
#include <map>
#include <string>
#include <memory>

namespace client {
  namespace commands {
    class map {
      public:
        typedef std::map<std::string, std::unique_ptr<command>> map_type;

        void assoc(const std::string &name, command *command);

        map_type::iterator find(const std::string &key);

        map_type::const_iterator find(const std::string &key) const;

        map_type::iterator begin();

        map_type::const_iterator begin() const;

        map_type::iterator end();

        map_type::const_iterator end() const;

      private:
       map_type commands;
    };
  }
}

#endif
