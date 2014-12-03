#include "shared/data.h"
#include <cstring>
#include <algorithm>

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

person person::from_values(unsigned int id, const string &name, const string &address, const string &phone) {
  person result;
  result.id = id;
  strncpy(result.name, name.c_str(), person::name_length);
  strncpy(result.address, address.c_str(), person::address_length);
  strncpy(result.phone, phone.c_str(), phone_length);

  return result;
}

std::ostream& shared::operator<<(std::ostream& os, const person &p) {
  return os << "Person(" <<
    p.id << ", " <<
    "'" << p.name << "', " <<
    "'" << p.address << "', " <<
    "'" << p.phone << "')";
}

constexpr long msgs::server::new_client_subtype;
constexpr long msgs::server::query_all_subtype;
constexpr long msgs::server::query_by_id_subtype;
constexpr long msgs::server::query_by_name_subtype;
constexpr long msgs::server::upsert_subtype;
constexpr long msgs::client::record_subtype;
constexpr long msgs::client::end_of_records_subtype;

msgs::server msgs::server::new_client() {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::new_client_subtype;
  return result;
}

msgs::server msgs::server::query_all(const long client_id) {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::query_all_subtype;
  result.client_id = client_id;
  return result;
}

msgs::server msgs::server::query_by_id(const long client_id, const unsigned int person_id) {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::query_by_id_subtype;
  result.client_id = client_id;
  result.data.id_query = person_id;
  return result;
}

msgs::server msgs::server::query_by_name(const long client_id, const std::string &name) {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::query_by_name_subtype;
  result.client_id = client_id;
  std::strncpy(
      result.data.name_query,
      name.c_str(),
      name.length() < person::name_length ? name.length() : person::name_length);
  return result;
}

msgs::server msgs::server::upsert(long client_id, const person &p) {
  msgs::server result;
  result.type = msgs::server_type;
  result.subtype = msgs::server::upsert_subtype;
  result.client_id = client_id;
  result.data.record = p;
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
