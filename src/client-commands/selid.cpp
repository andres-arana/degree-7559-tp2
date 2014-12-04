#include "client-commands/selid.h"
#include <sstream>

using namespace client;
using namespace client::commands;
using namespace std;

selid::selid(context &c)
  : command(c), db(c)  {

  }

void selid::handle(const string &args) {
  if (args.empty()) {
    c.writer.line("Invalid command 'selid'. See usage with '? selid'");
    return;
  }

  stringstream arg_parser(args);
  int id = 0;
  arg_parser >> id;

  auto records = db.query_by_id(id);
  if (records.empty()) {
    c.writer.fline("No records with id $", id);
  } else {
    c.writer.fline("Record $ found", id);
    c.writer.fline("  $", records[0]);
  }
}

void selid::print_description() const {
  c.writer.line("Displays information a single record given its ids");
  c.writer.line("USAGE: ");
  c.writer.line("> selid ID");
}

string selid::summary() const {
  return "Displays information about a single record given its id";
}
