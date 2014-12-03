#include "app-client/handler_help.h"
#include <iostream>
#include <map>

using namespace client;
using namespace std;

handler_help::handler_help(context &c, const std::map<std::string, std::unique_ptr<handler>> &handlers)
  :handler(c), handlers(handlers){

  }

void handler_help::handle(const string &args) {
  if (args.empty()) {
    print_description(cout);
  } else {
    auto it = handlers.find(args);

    if (it == handlers.end()) {
      cout << "Unknown command " << args << endl;
    } else {
      it->second->print_description(cout);
    }
  }
}

void handler_help::print_description(ostream &os) const {
  os << "These are the available commands. ";
  os << "Enter ? COMMAND for additional help on each command" << endl;

  for (auto &it : handlers) {
    os << "  " << it.first << ": " << it.second->summary() << endl;
  }
}

string handler_help::summary() const {
  return "Displays help messages";
}
