#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ProcessManager.h>
#include <ProcessClient.h>
#include <unistd.h>
#include <Process.h>
#include "Renice.h"
#include "Scheduler.h"

int priority;
ProcessID pid;

Renice::Renice(int argc, char **argv) : POSIXApplication(argc, argv){
    parser().setDescription("Modify the priority level of a process");
    parser().registerFlag('n', "setpriority", "Changes priorityrity level");
    parser().registerPositional("PRI", "priority to change the process to");
    parser().registerPositional("PID", "PID of the process to change");
    priority = atoi(argv[2]);
    pid = atoi(argv[3]);
}

Renice::~Renice(){

}

Renice::Result Renice::exec(){
    ProcessClient process;
    ProcessClient::Info info;

    // Case 1: Check if process exists at all
    if(process.processInfo(pid, info) != ProcessClient::Success) {
        ERROR("Invalid PID: " << pid << ". How tacky.");
        return InvalidArgument;
    }
    // Case 2: Check if priority is valid
    else if (priority <= 0 || priority > 5){
        ERROR("Invalid priority, sis: " << priority);
        return InvalidArgument;
    }
    else {
			process.setPriority(pid, priority);
            return Success;
    }
}