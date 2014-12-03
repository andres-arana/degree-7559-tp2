#include "app-client/handler_selall.h"
#include <iostream>

using namespace client;
using namespace std;

handler_selall::handler_selall(context &c)
  : handler(c), db(c)  {
    
  }

void handler_selall::handle(const string &args) {
  if (!args.empty()) {
    cout << "Invalid command selall " << args << ". See usage with ? selall" << endl;
  } else {
    auto records = db.query_all();
    if (records.empty()) {
      cout << "No records have been inserted" << endl;
    } else {
      cout << "Listing all records: " << endl;
      for (auto &person : records) {
        cout << "  " << person << endl;
      }
    }
  }
}

void handler_selall::print_description(ostream &os) const {
  os << "Displays information about all available records" << endl;
  os << "USAGE: " << endl;
  os << "> selall" << endl;
}

string handler_selall::summary() const {
  return "Displays information about all available records";
}
