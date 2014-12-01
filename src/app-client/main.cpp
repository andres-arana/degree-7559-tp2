#include "util/app.h"
#include "raii/signal.h"

using namespace std;

class client : public util::app {
  public:
    explicit client() :
      app("CLIENT") {}

  protected:
    virtual void do_run() override {
      log.info("Running client");
    }
};

DEFINE_MAIN(client);

