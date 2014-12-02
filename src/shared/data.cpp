#include "shared/data.h"
#include <cstring>

using namespace std;
using namespace shared;

void person::serialize_to(std::ostream &os) const {
  os.write(reinterpret_cast<const char *>(this), sizeof(person));
}

pair<bool, person> person::deserialize_from(std::istream &is) {
  person result;
  is.read(reinterpret_cast<char *>(&result), sizeof(person));

  return make_pair(!is.eof(), result);
}

std::ostream& shared::operator<<(std::ostream& os, const person &p) {
  return os << "Person(" <<
    p.id << ", " <<
    "'" << p.name << "', " <<
    "'" << p.address << "', " <<
    "'" << p.phone << "')";
}

constexpr long msgs::server::new_client_subtype;
constexpr long msgs::client::record_subtype;
constexpr long msgs::client::end_of_records_subtype;

msgs::server msgs::server::new_client() {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::new_client_subtype;
  return result;
}

constexpr long msgs::server::query_all_subtype;

msgs::server msgs::server::query_all(const long client_id) {
  return msgs::server {
    msgs::server_type,
    msgs::server::query_all_subtype,
    client_id
  };
}

msgs::broadcast msgs::broadcast::client_id(long id) {
  msgs::broadcast result;
  result.type = msgs::broadcast_type;
  result.id = id;
  return result;
}

msgs::client msgs::client::record(long client_id, person &p) {
  msgs::client result;
  result.type = msgs::client_type_offset + client_id;
  result.subtype = msgs::client::record_subtype;
  result.data.record = p;
  return result;
}

msgs::client msgs::client::end_of_records(long client_id) {
  msgs::client result;
  result.type = msgs::client_type_offset + client_id;
  result.subtype = msgs::client::end_of_records_subtype;
  return result;
}
