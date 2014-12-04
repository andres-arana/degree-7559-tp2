#include "util/reader.h"
#include "util/writer.h"
#include "util/string.h"
#include "client/repl.h"
#include "client-commands/help.h"
#include "client-commands/selall.h"
#include "client-commands/selid.h"
#include "client-commands/selname.h"
#include "client-commands/upsert.h"

using namespace client;
using namespace std;

repl::repl(context &c)
  : c(c) {

    commands.assoc(
        "?", new commands::help(c, commands));
    commands.assoc(
        "selall", new commands::selall(c));
    commands.assoc(
        "selid", new commands::selid(c));
    commands.assoc(
        "selname", new commands::selname(c));
    commands.assoc(
        "upsert", new commands::upsert(c));
  }

void repl::read_eval_print() {

  c.writer.prompt("Enter a command, ? for help or Ctrl-C to exit.", "> ");
  auto command = c.reader.line();
  auto parsed_command = util::ssplit_at(command, ' ');

  if (parsed_command.first.empty()) return;

  c.writer.separator();

  auto it = commands.find(parsed_command.first);
  if (it == commands.end()) {
    c.writer.line("Unknown command");
  } else {
    it->second->handle(parsed_command.second);
  }
}
