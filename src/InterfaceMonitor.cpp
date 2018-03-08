#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "InterfaceManager.hpp"
#include "SignalHandler.hpp"

using namespace std;

//******************************************************************************
/**
 * Main entry point to the InterfaceMonitor daemon
 *
 * @param argc   Argument count.
 * @param argv   Argument array.
 *
 * @return Exit code.
 */
//******************************************************************************
int main(int argc, const char *const argv[])
{
  int ret;
 
  try
  {
    // Register signal handler to handle exit signals
    SignalHandler signalHandler;
    signalHandler.setupSignalHandlers();
 
    // Start Interface Watchdog thread
    pthread_t threadWD;
    pthread_create( &threadWD, NULL, InterfaceManager::interfaceWatchdog, NULL);

    // Infinite loop until exit signals received
    while(!signalHandler.gotExitSignal()) {
      sleep(1);
      vector<string> vInterfaces = InterfaceManager::getListOfInterfaces();
      if (vInterfaces.empty()) {
        cout << "\nThere is no network interfaces in the system." << endl;
        continue;
      }
      cout << "\nCurrent network interfaces list:" << endl;
      for(int i=0;i<vInterfaces.size();++i) {
        cout << "IFACE " << vInterfaces.at(i) << " " <<
             InterfaceManager::getHwAddr(vInterfaces.at(i)) << endl;
      }
    }
    ret = EXIT_SUCCESS;
  }
  catch (SignalException& e)
  {
    cerr << "SignalException: " << e.what() << endl;
    ret = EXIT_FAILURE;
  }
  exit(ret);
}
