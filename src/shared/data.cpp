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
