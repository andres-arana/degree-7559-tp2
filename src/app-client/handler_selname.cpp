#include "app-client/handler_selname.h"
#include <iostream>
#include <sstream>

using namespace client;
using namespace std;

handler_selname::handler_selname(context &c)
  : handler(c), db(c)  {

  }

void handler_selname::handle(const string &args) {
  if (args.empty()) {
    cout << "Invalid command selname. See usage with ? selname" << endl;
  } else {
    auto records = db.query_by_name(args);
    if (records.empty()) {
      cout << "No records with name " << args << " have been inserted" << endl;
    } else {
      cout << "Listing records: " << endl;
      for (auto &p : records) {
        cout << "  " << p << endl;
      }
    }
  }
}

void handler_selname::print_description(ostream &os) const {
  os << "Displays information about records with a given name" << endl;
  os << "USAGE: " << endl;
  os << "> selname NAME" << endl;
  os << "EXAMPLES: " << endl;
  os << "> selname Andres" << endl;
}

string handler_selname::summary() const {
  return "Displays information about records with a given name";
}
