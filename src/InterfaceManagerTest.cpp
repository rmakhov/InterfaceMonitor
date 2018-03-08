#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ifacemgrtest
#include <boost/test/included/unit_test.hpp>
#include "InterfaceManager.hpp"

BOOST_AUTO_TEST_SUITE (ifacemgrtest)

// Test for non-empty list of interfaces
BOOST_AUTO_TEST_CASE (test1)
{
  BOOST_REQUIRE(!InterfaceManager::getListOfInterfaces().empty());
}

// Test of handling of fake interface
BOOST_AUTO_TEST_CASE (test2)
{
  BOOST_REQUIRE(InterfaceManager::getHwAddr("fake_iface").size() == 0);
}

// Test of handling loopback interface
BOOST_AUTO_TEST_CASE (test3)
{
  BOOST_REQUIRE(InterfaceManager::getHwAddr("lo").size() == 0);
}

// Test of correct returned MAC address
BOOST_AUTO_TEST_CASE (test4)
{
  string iface = InterfaceManager::getListOfInterfaces().front();
  string mac = InterfaceManager::getHwAddr(iface);
  BOOST_REQUIRE(InterfaceManager::getHwAddr(iface).size() != 0);
  BOOST_REQUIRE((mac[0] >= '0' && mac[0] <= '9') ||
                (mac[0] >= 'A' && mac[0] <= 'Z') ||
                (mac[0] >= 'a' && mac[0] <= 'z'));
  BOOST_REQUIRE((mac[1] >= '0' && mac[1] <= '9') ||
                (mac[1] >= 'A' && mac[1] <= 'Z') ||
                (mac[1] >= 'a' && mac[1] <= 'z'));
  BOOST_REQUIRE_EQUAL (':', mac[2]);
  BOOST_REQUIRE((mac[3] >= '0' && mac[3] <= '9') ||
                (mac[3] >= 'A' && mac[3] <= 'Z') ||
                (mac[3] >= 'a' && mac[3] <= 'z'));
  BOOST_REQUIRE((mac[4] >= '0' && mac[4] <= '9') ||
                (mac[4] >= 'A' && mac[4] <= 'Z') ||
                (mac[4] >= 'a' && mac[4] <= 'z'));
  BOOST_REQUIRE_EQUAL (':', mac[5]);
  BOOST_REQUIRE((mac[6] >= '0' && mac[6] <= '9') ||
                (mac[6] >= 'A' && mac[6] <= 'Z') ||
                (mac[6] >= 'a' && mac[6] <= 'z'));
  BOOST_REQUIRE((mac[7] >= '0' && mac[7] <= '9') ||
                (mac[7] >= 'A' && mac[7] <= 'Z') ||
                (mac[7] >= 'a' && mac[7] <= 'z'));
  BOOST_REQUIRE_EQUAL (':', mac[8]);
  BOOST_REQUIRE((mac[9] >= '0' && mac[9] <= '9') ||
                (mac[9] >= 'A' && mac[9] <= 'Z') ||
                (mac[9] >= 'a' && mac[9] <= 'z'));
  BOOST_REQUIRE((mac[10] >= '0' && mac[10] <= '9') ||
                (mac[10] >= 'A' && mac[10] <= 'Z') ||
                (mac[10] >= 'a' && mac[10] <= 'z'));
  BOOST_REQUIRE_EQUAL (':', mac[11]);
  BOOST_REQUIRE((mac[12] >= '0' && mac[12] <= '9') ||
                (mac[12] >= 'A' && mac[12] <= 'Z') ||
                (mac[12] >= 'a' && mac[12] <= 'z'));
  BOOST_REQUIRE((mac[13] >= '0' && mac[13] <= '9') ||
                (mac[13] >= 'A' && mac[13] <= 'Z') ||
                (mac[13] >= 'a' && mac[13] <= 'z'));
  BOOST_REQUIRE_EQUAL (':', mac[14]);
  BOOST_REQUIRE((mac[15] >= '0' && mac[15] <= '9') ||
                (mac[15] >= 'A' && mac[15] <= 'Z') ||
                (mac[15] >= 'a' && mac[15] <= 'z'));
  BOOST_REQUIRE((mac[16] >= '0' && mac[16] <= '9') ||
                (mac[16] >= 'A' && mac[16] <= 'Z') ||
                (mac[16] >= 'a' && mac[16] <= 'z'));
}

BOOST_AUTO_TEST_SUITE_END( )
