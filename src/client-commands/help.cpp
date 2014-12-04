#include "client-commands/help.h"

using namespace std;
using namespace client;
using namespace client::commands;

help::help(context &c, const map &cmds)
  : command(c), commands(cmds){

  }

void help::handle(const string &args) {
  if (args.empty()) {
    print_description();
  } else {
    auto it = commands.find(args);

    if (it == commands.end()) {
      c.writer.fline("Unknown command '$'", args);
    } else {
      it->second->print_description();
    }
  }
}

void help::print_description() const {
  c.writer.line("The following are the available commands. Enter ? COMMAND for additional help");

  for (auto &it : commands) {
    c.writer.fline("  $: $", it.first, it.second->summary());
  }
}

string help::summary() const {
  return "Displays help messages";
}
