#include "pch.h"

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // Add 1 entries
    add_entries(1);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // Add 5 entries
    add_entries(5);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
}

// Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsMaxSizeGreaterOrEqualSize)
{
    // Check for 0
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 1
    add_entries(1);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 1);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 5
    add_entries(4);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 10
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 10);
    // if empty, the size must be 0
    ASSERT_GE(collection->max_size(), collection->size());
}

// Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsCapacityGreaterOrEqualSize)
{   
    // Check for 0
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // if empty, the size must be 0
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 1
    add_entries(1);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 1);
    // if empty, the size must be 0
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 5
    add_entries(4);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // if empty, the size must be 0
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 10
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 10);
    // if empty, the size must be 0
    ASSERT_GE(collection->capacity(), collection->size());
}


// Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CanResizeIncreaseCollection)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    // Add 5 entries
    collection->resize(5);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
}

// Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CanResizeDecreaseCollection)
{
    // Add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // Resize to 1
    collection->resize(1);
    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CanResizeDecreaseCollectionToZero)
{
    // Add 5 entries
    add_entries(5);
    // is the collection empty?
    ASSERT_FALSE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 5);
    // Resize to 1
    collection->resize(0);
    // is the collection still empty?
    ASSERT_TRUE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify clear erases the collection
TEST_F(CollectionTest, CanClearCollection)
{
    // Add 5 entries
    add_entries(5);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
    // Call the clear function
    collection->clear();
    // Check if collection is empty
    ASSERT_TRUE(collection->empty());
    // Check the size
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CanEraseClearCollection)
{
    // Add 5 entries
    add_entries(5);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
    // Call the erase function
    collection->erase(collection->begin(), collection->end());
    // Check if collection is empty
    ASSERT_TRUE(collection->empty());
    // Check the size
    ASSERT_EQ(collection->size(), 0);
}

// Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CanReserveIncreaseCapacity)
{
    // Add 5 entries
    add_entries(1);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
    // Whats the capacity?
    ASSERT_EQ(collection->capacity(), 1);
    // Call the reserve function
    collection->reserve(6);
    // Check the capacity
    ASSERT_EQ(collection->capacity(), 6);
    // Check the size is still 1
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CanThrowAtOutOfRange)
{
    // Add 5 entries
    add_entries(1);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
    // Check if the collection throws
    ASSERT_THROW(collection->at(2), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// 
TEST_F(CollectionTest, CanInsertCollection)
{
    // Is the collection empty
    ASSERT_TRUE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 0);
    // Emplace Back
    collection->emplace(collection->end(), 1);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Create a test to verify std::length_error when reserving larger than max_size();
// NOTE: This is a negative test
TEST_F(CollectionTest, CanThrowLengthErrorOnMaxSize)
{
    // Add 5 entries
    add_entries(1);
    // Is the collection empty
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
    // Check if the collection throws
    ASSERT_THROW(collection->reserve(1073741824), std::length_error);
}