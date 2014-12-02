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

constexpr long msgs::server::new_client_subtype;

msgs::server msgs::server::new_client() {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::new_client_subtype;
  return result;
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
