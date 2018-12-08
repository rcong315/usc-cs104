//
// CS104 Heap test suite
//

#include <MinHeap.h>

#include <gtest/gtest.h>

#include <random_generator.h>

#include <queue>
#include <algorithm>

#define RANDOM_HEAP_ARY 0
const int MAX_HEAP_ARY = 26;
const int DEFAULT_HEAP_ARY = 2;

// Declaration for the type of item that will be stored in the heap.
typedef int IntType;

// Declaration for the type of std::heap used when checking during stress tests.
typedef std::priority_queue<IntType, std::deque<IntType>, std::greater<IntType> > __CPP_PRIORITY_QUEUE_TYPE_DECL;


// The random seed used to initialize the random number generator. If set to std::random_device()() then the
// tests will truly be random. Otherwise it should be set to some literal integer.
#define RANDOM_SEED 57821

// Testing setup.
class HeapTest : public testing::Test
{
protected:
	HeapTest()
	{
#if RANDOM_HEAP_ARY
		__RANDOM_NUMBER_GENERATOR randomGenerator{ RANDOM_SEED };
			D_ARY = randomGenerator() % MAX_HEAP_ARY + 3;
#else
		D_ARY = DEFAULT_HEAP_ARY;
#endif
	}
	~HeapTest() { }
	virtual void SetUp() { }
	virtual void TearDown() { }

	int D_ARY;
};

/**
 * Check that the given heap contains the elements from contents.
 * Will remove all elements from the heap.
 * Assumes that each integer has been inserted into the heap with priority the same as the integer.
 * @param heap
 * @param contents
 * @return
 */
testing::AssertionResult checkHeapContents(MinHeap<int> & heap, std::vector<int> contents)
{
	// sort vector least to greatest so that the order of elements matches the order in the heap
	std::sort(contents.begin(), contents.end());

	for(size_t index = 0; index < contents.size(); ++index)
	{
		if(heap.isEmpty())
		{
			return testing::AssertionFailure() << "Heap is missing " << (contents.size() - index) << " elements!  Only has " << index << ", should have had " << contents.size();
		}

		if(heap.peek() != contents[index])
		{
			return testing::AssertionFailure() << "Incorrect element value at depth " << index << "!  Was " << heap.peek() << ", expected " << contents[index];
		}

		heap.remove();
	}

	if(!heap.isEmpty())
	{
		return testing::AssertionFailure() << "Heap has extra elements!  Should have had " << contents.size() << "elements";
	}

	return testing::AssertionSuccess();
}

TEST_F(HeapTest, ConstructionDestruction)
{
	MinHeap<IntType> heap(D_ARY);
}

TEST_F(HeapTest, InitiallyEmpty)
{
	MinHeap<IntType> heap(D_ARY);
	EXPECT_TRUE(heap.isEmpty());
}

TEST_F(HeapTest, EmptyPeekException)
{
	MinHeap<IntType> heap(D_ARY);
	EXPECT_ANY_THROW(heap.peek());
}

TEST_F(HeapTest, EmptyRemoveException)
{
	MinHeap<IntType> heap(D_ARY);
	EXPECT_ANY_THROW(heap.remove());
}

TEST_F(HeapTest, SingleItemNonempty)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(2, 1);
	EXPECT_FALSE(heap.isEmpty());
}

TEST_F(HeapTest, SingleItemPush)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 1);
	EXPECT_EQ(10, heap.peek());
}

TEST_F(HeapTest, SingleItemPushPop)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 1);
	heap.remove();
	EXPECT_TRUE(heap.isEmpty());
}

TEST_F(HeapTest, TwoElementPush_LowPriFirst)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 3);
	heap.add(20, 10);
	EXPECT_EQ(10, heap.peek());

	heap.remove();

	EXPECT_EQ(20, heap.peek());
}

TEST_F(HeapTest, TwoElementPush_HighPriFirst)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 50);
	heap.add(20, 49);
	EXPECT_EQ(20, heap.peek());

	heap.remove();

	EXPECT_EQ(10, heap.peek());
}

TEST_F(HeapTest, TwoElementsSamePriority)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(20, 9);
	heap.add(10, 9);
	EXPECT_TRUE((heap.peek() == 10) || (heap.peek() == 20));
}

TEST_F(HeapTest, NegativePriorities)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(20, 9999);
	heap.add(10, -9999);
	EXPECT_EQ(10, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_10_20_30)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 0);
	heap.add(20, 5);
	heap.add(30, 10);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_10_30_20)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(10, 0);
	heap.add(30, 10);
	heap.add(20, 5);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_20_10_30)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(20, 5);
	heap.add(10, 0);
	heap.add(30, 10);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_20_30_10)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(20, 5);
	heap.add(30, 10);
	heap.add(10, 0);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_30_10_20)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(30, 10);
	heap.add(10, 0);
	heap.add(20, 5);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_30_20_10)
{
	MinHeap<IntType> heap(D_ARY);
	heap.add(30, 10);
	heap.add(20, 5);
	heap.add(10, 0);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, StringStorage)
{
	MinHeap<std::string> stringHeap(D_ARY);

	stringHeap.add("blah", 25);
	stringHeap.add("bluh", 30);
	stringHeap.add("bloh", 35);
	EXPECT_EQ("blah", stringHeap.peek());
	stringHeap.remove();
	EXPECT_EQ("bluh", stringHeap.peek());
	stringHeap.remove();
	EXPECT_EQ("bloh", stringHeap.peek());
}

TEST_F(HeapTest, ThreeElementPush_TrinaryHeap)
{
	MinHeap<IntType> heap(3);
	heap.add(10, 0);
	heap.add(20, 5);
	heap.add(30, 10);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST_F(HeapTest, ThreeElementPush_QuaternaryHeap)
{
	MinHeap<IntType> heap(4);
	heap.add(10, 0);
	heap.add(20, 5);
	heap.add(30, 10);
	EXPECT_EQ(10, heap.peek());
	heap.remove();
	EXPECT_EQ(20, heap.peek());
	heap.remove();
	EXPECT_EQ(30, heap.peek());
}

TEST(HeapStress, 50x50RandomElements_BinaryHeap)
{
	const RandomSeed masterSeed = 3764;
	const size_t numTrials = 50;
	const size_t numElements = 50;
	const size_t d = 2;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		MinHeap<int> heap(d);

		for(int value : data)
		{
			// add each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			heap.add(value, value);
		}

		EXPECT_TRUE(checkHeapContents(heap, data));
	}
}

TEST(HeapStress, 50x50RandomElements_QuaternaryHeap)
{
	const RandomSeed masterSeed = 99;
	const size_t numTrials = 50;
	const size_t numElements = 50;
	const size_t d = 4;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		MinHeap<int> heap(d);

		for(int value : data)
		{
			// add each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			heap.add(value, value);
		}

		EXPECT_TRUE(checkHeapContents(heap, data));
	}
}

TEST(HeapStress, 50x50RandomElements_DodecenaryHeap)
{
	const RandomSeed masterSeed = 674;
	const size_t numTrials = 50;
	const size_t numElements = 50;
	const size_t d = 12;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		MinHeap<int> heap(d);

		for(int value : data)
		{
			// add each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			heap.add(value, value);
		}

		EXPECT_TRUE(checkHeapContents(heap, data));
	}
}

TEST(HeapStress, 2x10000RandomElements_Binary)
{
	const RandomSeed masterSeed = 2434;
	const size_t numTrials = 2;
	const size_t numElements = 10000;
	const size_t d = 2;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		MinHeap<int> heap(d);

		for(int value : data)
		{
			// add each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			heap.add(value, value);
		}

		EXPECT_TRUE(checkHeapContents(heap, data));
	}
}