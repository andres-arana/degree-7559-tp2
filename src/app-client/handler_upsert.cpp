#include "app-client/handler_upsert.h"
#include <iostream>
#include <sstream>

using namespace client;
using namespace std;

namespace {
  string read_limited_string(const string &field, unsigned long length) {
    string result;

    do {
      cout << field << "(non null, less than " << length << " chars): ";
      getline(cin, result);
    } while (result.length() >= length || result.empty());

    return result;
  }
}

handler_upsert::handler_upsert(context &c)
  : handler(c), db(c)  {

  }

void handler_upsert::handle(const string &args) {
  if (!args.empty()) {
    cout << "Invalid command upsert. See usage with ? upsert" << endl;
  } else {
    cout << "Enter the id of the record you want to update, or 0 to insert a new record" << endl << "id: ";
    string id_as_string;
    unsigned int id;
    getline(cin, id_as_string);
    stringstream id_parser(id_as_string);
    id_parser >> id;

    cout << "Enter the record properties: " << endl;

    auto name = read_limited_string("name", shared::person::name_length);
    auto address = read_limited_string("address", shared::person::address_length);
    auto phone = read_limited_string("phone", shared::person::phone_length);

    shared::person p = shared::person::from_values(id, name, address, phone);
    cout << " Upserting person " << p << endl;
    cout << "Do you want to continue? (y/N)" << endl;

    string confirm;
    getline(cin, confirm);
    if (confirm == "y") {
      auto records = db.upsert(p);

      if (records.empty()) {
        cout << "Unable to insert record" << endl;
      } else {
        cout << "Upserted record with values " << records[0] << endl;
      }
    } else {
      cout << "Cancelled" << endl;
    }
  }
}

void handler_upsert::print_description(ostream &os) const {
  os << "Updates or inserts records" << endl;
  os << "USAGE: " << endl;
  os << "> upsert" << endl;
}

string handler_upsert::summary() const {
  return "Updates or inserts records";
}
