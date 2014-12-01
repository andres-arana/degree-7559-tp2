#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue_owner.h"
#include "app-server/db.h"
#include "app-server/queries.h"

#include <iostream>

using namespace std;

class server : public util::app {
  public:
    explicit server() :
      app("SERVER") {}

  protected:
    virtual void do_run() override {
      log.info("Running server");

      {
        log.debug("Creating new message queue");
        raii::msgqueue_owner queue;

        log.debug("Queue created with id $", queue.id());

        cout << "Server up and running" << endl;
        cout << "  Waiting for messages from clients at queue " << queue.id() << endl;
        cout << endl;

        cout << "Press enter to stop the server" << endl;
        cin.ignore();

        log.debug("Destroying the message queue");
      }

      log.debug("Queue has been destroyed");
    }
};

DEFINE_MAIN(server);

