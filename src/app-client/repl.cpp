#include "app-client/repl.h"
#include "app-client/handler_help.h"
#include "app-client/handler_selall.h"
#include "app-client/handler_selid.h"
#include "app-client/handler_selname.h"
#include "app-client/handler_upsert.h"
#include <iostream>
#include <string>
#include <utility>

using namespace client;
using namespace std;

namespace {
  pair<string, string> split_at(const string &s, char c) {
    auto first_occurrence = s.find(c);

    if (first_occurrence == string::npos) {
      return make_pair(s, "");
    } else {
      return make_pair(
          s.substr(0, first_occurrence),
          s.substr(first_occurrence + 1));
    }
  }
}

repl::repl(context &c)
  : c(c) {

    handlers.insert(std::make_pair(
          "?",
          std::unique_ptr<handler>(new handler_help(c, handlers))));

    handlers.insert(std::make_pair(
          "selall",
          std::unique_ptr<handler>(new handler_selall(c))));

    handlers.insert(std::make_pair(
          "selid",
          std::unique_ptr<handler>(new handler_selid(c))));

    handlers.insert(std::make_pair(
          "selname",
          std::unique_ptr<handler>(new handler_selname(c))));

    handlers.insert(std::make_pair(
          "upsert",
          std::unique_ptr<handler>(new handler_upsert(c))));
  }

void repl::read_eval_print() {
  cout << endl;
  cout << "Enter a command, ? for help or Ctrl-C to exit." << endl;
  cout << "> ";
  string command;
  getline(cin, command);
  if (command.empty()) return;
  cout << endl;

  auto parsed_command = split_at(command, ' ');

  auto it = handlers.find(parsed_command.first);
  if (it == handlers.end()) {
    cout << "Unknown command. Enter ? for help" << endl;
  } else {
    it->second->handle(parsed_command.second);
  }
}
