#include "server/handler_query_all.h"

using namespace server;

handler_query_all::handler_query_all(context &c)
  : handler(c) {

  }

void handler_query_all::handle(shared::msgs::server &message) {
  c.log.debug("Handling server event subtype $: query_all", message.subtype);
  auto result = c.data.all();

  for (shared::person &p : result) {
    c.log.debug("Sending client $ message record with $", message.client_id, p);
    c.queue.send(shared::msgs::client::record(message.client_id, p));
    c.log.debug("Message sent");
  }

  c.log.debug("Sending client $ message end of records", message.client_id);
  c.queue.send(shared::msgs::client::end_of_records(message.client_id));
  c.log.debug("Message sent");

  c.log.debug("Query all connection handled");
}
