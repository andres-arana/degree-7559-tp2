#include "util/app.h"
#include "raii/signal.h"

#include <iostream>

using namespace std;

class client : public util::app {
  public:
    explicit client() :
      app("CLIENT") {}

  protected:
    virtual void do_run() override {
      cout << "Running" << endl;
    }
};

DEFINE_MAIN(client);

