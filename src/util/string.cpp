#include "util/string.h"

using namespace std;

string util::sformat(const string &format) {
  return format;
}

vector<string> util::svector(vector<string> out) {
  return out;
}

pair<string, string> util::ssplit_at(const string &s, char c) {
  auto first_occurrence = s.find(c);

  if (first_occurrence == string::npos) {
    return make_pair(s, "");
  } else {
    return make_pair(
        s.substr(0, first_occurrence),
        s.substr(first_occurrence + 1));
  }
}
