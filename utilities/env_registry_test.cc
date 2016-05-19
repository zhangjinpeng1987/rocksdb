// Copyright (c) 2016-present, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef ROCKSDB_LITE

#include "rocksdb/utilities/env_registry.h"
#include "util/testharness.h"

namespace rocksdb {

class EnvRegistryTest : public testing::Test {
 public:
  static int num_a, num_b;
};

int EnvRegistryTest::num_a = 0;
int EnvRegistryTest::num_b = 0;

static EnvRegistrar test_reg_a("a://", [](const std::string& uri) {
  ++EnvRegistryTest::num_a;
  return std::unique_ptr<Env>(new EnvWrapper(Env::Default()));
});

static EnvRegistrar test_reg_b("b://", [](const std::string& uri) {
  ++EnvRegistryTest::num_b;
  return std::unique_ptr<Env>(new EnvWrapper(Env::Default()));
});

TEST_F(EnvRegistryTest, Basics) {
  auto res = NewEnvFromUri("a://test");
  ASSERT_NE(res, nullptr);
  ASSERT_EQ(1, num_a);
  ASSERT_EQ(0, num_b);

  res = NewEnvFromUri("b://test");
  ASSERT_NE(res, nullptr);
  ASSERT_EQ(1, num_a);
  ASSERT_EQ(1, num_b);

  res = NewEnvFromUri("c://test");
  ASSERT_EQ(res, nullptr);
  ASSERT_EQ(1, num_a);
  ASSERT_EQ(1, num_b);
}

}  // namespace rocksdb

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#else  // ROCKSDB_LITE
#include <stdio.h>

int main(int argc, char** argv) {
  fprintf(stderr, "SKIPPED as EnvRegistry is not supported in ROCKSDB_LITE\n");
  return 0;
}

#endif  // ROCKSDB_LITE
