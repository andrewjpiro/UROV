// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>
#include "Printers.hpp"

class JsonObject_Iterator_Test : public testing::Test {
 public:
  JsonObject_Iterator_Test() : object(_buffer.createObject()) {
    object["ab"] = 12;
    object["cd"] = 34;
  }

 protected:
  StaticJsonBuffer<256> _buffer;
  JsonObject& object;
};

TEST_F(JsonObject_Iterator_Test, NonConstIterator) {
  JsonObject::iterator it = object.begin();
  ASSERT_NE(object.end(), it);
  EXPECT_STREQ("ab", it->key);
  EXPECT_EQ(12, it->value);
  it->key = "a.b";
  it->value = 1.2;
  ++it;
  ASSERT_NE(object.end(), it);
  EXPECT_STREQ("cd", it->key);
  EXPECT_EQ(34, it->value);
  it->key = "c.d";
  it->value = 3.4;
  ++it;
  ASSERT_EQ(object.end(), it);

  ASSERT_EQ(2, object.size());
  EXPECT_EQ(1.2, object["a.b"]);
  EXPECT_EQ(3.4, object["c.d"]);
}

TEST_F(JsonObject_Iterator_Test, ConstIterator) {
  const JsonObject& const_object = object;
  JsonObject::const_iterator it = const_object.begin();

  ASSERT_NE(const_object.end(), it);
  EXPECT_STREQ("ab", it->key);
  EXPECT_EQ(12, it->value);
  ++it;
  ASSERT_NE(const_object.end(), it);
  EXPECT_STREQ("cd", it->key);
  EXPECT_EQ(34, it->value);
  ++it;
  ASSERT_EQ(const_object.end(), it);
}
