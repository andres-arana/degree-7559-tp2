#include "util/app.h"
#include "raii/signal.h"

#include <iostream>

using namespace std;

class server : public util::app {
  public:
    explicit server() :
      app("SERVER") {}

  protected:
    virtual void do_run() override {
      cout << "Running" << endl;
    }
};

DEFINE_MAIN(server);

