#include <assert.h>
#include <string>
#include <sstream>

#include "hashTable.h"
#include "testUtils.h"

typedef HashTable<int, std::string> TestTable;

std::string stringWithSuffix(int suffix) {
  std::stringstream fmt;
  fmt << "hello" << suffix;
  return fmt.str();
}

void testInsert() {
  TestTable table;
  std::string s;
  for (int i = 0; i < 1000; i++) {
    s = table.insert(i, stringWithSuffix(i));
    assert(s == stringWithSuffix(i));
  }
}

void testRemove() {
  TestTable table;

  // Non-existing value
  THROWS(table.remove(123), TestTable::NoSuchEntry);

  // Add some values
  for (int i = 0; i < 1000; i++)
      table.insert(i, stringWithSuffix(i));

  // Remove them now, in a different order
  for (int i = 999; i >= 0; i--)
    table.remove(i);

  // Empty array again
  THROWS(table.remove(123), TestTable::NoSuchEntry);
}

void testLength() {
  TestTable table;

  // Empty
  assert(table.length() == 0);

  // With values
  for (int i = 0; i < 1000; i++) {
    table.insert(i, stringWithSuffix(i));
    assert(table.length() == i+1);
  }
  // Set them again
  for (int i = 0; i < 1000; i++) {
    table[i] = stringWithSuffix(1000+i);
    assert(table.length() == 1000);
  }

  // Remove them with a messy order
  for (int i = 0; i < 1000; i+=2) {
    table.remove(i);
    assert(table.length() == 1000-(i/2+1));
  }
  for (int i = 1; i < 1000; i+=2) {
    table.remove(i);
    assert(table.length() == 500 - ((i-1)/2 + 1));
  }
}

void testGet() {
  TestTable table;

  // Empty
  THROWS(table[0], TestTable::NoSuchEntry);

  // Add a value and save its reference
  // Save some value reference
  std::string& valueThousand(table.insert(10000, "Test"));

  // Add more values, causing resize
  for (int i = 0; i < 1000; i++) {
    table.insert(i, stringWithSuffix(i));
    assert(table[i] == stringWithSuffix(i));
  }

  // Save another value reference
  std::string& valueZero(table[0]);

  // Set values again
  for (int i = 0; i < 1000; i++) {
    table[i] = stringWithSuffix(1000+i);
    assert(table[i] == stringWithSuffix(1000+i));
  }

  // references should still be correct
  assert(valueThousand == "Test");
  assert(valueThousand == table[10000]);
  assert(valueZero == table[0]);

  // Remove
  for (int i = 0; i < 1000; i++) {
    table.remove(i);
    THROWS(table[i], TestTable::NoSuchEntry);
  }
}

void testSet() {
  TestTable table;

  // Add some values
  for (int i = 0; i < 1000; i++)
    table.insert(i, stringWithSuffix(i));

  // Set them again
  for (int i = 0; i < 1000; i++)
    table[i] = stringWithSuffix(2000+i);
}

int main() {
  RUN_TEST(testInsert);
  RUN_TEST(testRemove);
  RUN_TEST(testLength);
  RUN_TEST(testGet);
  RUN_TEST(testSet);
  return 0;
}
