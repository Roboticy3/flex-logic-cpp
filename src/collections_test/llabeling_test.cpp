// cpp-test/flex-logic-cpp/src/collections_test/llabeling_test.cpp
#include <string>
#include <vector>

#include "test_definitions.h"
#include "collections_test/llabeling_test.h"
#include "collections/llabeling.h"

int llabeling_test() {
  // Run all declared tests
  test_add();
  test_set();
  test_get();
  test_remove();
  test_add_remove_add();
  
  // BlockLabeling tests
  test_block_add_remove();
  test_block_get();
  test_block_compress();
  test_block_edge_cases();
  test_block_reuse();

  return TestSingleton::status("llabeling test");
}

// Llabeling tests

void test_add() {
  TestSingleton::start("add");
  Labeling<std::string> labels;
  
  labels.add("example");
  labels.add("test");

  TestSingleton::assert<int>(labels.size(), 2, "size");
}

void test_set() {
  TestSingleton::start("set");
  Labeling<std::string> labels;
  
  labels.set("example", 2);

  TestSingleton::assert<int>(labels.size(), 3, "size");
  std::string* val = labels.get(2);
  TestSingleton::assert<bool>(val != nullptr && *val == "example", true, "value at position 2");
}

void test_get() {
  TestSingleton::start("get");
  Labeling<std::string> labels;
  
  labels.set("example", 1);

  std::string* val1 = labels.get(1);
  TestSingleton::assert<bool>(val1 != nullptr && *val1 == "example", true, "value at position 1");
  
  std::string* val0 = labels.get(0);
  TestSingleton::assert<bool>(val0 == nullptr, true, "nil at position 0");
}

void test_remove() {
  TestSingleton::start("remove");
  Labeling<std::string> labels;
  
  labels.set("example", 1);
  labels.remove(1);

  std::string* val = labels.get(1);
  TestSingleton::assert<bool>(val == nullptr, true, "nil at position 1 after removal");
}

void test_add_remove_add() {
  TestSingleton::start("add remove add");
  Labeling<std::string> labels;
  
  ll first_label = labels.add("first");
  ll second_label = labels.add("second");
  
  labels.remove(second_label);
  
  ll third_label = labels.add("third");
  
  TestSingleton::assert<bool>(third_label == second_label, true, "new element should reuse removed index");
  std::string* val = labels.get(third_label);
  TestSingleton::assert<bool>(val != nullptr && *val == "third", true, "value at reused index should be 'third'");
}

// BlockLabeling Tests

void test_block_add_remove() {
    TestSingleton::start("BlockLabeling add_block and remove_block");
    BlockLabeling<int> blocks;
    
    // Test adding a block
    auto block1 = blocks.add_block(3);
    TestSingleton::assert<int>(block1.size, 3, "block1 size should be 3");
    
    // Test block values are initialized to default
    if (block1.base == nullptr) {
      TestSingleton::shout("block1 did not instantiate correctly");
    }
    TestSingleton::assert<int>(block1[0], 0, "block1[0] should be default (0)");
    
    // Test removing the block
    bool remove_result = blocks.remove_block(block1.index);
    TestSingleton::assert<bool>(remove_result, true, "remove_block should return true for valid block");
    
    // Test removing non-existent block
    remove_result = blocks.remove_block(999);
    TestSingleton::assert<bool>(remove_result, false, "remove_block should return false for invalid block");
}

void test_block_get() {
    TestSingleton::start("BlockLabeling get_block");
    BlockLabeling<std::string> blocks;
    
    // Add and retrieve a block
    auto block1 = blocks.add_block(2);

    if (block1.base == nullptr) {
      TestSingleton::shout("block1 did not instantiate correctly");
    }

    block1[0] = "hello";
    block1[1] = "world";
    
    auto retrieved = blocks.get_block(block1.index);
    TestSingleton::assert<int>(retrieved.size, 2, "retrieved block size should be 2");
    TestSingleton::assert<const char*>(retrieved[0].c_str(), block1[0].c_str(), "retrieved[0] should be 'hello'");
    TestSingleton::assert<const char*>(retrieved[1].c_str(), block1[1].c_str(), "retrieved[1] should be 'world'");
    
    // Test getting non-existent block
    auto invalid = blocks.get_block(999);
    TestSingleton::assert<int>(invalid.size, 0, "invalid block size should be 0");
}

void test_block_compress() {
    TestSingleton::start("BlockLabeling compress_blocks");
    BlockLabeling<int> blocks;
    
    // Add some blocks
    auto block1 = blocks.add_block(2);

    if (block1.base == nullptr) {
      TestSingleton::shout("block1 did not instantiate correctly");
    }

    block1[0] = 1;
    block1[1] = 2;

    /*
    Keeping this around as an example of how to debug using my test system

    TestSingleton::shout("Added block at " + std::to_string(block1.index) + "\n\t\t(buffer: ", 0);
    TestSingleton::print_vector(blocks.copy_buffer());
    TestSingleton::shout("; blocks: ", 0);
    TestSingleton::print_vector(blocks.copy_blocks());
    TestSingleton::shout(")", 0);
    */
    
    auto block2 = blocks.add_block(3);

    if (block2.base == nullptr) {
      TestSingleton::shout("block2 did not instantiate correctly");
    }

    block2[0] = 3;
    block2[1] = 4;
    block2[2] = 5;

    /*
    TestSingleton::shout("Added block at " + std::to_string(block2.index) + "\n\t\t(buffer: ", 0);
    TestSingleton::print_vector(blocks.copy_buffer());
    TestSingleton::shout("; blocks: ", 0);
    TestSingleton::print_vector(blocks.copy_blocks());
    TestSingleton::shout(")", 0);
    */
    
    // Remove the first block
    blocks.remove_block(block1.index);

    /*
    TestSingleton::shout("Removed block at " + std::to_string(block1.index) + "\n\t\t(buffer: ", 0);
    TestSingleton::print_vector(blocks.copy_buffer());
    TestSingleton::shout("; blocks: ", 0);
    TestSingleton::print_vector(blocks.copy_blocks());
    TestSingleton::shout(")", 0);
    */
    
    // Compress and verify
    auto compressed = blocks.compress_blocks();
    TestSingleton::assert<size_t>(compressed.size(), 1, "should have 1 block after compression");
    TestSingleton::assert<size_t>(compressed[0].size(), 3, "compressed block should have 3 elements");
    TestSingleton::assert<int>(compressed[0][0], 3, "compressed[0][0] should be 3");
}

void test_block_edge_cases() {
    TestSingleton::start("BlockLabeling edge cases");
    BlockLabeling<int> blocks;
    
    // Test adding empty block
    auto empty_block = blocks.add_block(0);
    TestSingleton::assert<int>(empty_block.size, 0, "empty block should have size 0");
    
    // Test adding block with start position
    blocks.add_block(2); // First block
    auto block2 = blocks.add_block(2, 0); // Should skip first position
    TestSingleton::assert<int>(block2.index >= 2, true, "second block should start after first block");
    
    // Test block reuse after removal
    blocks.remove_block(block2.index);
    auto block3 = blocks.add_block(1, 0);
    TestSingleton::assert<int>(block3.index, block2.index, "should reuse space from removed block");
}

void test_block_reuse() {
    TestSingleton::start("BlockLabeling block reuse");
    BlockLabeling<char> blocks;
    
    // Add and remove multiple blocks
    std::vector<size_t> block_indices;
    for (int i = 0; i < 5; i++) {
        auto block = blocks.add_block(2);

        if (block.base == nullptr) {
          std::string msg = "block " + std::to_string(i) + " did not instantiate correctly";
          TestSingleton::shout(msg);
        }

        block[0] = 'a' + i;
        block[1] = 'A' + i;
        block_indices.push_back(block.index);
    }
    
    // Remove some blocks
    blocks.remove_block(block_indices[1]);
    blocks.remove_block(block_indices[3]);
    
    // Add new blocks that should fit in the gaps
    auto new_block1 = blocks.add_block(2, 0);
    TestSingleton::assert<int>(new_block1.index, block_indices[1], "should reuse first gap");
    
    auto new_block2 = blocks.add_block(2, 0);
    TestSingleton::assert<int>(new_block2.index, block_indices[3], "should reuse second gap");
    
    // Add another block that should go to the end
    auto last_block = blocks.add_block(2);
    TestSingleton::assert<int>(last_block.index >= 10, true, "new block should be at the end");
}