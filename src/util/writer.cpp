#include "util/writer.h"

using namespace std;
using namespace util;

writer::writer(ostream &os)
  : os(os) {

  }

void writer::line(const string &what) {
  os << what << endl;
}

void writer::prompt(const string &banner, const string &prompt) {
  os << endl;
  os << banner << endl;
  os << prompt;
}

void writer::separator() {
  os << endl;
}

void writer::field(const string &f) {
  os << f << ": ";
}

ostream &writer::raw() {
  return os;
}
