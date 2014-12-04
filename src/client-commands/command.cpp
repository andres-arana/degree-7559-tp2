#include "client-commands/command.h"

using namespace client::commands;

command::command(context &c)
  : c(c) {

  }

command::~command() {

}
