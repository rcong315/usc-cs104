//
// Test suite for simpleCharManager
//

// get access to private variables
#define protected public
#define private public
#include <simpleCharManager.h>
#undef protected
#undef private

#include <gtest/gtest.h>

#include <memory>

// utility function to check that the char manager's buffer contains the right amount of zeroes
testing::AssertionResult checkBufferZeroes(std::shared_ptr<simpleCharManager> charManagerPtr, size_t zeroStartIndex)
{
	for(size_t index = 0; index < simpleCharManager::BUF_SIZE; ++index)
	{
		if(index < zeroStartIndex)
		{
			if(charManagerPtr->buffer[index] == 0)
			{
				return testing::AssertionFailure() << "Buffer should not have contained 0 at index " << index << ", but was a 0";
			}
		}
		else
		{
			if(charManagerPtr->buffer[index] != 0)
			{
				return testing::AssertionFailure() << "Buffer should have contained 0 at index " << index << ", but instead held " << charManagerPtr->buffer[index];
			}
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

TEST(SimpleCharManager, ConstructionDestruction)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());
}


TEST(SimpleCharManager, OneCharAlloc)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(1);
	ASSERT_NE(allocatedPointer, nullptr);
	*allocatedPointer = 'A';

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);

}

TEST(SimpleCharManager, OneCharFree)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(1);
	ASSERT_NE(allocatedPointer, nullptr);
	*allocatedPointer = 'A';

	charManagerPtr->free_chars(allocatedPointer);
}

TEST(SimpleCharManager, FiveCharAlloc)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(5);
	writeString("Hello", allocatedPointer);

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);
}

TEST(SimpleCharManager, FiveCharAllocFree)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * allocatedPointer = charManagerPtr->alloc_chars(5);
	writeString("Hello", allocatedPointer);

	// we should have gotten the first address in the buffer
	EXPECT_EQ(charManagerPtr->buffer, allocatedPointer);

	charManagerPtr->free_chars(allocatedPointer);
}


TEST(SimpleCharManager, AllocFree_x2)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);

	*firstPointer = 'A';
	secondPointer[0] = 'B';
	secondPointer[1] = 'C';

	EXPECT_EQ(charManagerPtr->buffer, firstPointer);
	EXPECT_EQ(charManagerPtr->buffer + 1, secondPointer);

	charManagerPtr->free_chars(secondPointer);

	charManagerPtr->free_chars(firstPointer);
}

TEST(SimpleCharManager, FreeAll)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char * firstPointer = charManagerPtr->alloc_chars(1);
	char * secondPointer = charManagerPtr->alloc_chars(2);
	char * thirdPointer = charManagerPtr->alloc_chars(3);

	writeString("I", firstPointer);
	writeString("do", secondPointer);
	writeString("not", thirdPointer);

	charManagerPtr->free_chars(firstPointer);
}


TEST(SimpleCharManager, Alloc10000Chars)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	char* bigBlock = charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE);
	ASSERT_NE(bigBlock, nullptr);
	bigBlock[simpleCharManager::BUF_SIZE - 1] = '!';

	// trying to alloc any more should result in errors
	EXPECT_EQ(charManagerPtr->alloc_chars(1), nullptr);
	EXPECT_EQ(charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE), nullptr);
}

TEST(SimpleCharManager, Alloc1Charx10000)
{
	std::shared_ptr<simpleCharManager> charManagerPtr(std::make_shared<simpleCharManager>());

	for(int counter = 0; counter < simpleCharManager::BUF_SIZE; ++counter)
	{
		char * singleChar =  charManagerPtr->alloc_chars(1);
		ASSERT_NE(singleChar, nullptr);
		*singleChar = 'B';
	}

	// trying to alloc any more should result in errors
	EXPECT_EQ(charManagerPtr->alloc_chars(1), nullptr);
	EXPECT_EQ(charManagerPtr->alloc_chars(simpleCharManager::BUF_SIZE), nullptr);
}