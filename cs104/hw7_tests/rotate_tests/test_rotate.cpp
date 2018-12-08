#include "publicified_rotatebst.h"
#include <check_bst.h>
#include <create_bst.h>

#include <gtest/gtest.h>

#include <initializer_list>
#include <utility>


// rotation tests author credit: Jillian Khoo
template<typename Key, typename Value>
class InheritedRotate;

using StressTreeType = InheritedRotate<std::mt19937::result_type, int>;

template<typename Key, typename Value>
class InheritedRotate : public rotateBST<Key, Value>
{
public:
	void leftRotateRoot() { this->leftRotate(this->mRoot); }
	void rightRotateRoot() { this->rightRotate(this->mRoot); }
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

class Rotate : public testing::Test
{
protected:
	void redirectOutput(std::ostream& output,
		void (*f)(const StressTreeType&),
		const StressTreeType& t);
};


void Rotate::redirectOutput(std::ostream& output,
	void (*f)(const StressTreeType&),
	const StressTreeType& t)
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::cout.rdbuf(output.rdbuf());
	(*f)(t);
	std::cout.rdbuf(oldCout);
}


TEST_F(Rotate, Test1_BiggerLeftRootRotate)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.leftRotateRoot();

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(30, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight());
	EXPECT_EQ(35, bst.getRoot()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft());
	EXPECT_EQ(20, bst.getRoot()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getLeft());
	EXPECT_EQ(10, bst.getRoot()->getLeft()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getRight());
	EXPECT_EQ(25, bst.getRoot()->getLeft()->getRight()->getKey());

}

TEST_F(Rotate, Test2_BiggerRightRootRotate)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.rightRotateRoot();

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(10, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight());
	EXPECT_EQ(20, bst.getRoot()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft());
	EXPECT_EQ(5, bst.getRoot()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getRight());
	EXPECT_EQ(30, bst.getRoot()->getRight()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getLeft());
	EXPECT_EQ(15, bst.getRoot()->getRight()->getLeft()->getKey());

}

TEST_F(Rotate, Test3_RightNonRootRotateRightChild)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.rightRotate(bst.getRoot()->getRight());

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight());
	EXPECT_EQ(25, bst.getRoot()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getRight());
	EXPECT_EQ(30, bst.getRoot()->getRight()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getRight()->getRight());
	EXPECT_EQ(35, bst.getRoot()->getRight()->getRight()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getRight()->getLeft());
	EXPECT_EQ(27, bst.getRoot()->getRight()->getRight()->getLeft()->getKey());

	EXPECT_EQ(nullptr, bst.getRoot()->getRight()->getLeft());
}

TEST_F(Rotate, Test4_LeftNonRootRotateLeftChild)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.leftRotate(bst.getRoot()->getLeft());

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft());
	EXPECT_EQ(15, bst.getRoot()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getLeft());
	EXPECT_EQ(10, bst.getRoot()->getLeft()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getLeft()->getLeft());
	EXPECT_EQ(5, bst.getRoot()->getLeft()->getLeft()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getLeft()->getRight());
	EXPECT_EQ(12, bst.getRoot()->getLeft()->getLeft()->getRight()->getKey());

	EXPECT_EQ(nullptr, bst.getRoot()->getLeft()->getRight());

}

TEST_F(Rotate, Test5_RightRotateNoLeftChildRightChild)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.rightRotate(bst.getRoot()->getLeft());

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft());
	EXPECT_EQ(5, bst.getRoot()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getRight());
	EXPECT_EQ(10, bst.getRoot()->getLeft()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft()->getRight()->getRight());
	EXPECT_EQ(15, bst.getRoot()->getLeft()->getRight()->getRight()->getKey());
	EXPECT_EQ(nullptr, bst.getRoot()->getLeft()->getLeft());
	EXPECT_EQ(nullptr, bst.getRoot()->getLeft()->getRight()->getLeft());

}
TEST_F(Rotate, Test6_LeftRotateNoRightChildLeftChild)
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(30, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.insert(std::make_pair(35, 1.0));
	bst.insert(std::make_pair(27, 1.0));
	bst.insert(std::make_pair(12, 1.0));
	bst.leftRotate(bst.getRoot()->getRight());

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight());
	EXPECT_EQ(35, bst.getRoot()->getRight()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getLeft());
	EXPECT_EQ(30, bst.getRoot()->getRight()->getLeft()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight()->getLeft()->getLeft());
	EXPECT_EQ(25, bst.getRoot()->getRight()->getLeft()->getLeft()->getKey());
	EXPECT_EQ(nullptr, bst.getRoot()->getRight()->getRight());
	EXPECT_EQ(nullptr, bst.getRoot()->getRight()->getLeft()->getRight());

}

TEST_F(Rotate, Test7_LeftDontRotate){
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(15, 1.0));
	bst.leftRotateRoot();

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getLeft());
	EXPECT_EQ(15, bst.getRoot()->getLeft()->getKey());
	EXPECT_EQ(nullptr, bst.getRoot()->getRight());

}

TEST_F(Rotate, Test8_RightDontRotate){
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(20, 1.0));
	bst.insert(std::make_pair(25, 1.0));
	bst.rightRotateRoot();

	EXPECT_TRUE(verifyBST(bst));

	ASSERT_NE(nullptr, bst.getRoot());
	EXPECT_EQ(20, bst.getRoot()->getKey());
	ASSERT_NE(nullptr, bst.getRoot()->getRight());
	EXPECT_EQ(25, bst.getRoot()->getRight()->getKey());
	EXPECT_EQ(nullptr, bst.getRoot()->getLeft());
}

