//
// Test suite for flexCharManager
//

// get access to private variables
#include <bits/stdc++.h>

#define protected public
#define private public
#include <flexCharManager.h>
#undef protected
#undef private

#include <gtest/gtest.h>

#include <memory>

// utility function to check that the char manager's buffer contains the right amount of zeroes
testing::AssertionResult checkBufferZeroes(std::shared_ptr<flexCharManager> charManagerPtr, size_t zeroStartIndex, size_t zeroEndIndex = simpleCharManager::BUF_SIZE - 1)
{
	for(size_t index = zeroStartIndex; index <= zeroEndIndex; ++index)
	{
		if(charManagerPtr->buffer[index] != 0)
		{
			return testing::AssertionFailure() << "Buffer should have contained 0 at index " << index << ", but instead held " << charManagerPtr->buffer[index];
		}
	}

	return testing::AssertionSuccess();
}

// Utility function to write a string to a char array from the char manager.
// Does NOT write a null terminator.
void writeString(std::string const & string, char* array)
{
	memcpy(array, string.c_str(), string.length());
}

TEST(FlexCharManager, ConstructionDestruction)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());
}

TEST(FlexCharManager, InvalidFree)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	// these invalid frees should do nothing
	charManagerPtr->free_chars((char*)7);
	charManagerPtr->free_chars(nullptr);
	charManagerPtr->free_chars(charManagerPtr->buffer + 600);
}

TEST(FlexCharManager, ZeroFill)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	// the entire buffer should be filled with zeroes at construction time
	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 0));
}

TEST(FlexCharManager, OneCharAlloc)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(1);
	*allocatedPointer = 'A';

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);

}

TEST(FlexCharManager, OneCharFree)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(1);
	*allocatedPointer = 'A';

	charManagerPtr->free_chars(allocatedPointer);

	// char should have been set back to 0
	EXPECT_EQ('\0', *allocatedPointer);
}

TEST(FlexCharManager, FiveCharAlloc)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(1);
	writeString("Hello", allocatedPointer);

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);
	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 5));

}

TEST(FlexCharManager, FiveCharAllocFree)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(5);
	writeString("Hello", allocatedPointer);

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);
	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 5));

	charManagerPtr->free_chars(allocatedPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 0));

}

TEST(FlexCharManager, Alloc_x2)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);

	*firstPointer = 'A';
	secondPointer[0] = 'B';
	secondPointer[1] = 'C';

	EXPECT_EQ(charManagerPtr->buffer, firstPointer);
	EXPECT_EQ(charManagerPtr->buffer + 1, secondPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 3));

}

TEST(FlexCharManager, AllocFree_x2_RevOrder)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);

	*firstPointer = 'A';
	secondPointer[0] = 'B';
	secondPointer[1] = 'C';

	EXPECT_EQ(charManagerPtr->buffer, firstPointer);
	EXPECT_EQ(charManagerPtr->buffer + 1, secondPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 3));

	charManagerPtr->free_chars(secondPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 1));

	charManagerPtr->free_chars(firstPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 0));
}

TEST(FlexCharManager, AllocFree_x2_FwdOrder)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);

	*firstPointer = 'A';
	secondPointer[0] = 'B';
	secondPointer[1] = 'C';

	EXPECT_EQ(charManagerPtr->buffer, firstPointer);
	EXPECT_EQ(charManagerPtr->buffer + 1, secondPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 3));

	charManagerPtr->free_chars(firstPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 0, 0));
	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 3));

	charManagerPtr->free_chars(secondPointer);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 0));
}

TEST(FlexCharManager, MemoryReuse)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	const size_t numLoops = 20;
	const size_t blockSize = 100;

	// loop: allocate two areas of memory, then free the second one
	for(size_t loopCounter = 0; loopCounter < numLoops; ++loopCounter)
	{
		const char firstFillChar = static_cast<char>('A' + loopCounter * 2);
		const char secondFillChar = static_cast<char>('A' + loopCounter * 2 + 1);

		char * firstBuffer = charManagerPtr->alloc_chars(blockSize);
		memset(firstBuffer, firstFillChar, blockSize);

		ASSERT_TRUE(checkBufferZeroes(charManagerPtr, (loopCounter + 1) * blockSize));

		char * secondBuffer = charManagerPtr->alloc_chars(blockSize);
		memset(secondBuffer, secondFillChar, blockSize);

		ASSERT_TRUE(checkBufferZeroes(charManagerPtr, (loopCounter + 2) * blockSize));

		charManagerPtr->free_chars(secondBuffer);
		ASSERT_TRUE(checkBufferZeroes(charManagerPtr, (loopCounter + 1) * blockSize));

	}

}

TEST(FlexCharManager, Alloc10000Chars)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char* bigBlock = charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE);
	ASSERT_NE(bigBlock, nullptr);
	bigBlock[simpleCharManager::BUF_SIZE - 1] = '!';

	// trying to alloc any more should result in errors
	EXPECT_EQ(charManagerPtr->alloc_chars(1), nullptr);
	EXPECT_EQ(charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE), nullptr);
}


TEST(FlexCharManager, Alloc5Charx2000)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	std::vector<char*> allocatedPointers;

	for(int counter = 0; counter < simpleCharManager::BUF_SIZE / 5; ++counter)
	{
		char * fiveChars =  charManagerPtr->alloc_chars(5);
		ASSERT_NE(fiveChars, nullptr);
		writeString(std::string("ABCDE"), fiveChars);

		allocatedPointers.push_back(fiveChars);
	}

	// trying to alloc any more should result in errors
	EXPECT_EQ(charManagerPtr->alloc_chars(1), nullptr);
	EXPECT_EQ(charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE), nullptr);
}

TEST(FlexCharManager, AllocDealloc10Charx1000)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	std::vector<char*> allocatedPointers;

	for(int counter = 0; counter < simpleCharManager::BUF_SIZE / 10; ++counter)
	{
		char * fiveChars =  charManagerPtr->alloc_chars(10);
		ASSERT_NE(fiveChars, nullptr);
		writeString(std::string("ABCDE"), fiveChars);

		allocatedPointers.push_back(fiveChars);
	}

	for(int reverseCounter = static_cast<int>(allocatedPointers.size() - 1); reverseCounter >= 0; --reverseCounter)
	{
		charManagerPtr->free_chars(allocatedPointers[reverseCounter]);

		ASSERT_TRUE(checkBufferZeroes(charManagerPtr, reverseCounter * 10));
	}
}


TEST(FlexCharManager, RandomOrderDealloc)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	std::vector<char*> allocatedPointers;

	const int numBlocks = 500;
	const int blockSize = 5;

	for(int counter = 0; counter < numBlocks; ++counter)
	{
		char * fiveChars =  charManagerPtr->alloc_chars(blockSize);
		ASSERT_NE(fiveChars, nullptr);
		writeString(std::string("ABCDE"), fiveChars);

		allocatedPointers.push_back(fiveChars);
	}

	std::mt19937 randEngine;
	randEngine.seed(343);
	std::shuffle(allocatedPointers.begin(), allocatedPointers.end(), randEngine);

	for(size_t counter = 0; counter < allocatedPointers.size(); ++counter)
	{
		charManagerPtr->free_chars(allocatedPointers[counter]);
	}

	ASSERT_TRUE(checkBufferZeroes(charManagerPtr, 0));
}


TEST(FlexCharManager, BasicFirstFit)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(8);
	char * secondPointer = charManagerPtr->alloc_chars(4);

	ASSERT_NE(firstPointer, nullptr);
	ASSERT_NE(secondPointer, nullptr);

	writeString("Adda", secondPointer);

	charManagerPtr->free_chars(firstPointer);

	// should get allocated to space in front of secondPointer
	char* thirdPtr = charManagerPtr->alloc_chars(4);

	ASSERT_NE(thirdPtr, nullptr);
	EXPECT_EQ(charManagerPtr->buffer, thirdPtr);

	writeString("blah", thirdPtr);

	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 4, 7));
	EXPECT_TRUE(checkBufferZeroes(charManagerPtr, 12));
}


TEST(FlexCharManager, IntermediateFirstFit)
{
	std::shared_ptr<flexCharManager> charManagerPtr(std::make_shared<flexCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(2);
	char * firstSpacer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);
	char * secondSpacer = charManagerPtr->alloc_chars(2);
	char * thirdPointer = charManagerPtr->alloc_chars(3);
	char * thirdSpacer = charManagerPtr->alloc_chars(2);
	char * fourthPointer = charManagerPtr->alloc_chars(5);

	charManagerPtr->free_chars(firstSpacer);
	charManagerPtr->free_chars(thirdSpacer);
	charManagerPtr->free_chars(secondSpacer);

	writeString("Hi", firstPointer);
	writeString("in", secondPointer);
	writeString("the", thirdPointer);
	writeString("frame", fourthPointer);

	// at this point, the buffer should look like this:
	//
	// X X   X X     X X X     X X X X X
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20



	char * fourByteObj = charManagerPtr->alloc_chars(4);
	EXPECT_EQ(fourByteObj, (charManagerPtr->buffer + 17));

	// X X   X X     X X X     X X X X X A A A A
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20



	char * firstOneByteObj = charManagerPtr->alloc_chars(1);
	EXPECT_EQ(firstOneByteObj, (charManagerPtr->buffer + 2));

	// X X B X X     X X X     X X X X X A A A A
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20



	char * secondOneByteObj = charManagerPtr->alloc_chars(1);
	EXPECT_EQ(secondOneByteObj, (charManagerPtr->buffer + 5));

	// X X B X X C   X X X     X X X X X A A A A
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20



	char * twoByteObj = charManagerPtr->alloc_chars(2);
	EXPECT_EQ(twoByteObj, (charManagerPtr->buffer + 10));

	// X X B X X C   X X X D D X X X X X A A A A
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20


	char * thirdOneByteObj = charManagerPtr->alloc_chars(1);
	EXPECT_EQ(thirdOneByteObj, (charManagerPtr->buffer + 6));

	// X X B X X C E X X X D D X X X X X A A A A
	// - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20



	char * tenByteObj = charManagerPtr->alloc_chars(10);
	EXPECT_EQ(tenByteObj, (charManagerPtr->buffer + 21));

	// X X B X X C E X X X D D X X X X X A A A A F F F F F F F F F F
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// 0       4       8       12      16      20

}