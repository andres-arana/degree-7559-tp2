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
  return msgs::server {
    msgs::server_type,
    msgs::server::new_client_subtype
  };
}

msgs::broadcast msgs::broadcast::client_id(long id) {
  return msgs::broadcast {
    msgs::broadcast_type,
    id
  };
}
