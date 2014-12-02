#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue.h"
#include "shared/data.h"
#include "app-client/remote_db.h"

using namespace std;

class appclient : public util::app {
  public:
    explicit appclient() :
      app("CLIENT"),
      queue_id("q", "queue", "Queue id", true, 0, "int", args) {

      }

  protected:
    virtual void do_run() override {
      log.info("Running client");

      log.debug("Connecting to queue $", queue_id.getValue());
      raii::msgqueue queue(queue_id.getValue());

      log.debug("Sending new client message");
      queue.send(shared::msgs::server::new_client());

      log.debug("Waiting for client id message");
      auto client_id_message = queue.receive<shared::msgs::broadcast>(
          shared::msgs::broadcast_type);

      log.debug("Received message with client id $", client_id_message.id);
      auto client = client_id_message.id;

      log.debug("Initializing remote db");
      client::context context { queue, log, client };
      client::remote_db db(context);

      cout << "Before inserting new person, showing all records" << endl;
      auto records = db.query_all();
      for (auto &p : records) {
        cout << "  " << p << endl;
      }

      cout << "Inserting new person" << endl;
      auto record = db.upsert(shared::person {0, "Andres", "Maipu 1855", "47955709"});
      cout << "  " << record << endl;

      cout << "After inserting new person, showing all records" << endl;
      records = db.query_all();
      for (auto &p : records) {
        cout << "  " << p << endl;
      }

      cout << "Querying by existing name" << endl;
      records = db.query_by_name("Andres");
      for (auto &p : records) {
        cout << "  " << p << endl;
      }

      cout << "Querying by unexisting name" << endl;
      records = db.query_by_name("Pepe");
      for (auto &p : records) {
        cout << "  " << p << endl;
      }
    }

  private:
    TCLAP::ValueArg<int> queue_id;
};

DEFINE_MAIN(appclient);

