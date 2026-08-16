// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
#include "gtest/gtest.h"
//
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
 //TEST_F(CollectionTest, AlwaysFail)
 //{
 //    FAIL();
 //}

 // 1. Verify that one value can be added to an empty vector.
TEST_F(CollectionTest, CanAddSingleValueToEmptyVector)
{
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1);
}

// 2. Verify that five values can be added to a vector.
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    ASSERT_TRUE(collection->empty());

    add_entries(5);

    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5);
}

// 3. Verify max_size() is always at least as large as size().
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToCurrentSize)
{
    const int entry_counts[] = { 0, 1, 5, 10 };

    for (const int count : entry_counts)
    {
        collection->clear();

        if (count > 0)
        {
            add_entries(count);
        }

        EXPECT_GE(collection->max_size(), collection->size());
        EXPECT_EQ(collection->size(), static_cast<std::size_t>(count));
    }
}

// 4. Verify capacity() is always at least as large as size().
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToCurrentSize)
{
    const int entry_counts[] = { 0, 1, 5, 10 };

    for (const int count : entry_counts)
    {
        collection->clear();

        if (count > 0)
        {
            add_entries(count);
        }

        EXPECT_GE(collection->capacity(), collection->size());
        EXPECT_EQ(collection->size(), static_cast<std::size_t>(count));
    }
}

// 5. Verify resize() can increase the vector size.
TEST_F(CollectionTest, ResizeIncreasesCollectionSize)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    collection->resize(10);

    EXPECT_EQ(collection->size(), 10);
    EXPECT_FALSE(collection->empty());
}

// 6. Verify resize() can decrease the vector size.
TEST_F(CollectionTest, ResizeDecreasesCollectionSize)
{
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    collection->resize(5);

    EXPECT_EQ(collection->size(), 5);
    EXPECT_FALSE(collection->empty());
}

// 7. Verify resize(0) removes all elements.
TEST_F(CollectionTest, ResizeToZeroEmptiesCollection)
{
    add_entries(10);
    ASSERT_FALSE(collection->empty());

    collection->resize(0);

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// 8. Verify clear() removes all elements.
TEST_F(CollectionTest, ClearErasesEntireCollection)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    collection->clear();

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// 9. Verify erase(begin, end) removes all elements.
TEST_F(CollectionTest, EraseRangeErasesEntireCollection)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    collection->erase(collection->begin(), collection->end());

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// 10. Verify reserve() increases capacity without changing size.
TEST_F(CollectionTest, ReserveIncreasesCapacityWithoutChangingSize)
{
    add_entries(5);

    const std::size_t original_size = collection->size();
    const std::size_t requested_capacity = collection->capacity() + 20;

    collection->reserve(requested_capacity);

    EXPECT_EQ(collection->size(), original_size);
    EXPECT_GE(collection->capacity(), requested_capacity);
}

// 11. Negative test: at() throws when an empty vector is accessed.
TEST_F(CollectionTest, AtThrowsOutOfRangeForEmptyCollection)
{
    ASSERT_TRUE(collection->empty());

    EXPECT_THROW(collection->at(0), std::out_of_range);
}

// 12 Verify push_back() stores the correct value.
TEST_F(CollectionTest, PushBackStoresExpectedValue)
{
    const int expected_value = 42;

    collection->push_back(expected_value);

    ASSERT_EQ(collection->size(), 1);
    EXPECT_EQ(collection->front(), expected_value);
    EXPECT_EQ(collection->back(), expected_value);
}

// 13. An index equal to size() is one position past the final valid element.
TEST_F(CollectionTest, AtThrowsOutOfRangeAtUpperBoundary)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);

    EXPECT_THROW(collection->at(collection->size()), std::out_of_range);
}