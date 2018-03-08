#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include <vector>

using namespace std;

class InterfaceManager
{
protected:
    static bool mbGotExitSignal;
 
public:
    InterfaceManager();
    ~InterfaceManager();

    static vector<string> getListOfInterfaces(); 
    static string getHwAddr(string interface);
    static void *interfaceWatchdog(void *args);
};

#endif //INTERFACEMANAGER_H

