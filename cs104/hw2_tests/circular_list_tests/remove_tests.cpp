#include <gtest/gtest.h>

#include <circular_list_int.h>

#include <circular_list_utils.h>
#include <random_generator.h>
#include <misc_utils.h>

// ----------------------------------------
// CS104 HW2 Problem 2 remove test file
// ----------------------------------------

TEST(ListRemove, ZeroElementRemove)
{
    CircularListInt list;

    // should do nothing
    list.remove(0);
    list.remove(7500);

    EXPECT_EQ(0, list.size());
    EXPECT_EQ(true, list.empty());
}

TEST(ListRemove, RepeatedOneEleRemove)
{
    CircularListInt list;

    for(int count = 0; count < 4; ++count)
    {
        list.push_back(3);

        EXPECT_EQ(3, list.get(0));

        list.remove(0);

        EXPECT_EQ(0, list.size());
        EXPECT_EQ(true, list.empty());
    }
}

TEST(ListRemove, Head2Elements)
{
    std::vector<int> contents{9, -800};
    CircularListInt * list = makeCircularList(contents);

    list->remove(0);

    contents.erase(contents.begin());
    EXPECT_TRUE(checkListContent(list, contents));

    delete list;
}

TEST(ListRemove, Tail2Elements)
{
    std::vector<int> contents{9, -800};
    CircularListInt * list = makeCircularList(contents);

    list->remove(1);

    contents.erase(contents.begin() + 1);
    EXPECT_TRUE(checkListContent(list, contents));

    delete list;
}

TEST(ListRemove, Head3Elements)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    list->remove(0);

    contents.erase(contents.begin());
    EXPECT_TRUE(checkListContent(list, contents));

    delete list;
}

TEST(ListRemove, Middle3Elements)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    list->remove(1);

    contents.erase(contents.begin() + 1);
    EXPECT_TRUE(checkListContent(list, contents));

    delete list;
}

TEST(ListRemove, Tail3Elements)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    list->remove(2);

    contents.erase(contents.begin() + 2);
    EXPECT_TRUE(checkListContent(list, contents));

    delete list;
}

TEST(ListRemove, ThreeElementsAscending)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    for(size_t counter = 0; counter < contents.size(); ++counter)
    {
        list->remove(0);
        contents.erase(contents.begin());
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;
}

TEST(ListRemove, ThreeElementsDescending)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    for(size_t counter = 0; counter < contents.size(); ++counter)
    {
        list->remove(0);
        contents.erase(contents.begin());
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;
}

TEST(ListRemove, ThreeElementsWraparoundAscending)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    for(size_t counter = 0; counter < contents.size(); ++counter)
    {
        list->remove(list->size());
        contents.erase(contents.begin());
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;
}

TEST(ListRemove, ThreeElementsWraparoundDescending)
{
    std::vector<int> contents{23, -29, 31};
    CircularListInt * list = makeCircularList(contents);

    for(int index = static_cast<int>(list->size() - 1); index >= 0; --index)
    {
        list->remove(list->size() + index);
        contents.erase(contents.begin() + index);
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;
}

TEST(ListRemove, 50ElementsAscending)
{
    const size_t numElements = 50;
    const RandomSeed origSeed = 18;

    std::vector<int> contents(makeRandomIntVector(numElements, origSeed, false));

    CircularListInt * list = makeCircularList(contents);

    for(int index = static_cast<int>(contents.size() - 1); index >= 0; --index)
    {
        list->remove(index);
        contents.erase(contents.begin() + index);
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;

}


TEST(ListRemove, 50ElementsDescending)
{
    const size_t numElements = 50;
    const RandomSeed origSeed = 5;

    std::vector<int> contents(makeRandomIntVector(numElements, origSeed, false));

    CircularListInt * list = makeCircularList(contents);

    for(size_t counter = 0; counter < contents.size(); ++counter)
    {
        list->remove(0);
        contents.erase(contents.begin());
        EXPECT_TRUE(checkListContent(list, contents));
    }

    delete list;

}

TEST(ListRemove, 50ElementBreakdownBuildup)
{
    const size_t numElements = 50;
    const size_t numTrials = 30;
    const RandomSeed contentsSeed = 999;
    const RandomSeed orderSeedSeed = 100001;

    std::vector<int> contents(makeRandomIntVector(numElements, contentsSeed, false));
    CircularListInt list;

    //keep adding and removing values to the same list
    for(RandomSeed orderSeed : makeRandomSeedVector(numTrials, orderSeedSeed))
    {
        // re-add contents to the list
        for(int item : contents)
        {
            list.push_back(item);
        }

        std::vector<int> currentContents(contents);

        // now, remove them in random order
        std::vector<RandomSeed> removeIndexSeeds = makeRandomSeedVector(numElements, orderSeed);
        for(size_t counter = 0; counter < numElements; ++counter)
        {
            size_t randomIndex = makeRandomNumber<size_t>(0, currentContents.size() - 1, orderSeed);
            list.remove(randomIndex);
            currentContents.erase(currentContents.begin() + randomIndex);

            EXPECT_TRUE(checkListContent(&list, currentContents));
        }

    }

}

TEST(ListRemove, 50ElementsDescWraparound)
{
    const size_t numElements = 50;
    const RandomSeed origSeed = 7;
    const size_t timesToWrap = 10;

    std::vector<int> contents(makeRandomIntVector(numElements, origSeed, false));

    CircularListInt * list = makeCircularList(contents);

    // loop around 4 times through the list
    size_t realIndex = contents.size() - 1;
    do
    {
        --realIndex;

        // wrap around randomly between 0 and 4 times
        size_t circularIndex = realIndex + contents.size() * makeRandomNumber<size_t>(0, timesToWrap, static_cast<RandomSeed>(origSeed + realIndex));

        list->remove(circularIndex);

        contents.erase(contents.begin() + realIndex);

        EXPECT_TRUE(checkListContent(list, contents));
    }
    while(realIndex > 0);

    delete list;
}