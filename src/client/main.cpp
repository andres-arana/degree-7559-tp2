#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue.h"
#include "shared/data.h"
#include "client/repl.h"

using namespace std;

class clientapp : public util::app {
  public:
    explicit clientapp() :
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
      util::reader reader(cin);
      util::writer writer(cout);
      client::context context { queue, log, client, reader, writer };

      log.debug("Starting REPL loop");
      client::repl repl(context);

      try {
        while (!is_halted() && !cin.eof()) {
          repl.read_eval_print();
        }
      } catch (syscalls::interrupt &e) {
        log.debug("Syscall interrupted");
      } catch (syscalls::removed_queue &e) {
        log.info("Message queue closed, the server was closed");
        cout << "The server was closed, terminating" << endl;
      } catch (std::runtime_error &e) {
        log.error("Uncaught runtime error: $", e.what());
      }

      cout << "Bye!" << endl;
    }

  private:
    TCLAP::ValueArg<int> queue_id;
};

DEFINE_MAIN(clientapp);

