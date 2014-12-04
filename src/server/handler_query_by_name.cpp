#include "server/handler_query_by_name.h"
#include "server/queries.h"
#include <string>

using namespace server;

handler_query_by_name::handler_query_by_name(context &c)
  : handler(c) {

  }

void handler_query_by_name::handle(shared::msgs::server &message) {
  c.log.debug("Handling server event subtype $: query_by_name", message.subtype);
  auto result = c.data.lookup(queries::by_name { std::string(message.data.name_query) });

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
