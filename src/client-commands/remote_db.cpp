#include "client-commands/remote_db.h"

using namespace client;
using namespace client::commands;

namespace {
  shared::people accumulate_records(context &c) {
    shared::people result;

    while (true) {
      c.log.debug("Waiting for data from the server");
      auto message = c.queue.receive<shared::msgs::client>(
          shared::msgs::client_type_offset + c.client_id);
      c.log.debug("Received message from server subtype $", message.subtype);

      if (message.subtype == shared::msgs::client::record_subtype) {
        c.log.debug("Message is a record, accumulating $ and waiting for more data", message.data.record);
        result.push_back(message.data.record);
      } else {
        c.log.debug("Message is an end of records");
        break;
      }
    }

    c.log.debug("Returning accumulated records from the remote db");
    return result;
  }
}

remote_db::remote_db(context &c)
  : c(c) {

  }

shared::people remote_db::upsert(const shared::person &p) {
  c.log.debug("Upserting record $", p);

  c.log.debug("Sending upsert message to server");
  c.queue.send(shared::msgs::server::upsert(c.client_id, p));

  c.log.debug("Upsert message sent, waiting for record");
  auto results = ::accumulate_records(c);

  c.log.debug("Received $ records", results.size());
  return results;
}

shared::people remote_db::query_all() {
  c.log.debug("Querying all records through remote db");

  c.log.debug("Sending query all server message");
  c.queue.send(shared::msgs::server::query_all(c.client_id));
  c.log.debug("Message sent");

  return ::accumulate_records(c);
}

shared::people remote_db::query_by_id(const unsigned int person_id) {
  c.log.debug("Querying by id records through remote db");

  c.log.debug("Sending query by id server message");
  c.queue.send(shared::msgs::server::query_by_id(c.client_id, person_id));
  c.log.debug("Message sent");

  auto results = ::accumulate_records(c);

  c.log.debug("Received $ records", results.size());
  return results;
}

shared::people remote_db::query_by_name(const std::string &name) {
  c.log.debug("Querying records by name $ through remote db", name);

  c.log.debug("Sending query by name server message");
  c.queue.send(shared::msgs::server::query_by_name(c.client_id, name));
  c.log.debug("Message sent");

  return ::accumulate_records(c);
}
