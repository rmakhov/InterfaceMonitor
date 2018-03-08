InterfaceMonitord is daemon for monitoring network interfaces.
After startup it displays the current network interfaces every second,
in the format:
IFACE <interface name> <MAC address>

In case if new interface is started up, then the following string
is displayed on the console:
NEW <interface name> <MAC address>

The following string is displayed after interface shutdown:
GONE <interface name>

================================================================================

Please perform the following:
-to compile InterfaceMonitord:
> make all

-to run InterfaceMonitord
> cd out
> ./InterfaceMonitord

- press Ctrl-C to shutdown daemon

- to run Unit Tests:
> make test

================================================================================

Daemon is compiled and tested on the platform:
Ubuntu 12.10 desktop i386

The following packages has been installed additionally:
build-essential
libboost-all-dev

Roman Makhov (roman.makhov@gmail.com)
