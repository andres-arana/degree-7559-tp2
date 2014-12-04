#include "client-commands/selall.h"

using namespace client;
using namespace client::commands;
using namespace std;

selall::selall(context &c)
  : command(c), db(c)  {

  }

void selall::handle(const string &args) {
  if (!args.empty()) {
    c.writer.fline("Invalid command 'selall $'. See usage with '? selall'", args);
    return;
  }

  auto records = db.query_all();
  if (records.empty()) {
    c.writer.line("No records are available");
  } else {
    c.writer.line("Listing all records:");
    for (auto &person : records) {
      c.writer.fline("  $", person);
    }
  }
}

void selall::print_description() const {
  c.writer.line("Displays information about all available records");
  c.writer.line("USAGE:");
  c.writer.line("> selall");
}

string selall::summary() const {
  return "Displays information about all available records";
}
