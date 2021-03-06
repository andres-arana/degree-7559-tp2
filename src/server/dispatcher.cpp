#include "server/dispatcher.h"
#include "server/handler_new_client.h"
#include "server/handler_query_all.h"
#include "server/handler_query_by_name.h"
#include "server/handler_upsert.h"
#include "server/handler_query_by_id.h"
#include "shared/data.h"

using namespace server;
using namespace shared;

dispatcher::dispatcher(context &c)
  : c(c) {

    handlers.insert(std::make_pair(
          msgs::server::new_client_subtype,
          std::unique_ptr<handler>(new handler_new_client(c))));

    handlers.insert(std::make_pair(
          msgs::server::query_all_subtype,
          std::unique_ptr<handler>(new handler_query_all(c))));

    handlers.insert(std::make_pair(
          msgs::server::query_by_name_subtype,
          std::unique_ptr<handler>(new handler_query_by_name(c))));

    handlers.insert(std::make_pair(
          msgs::server::upsert_subtype,
          std::unique_ptr<handler>(new handler_upsert(c))));

    handlers.insert(std::make_pair(
          msgs::server::query_by_id_subtype,
          std::unique_ptr<handler>(new handler_query_by_id(c))));
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

