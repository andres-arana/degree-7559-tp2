#include "app-client/handler_selid.h"
#include <iostream>
#include <sstream>

using namespace client;
using namespace std;

handler_selid::handler_selid(context &c)
  : handler(c), db(c)  {

  }

void handler_selid::handle(const string &args) {
  if (args.empty()) {
    cout << "Invalid command selid. See usage with ? selid" << endl;
  } else {
    stringstream arg_parser(args);
    int id = 0;
    arg_parser >> id;

    auto records = db.query_by_id(id);
    if (records.empty()) {
      cout << "No records with id " << id << " have been inserted" << endl;
    } else {
      cout << "Record " << id << " found." << endl;
      cout << "  " << records[0] << endl;
    }
  }
}

void handler_selid::print_description(ostream &os) const {
  os << "Displays information a single record given its ids" << endl;
  os << "USAGE: " << endl;
  os << "> selid ID" << endl;
  os << "EXAMPLES: " << endl;
  os << "> selid 5" << endl;
}

string handler_selid::summary() const {
  return "Displays information about a single record given its id";
}
