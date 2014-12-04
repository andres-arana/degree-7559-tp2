#include "server/handler_query_by_id.h"
#include "server/queries.h"

using namespace server;

handler_query_by_id::handler_query_by_id(context &c)
  : handler(c) {

  }

void handler_query_by_id::handle(shared::msgs::server &message) {
  c.log.debug("Handling server event subtype $: query_by_id", message.subtype);
  auto person_id_query = message.data.id_query;
  c.log.debug("Looking person by id $", person_id_query);
  auto result = c.data.lookup(queries::by_id{ person_id_query });

  for (shared::person &p : result) {
    c.log.debug("Sending client $ message record with $", message.client_id, p);
    c.queue.send(shared::msgs::client::record(message.client_id, p));
    c.log.debug("Message sent");
  }

  c.log.debug("Sending client $ message end of records", message.client_id);
  c.queue.send(shared::msgs::client::end_of_records(message.client_id));
  c.log.debug("Message sent");

  c.log.debug("Query by id connection handled");
}
