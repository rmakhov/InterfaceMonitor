#include <signal.h>
#include <errno.h>
#include <iostream>
 
#include "SignalHandler.hpp"
 
bool SignalHandler::mbGotExitSignal = false;
 
/**
* Default Contructor.
*/
SignalHandler::SignalHandler()
{
}
 
/**
* Destructor.
*/
SignalHandler::~SignalHandler()
{
}
 

//******************************************************************************
/**
 * Returns the bool flag indicating whether we received an exit signal
 *
 * @param None
 *
 * @return Flag indicating shutdown of program
 *
 */
//******************************************************************************
bool SignalHandler::gotExitSignal()
{
    return mbGotExitSignal;
}
 
//******************************************************************************
/**
 * Sets the bool flag indicating whether we received an exit signal
 *
 * @param None
 *
 * @return Flag indicating shutdown of program
 *
 */
//******************************************************************************
void SignalHandler::setExitSignal(bool _bExitSignal)
{
    mbGotExitSignal = _bExitSignal;
}

//******************************************************************************
/**
 * Sets exit signal to true
 *
 * @param[in] _ignored Not used but required by function prototype
 *                     to match required handler
 *
 * @return None
 *
 */
//******************************************************************************
void SignalHandler::exitSignalHandler(int _ignored)
{
    std::cout << "Received exit signal. Exiting." << std::endl;
    mbGotExitSignal = true;
}

//******************************************************************************
/**
 * Ignore all signals except SIGINT and SIGTERM
 *
 * @param[in] _ignored Not used but required by function prototype
 *                     to match required handler
 *
 * @return None
 *
 */
//******************************************************************************
void SignalHandler::ignoreSignalHandler(int _ignored)
{
    std::cout << "Ignore all signals except SIGINT and SIGTERM\n" << std::endl;
}

//******************************************************************************
/**
 * Set up the signal handlers
 *
 * @param None
 *
 * @return None
 *
 */
//******************************************************************************
void SignalHandler::setupSignalHandlers()
{
    signal((int) SIGHUP, SignalHandler::ignoreSignalHandler);
    signal((int) SIGINT, SignalHandler::exitSignalHandler);
    signal((int) SIGQUIT, SignalHandler::ignoreSignalHandler);
    signal((int) SIGABRT, SignalHandler::ignoreSignalHandler);
    signal((int) SIGFPE, SignalHandler::ignoreSignalHandler);
    signal((int) SIGKILL, SignalHandler::ignoreSignalHandler);
    signal((int) SIGSEGV, SignalHandler::ignoreSignalHandler);
    signal((int) SIGPIPE, SignalHandler::ignoreSignalHandler);
    signal((int) SIGALRM, SignalHandler::ignoreSignalHandler);
    signal((int) SIGTERM, SignalHandler::exitSignalHandler);
}
