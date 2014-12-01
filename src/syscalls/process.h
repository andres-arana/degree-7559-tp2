#ifndef __SYSCALLS__PROCESSS_H_INCLUDED__
#define __SYSCALLS__PROCESSS_H_INCLUDED__

#include <string>
#include <vector>
#include <sys/types.h>
#include "syscalls/error.h"
#include "syscalls/interrupt.h"

namespace syscalls {
    pid_t getpid();
}

#endif

