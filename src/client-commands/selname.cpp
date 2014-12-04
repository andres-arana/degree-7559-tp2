#include "client-commands/selname.h"

using namespace client;
using namespace client::commands;
using namespace std;

selname::selname(context &c)
  : command(c), db(c)  {

  }

void selname::handle(const string &args) {
  if (args.empty()) {
    c.writer.line("Invalid command selname. See usage with ? selname");
    return;
  }

  auto records = db.query_by_name(args);
  if (records.empty()) {
    c.writer.fline("No records with name $", args);
  } else {
    c.writer.line("Listing records: ");
    for (auto &p : records) {
      c.writer.fline("  $", p);
    }
  }
}

void selname::print_description() const {
  c.writer.line("Displays information about records with a given name");
  c.writer.line("USAGE: ");
  c.writer.line("> selname NAME");
}

string selname::summary() const {
  return "Displays information about records with a given name";
}
