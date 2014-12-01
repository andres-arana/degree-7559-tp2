#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue_owner.h"
#include "raii/msgqueue.h"
#include "app-server/db.h"
#include "app-server/queries.h"

#include <iostream>

// This is a test structure for the message queueing system
struct message {
  long type;
  int value;
};

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

        // This is a test for the message queueing system
        cout << "Writing a message to the message queue" << endl;
        raii::msgqueue q(queue.id());
        q.send(message { 1, 10 });
        cout << "Message written with value 10, attempting to read message" << endl;
        auto m = q.receive<message>(1);
        cout << "Message received with value " << m.value << endl;

        cout << "Press enter to stop the server" << endl;
        cin.ignore();

        log.debug("Destroying the message queue");
      }

      log.debug("Queue has been destroyed");
    }
};

DEFINE_MAIN(server);

