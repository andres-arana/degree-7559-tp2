#include "util/reader.h"

using namespace util;
using namespace std;

reader::reader(istream &is)
  : is(is) {

  }

string reader::line() {
  string result;
  getline(is, result);
  return result;
}

istream &reader::raw() {
  return is;
}
