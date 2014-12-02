#include "util/app.h"
#include "raii/signal.h"
#include "raii/msgqueue.h"
#include "shared/data.h"

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

      log.debug("Sending query_all message");
      queue.send(shared::msgs::server::query_all(client));

      log.debug("Waiting for query_all message");
      while( true ) {

        log.debug("Waiting message from server");

        auto message = queue.receive<shared::msgs::client>(
          shared::msgs::client_type_offset + client);

        if (message.subtype == shared::msgs::client::record_subtype) {
          log.debug("Message arrives $", message.data.record);
        } else {
          log.debug("End of messages");
          break;
        }

      }
    }

  private:
    TCLAP::ValueArg<int> queue_id;
};

DEFINE_MAIN(appclient);

