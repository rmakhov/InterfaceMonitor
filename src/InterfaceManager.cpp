#include <iostream>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <boost/format.hpp>
#include "InterfaceManager.hpp"

/**
* Default Contructor.
*/
InterfaceManager::InterfaceManager()
{
}
 
/**
* Destructor.
*/
InterfaceManager::~InterfaceManager()
{
}

//******************************************************************************
/**
 * Get current list of the system interfaces. .
 *
 * @param None
 *
 * @return list of the interfaces.
 *
 */
//******************************************************************************
vector<string> InterfaceManager::getListOfInterfaces()
{
  vector<string> vInterfaces;
  struct ifreq ifr;
  struct ifconf ifc;
  char buf[1024];

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock == -1) {
    cerr << "ERROR: Unable to create socket" << endl;
    return vInterfaces;
  }

  ifc.ifc_len = sizeof(buf);
  ifc.ifc_buf = buf;
  if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
    cerr << "ERROR: failed SIOCGIFCONF request" << endl;
    return vInterfaces;
  }

  struct ifreq* it = ifc.ifc_req;
  const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
  for (; it != end; ++it) {
    strcpy(ifr.ifr_name, it->ifr_name);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
      if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // skip loopback
        vInterfaces.push_back(ifr.ifr_name);
      }
    }
    else {
        cerr << "ERROR: failed SIOCGIFFLAGS request" << endl;
    }
  }
  return vInterfaces;
}

//******************************************************************************
/**
 * Get MAC address of the interfaces. .
 *
 *
 * @param target interface.
 *
 * @return MAC address.
 *
 */
//******************************************************************************
string InterfaceManager::getHwAddr(string interface)
{
  string vMacAddress;
  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock == -1) {
    cerr << "ERROR: Unable to create socket" << endl;
    return vMacAddress;
  }

  struct ifreq ifr;
  strcpy(ifr.ifr_name, interface.c_str());
  if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
    if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // skip loopback
      if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
        unsigned char ucMacAddress[6];
        memcpy(ucMacAddress, ifr.ifr_hwaddr.sa_data, 6);
        boost::format fmt("%02X:%02X:%02X:%02X:%02X:%02X");
        for (int i = 0; i != 6; ++i) {
          fmt % static_cast<unsigned int>(ucMacAddress[i]);
        }
        vMacAddress = fmt.str();
      }
      else {
        cerr << "ERROR: failed SIOCGIFHWADDR request" << endl;
      }
    }
  }
  else {
    cerr << "ERROR: failed SIOCGIFFLAGS request" << endl;
  }
return vMacAddress.c_str();
}

//******************************************************************************
/**
 * Interface watchdog: notifies about appearance/disappearance of
 * network interfaces. Executed in the thread.
 *
 *
 * @param None.
 *
 * @return None.
 *
 */
//******************************************************************************
void *InterfaceManager::interfaceWatchdog(void *args)
{
  vector<string> vOldInterfaceList, vNewInterfaceList;
  bool isFirstCall = true;

  while (true)
  {
    vNewInterfaceList = InterfaceManager::getListOfInterfaces();
    if(!isFirstCall && vOldInterfaceList.size() != vNewInterfaceList.size()) {
      vector<string> vDiff;
      set_symmetric_difference(vOldInterfaceList.begin(),
                               vOldInterfaceList.end(),
                               vNewInterfaceList.begin(),
                               vNewInterfaceList.end(), 
                               back_inserter( vDiff ) );
      if(vOldInterfaceList.size() > vNewInterfaceList.size()) {
        for(int i=0;i<vDiff.size();++i) {
          cout << "\nGONE " << vDiff.at(i) << endl;
        }
      }
      else {
        for(int i=0;i<vDiff.size();++i) {
          cout << "\nNEW " << vDiff.at(i) << " " << 
               InterfaceManager::getHwAddr(vDiff.at(i)) << endl;
        }  
      }
      vDiff.clear();
    }
    vOldInterfaceList = vNewInterfaceList;
    isFirstCall = false;
    sleep(1);
  }
}

