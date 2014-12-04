#include "client-commands/upsert.h"

using namespace client;
using namespace client::commands;
using namespace std;

namespace {
  string read_limited_string(context &c, const string &field, unsigned long length) {
    string result;

    do {
      c.writer.field(util::sformat("$ (non null, less than $ chars)", field, length));
      result = c.reader.line();
    } while (result.length() >= length || result.empty());

    return result;
  }
}

upsert::upsert(context &c)
  : command(c), db(c)  {

  }

void upsert::handle(const string &args) {
  if (!args.empty()) {
    c.writer.fline("Invalid command 'upsert $'. See usage with ? upsert", args);
    return;
  }
  c.writer.line("Enter the id of the record you want to update, or 0 to insert a new record");
  c.writer.field("id");
  auto id = c.reader.typecasted_line<unsigned int>();

  c.writer.line("Enter the record properties:");

  auto name = read_limited_string(c, "Name", shared::person::name_length);
  auto address = read_limited_string(c, "Address", shared::person::address_length);
  auto phone = read_limited_string(c, "Phone", shared::person::phone_length);

  shared::person p = shared::person::from_values(id, name, address, phone);
  c.writer.fline("Upserting $", p);
  c.writer.line("Do you want to continue? (y/N)");

  auto confirm = c.reader.line();
  if (confirm == "y") {
    auto records = db.upsert(p);

    if (records.empty()) {
      c.writer.line("Unable to insert record");
    } else {
      c.writer.fline("Upserted record $", records[0]);
    }
  } else {
    c.writer.line("Cancelled");
  }
}

void upsert::print_description() const {
  c.writer.line("Updates or inserts records interactively");
  c.writer.line("USAGE: ");
  c.writer.line("> upsert");
}

string upsert::summary() const {
  return "Updates or inserts records";
}
