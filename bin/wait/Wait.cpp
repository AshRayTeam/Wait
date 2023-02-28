#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait execution for some time");
    parser().registerPositional("PROCESS", "Wait execution for the given number of seconds");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    ProcessID pid;

    if ((pid = atoi(arguments().get("PROCESS"))) < 0) {
	    ERROR("wait: `" << arguments().get("PROCESS") << "is an invalid argument");
        return InvalidArgument;
    }


    if (waitpid(pid, 0, 0) == (pid_t) -1) {
    	ERROR("wait " << arguments().get("PROCESS") << " is an invalid input, miss girl.");
        return IOError;
    }

    // Done
    return Success;
}