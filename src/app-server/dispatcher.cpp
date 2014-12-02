#include "app-server/dispatcher.h"
#include "app-server/handler_new_client.h"
#include "shared/data.h"

using namespace server;
using namespace shared;

dispatcher::dispatcher(context &c)
  : c(c) {

    handlers.insert(std::make_pair(
          msgs::server::new_client_subtype,
          std::unique_ptr<handler>(new handler_new_client(c))));
  }

void dispatcher::dispatch_next() {
  c.log.debug("Waiting for server message");
  auto message = c.queue.receive<msgs::server>(msgs::server_type);
  c.log.debug("Received server message subtype $", message.subtype);

  auto it = handlers.find(message.subtype);

  if (it == handlers.end()) {
      c.log.warn("Unknown message subtype $", message.subtype);
  } else {
    it->second->handle(message);
  }
}
