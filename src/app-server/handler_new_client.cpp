#include "app-server/handler_new_client.h"

using namespace server;

handler_new_client::handler_new_client(context &c)
  : handler(c), current_client_id(0) {

  }

void handler_new_client::handle(shared::msgs::server &message) {
  c.log.debug("Handling server event subtype $: new_client", message.subtype);

  c.log.debug("Sending broadcast to set client id to $", current_client_id);
  c.queue.send(shared::msgs::broadcast::client_id(current_client_id));
  c.log.debug("Message sent");

  current_client_id++;

  c.log.debug("New client connection handled");
}
