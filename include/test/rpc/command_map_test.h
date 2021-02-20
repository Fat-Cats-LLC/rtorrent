#include <cppunit/extensions/HelperMacros.h>

#include "rpc/command_map.h"

class CommandMapTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CommandMapTest);
  CPPUNIT_TEST(test_basics);
  CPPUNIT_TEST_SUITE_END();

public:
  static constexpr int cmd_size = 256;

  void setUp() override {
    m_commandItr = m_commands;
  }
  void tearDown() override {}

  void test_basics();

private:
  rpc::CommandMap m_map;

  rpc::command_base  m_commands[cmd_size];
  rpc::command_base* m_commandItr;
};
