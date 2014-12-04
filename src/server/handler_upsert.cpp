#include "server/handler_upsert.h"

using namespace server;

handler_upsert::handler_upsert(context &c)
  : handler(c) {

  }

void handler_upsert::handle(shared::msgs::server &message) {
  c.log.debug("Handling server event subtype $: upsert", message.subtype);

  c.log.debug("Upserting with person $", message.data.record);
  auto record = c.data.upsert(message.data.record);

  c.log.debug("Upsert complete, sending record to client");
  c.queue.send<shared::msgs::client>(
      shared::msgs::client::record(message.client_id, record));

  c.log.debug("Sending end of records to client");
  c.queue.send<shared::msgs::client>(
      shared::msgs::client::end_of_records(message.client_id));
}
