#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue_owner.h"
#include "raii/msgqueue.h"
#include "app-server/db.h"
#include "app-server/dispatcher.h"
#include "shared/data.h"

#include <iostream>

using namespace std;

class appserver : public util::app {
  public:
    explicit appserver() :
      app("SERVER") {}

  protected:
    virtual void do_run() override {
      log.info("Running server");

      log.debug("Loading database");
      server::db data;

      log.debug("Creating new message queue");
      raii::msgqueue_owner queue_registration;
      raii::msgqueue queue(queue_registration.id());
      log.debug("Queue created with id $", queue_registration.id());

      log.debug("Creating event dispatcher");
      server::context context {data, log, queue};
      server::dispatcher dispatcher(context);
      log.debug("Event dispatcher ready");

      cout << "Server up and running" << endl;
      cout << "  Waiting for messages from clients at queue " << queue_registration.id() << endl;
      cout << endl;
      cout << "Press Ctrl-C to stop the server" << endl;

      try {
        while (!is_halted()) {
          log.debug("Dispatching next event");
          dispatcher.dispatch_next();
        }
      } catch (syscalls::interrupt &e) {
        log.debug("Syscall interrupted");
      } catch (std::runtime_error &e) {
        log.error("Uncaught runtime error: $", e.what());
      }

      log.debug("Queue has been destroyed");
    }
};

DEFINE_MAIN(appserver);

