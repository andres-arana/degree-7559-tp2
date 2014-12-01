#include "util/app.h"
#include "raii/signal.h"
#include "app-server/db.h"
#include "app-server/queries.h"

#include <iostream>

using namespace std;

void print_people(const shared::people &p) {
  if (p.empty()) { cout << "  NO DATA" << endl; }
  for (shared::people::const_iterator it = p.begin(); it != p.end(); it++) {
    cout << "  Person (" <<
      "id: " << it->id <<
      "; name: '" << it->name << "'" <<
      "; address: '" << it->address << "'" <<
      "; phone: '" << it->phone << "'" <<
      ")" << endl;
  }
}

class server : public util::app {
  public:
    explicit server() :
      app("SERVER") {}

  protected:
    virtual void do_run() override {
      log.info("Running server");

      db data;

      cout << "Database stats" << endl;
      auto first_stats = data.stats();
      cout << "  Records: " << first_stats.record_count << endl;
      cout << endl;

      cout << "Data is empty: " << endl;
      print_people(data.all());
      cout << endl;

      cout << "After inserting a couple of records" << endl;
      data.upsert(shared::person { 0, "Andres", "Av. Maipu 1855", "47955709" });
      data.upsert(shared::person { 0, "Gaston", "Montevideo 914", "47407988" });
      data.upsert(shared::person { 0, "Arana", "Montevideo 155", "47405936" });
      print_people(data.all());
      cout << endl;

      cout << "After updating the first record" << endl;
      data.upsert(shared::person { 1, "Arana", "Av. Maipú 1855 7D", "541147955709" });
      print_people(data.all());
      cout << endl;

      cout << "Querying by id 1" << endl;
      print_people(data.lookup(queries::by_id { 1 }));
      cout << endl;

      cout << "Querying by wrong id" << endl;
      print_people(data.lookup(queries::by_id { 100 }));
      cout << endl;

      cout << "Querying by name 'Arana'" << endl;
      print_people(data.lookup(queries::by_name { "Arana" }));
      cout << endl;

      cout << "Querying by wrong name" << endl;
      print_people(data.lookup(queries::by_name { "Pepe" }));
      cout << endl;

      cout << "Querying by telephone '47407988'" << endl;
      print_people(data.lookup(queries::by_phone {"47407988"}));
      cout << endl;

      cout << "Querying by wrong telephone" << endl;
      print_people(data.lookup(queries::by_phone {"11111111"}));
      cout << endl;

      cout << "Database stats" << endl;
      auto second_stats = data.stats();
      cout << "  Records: " << second_stats.record_count << endl;
      cout << endl;
    }
};

DEFINE_MAIN(server);

