#include <gtest/gtest.h>
#include <memory>

#include "SharedPointer.hpp"

namespace {

class SharedPointerTestSmpl : public ::testing::Test {
protected:
    void SetUp() override {
        sharedPointerVector1.push_back(pp::SharedPointer<std::string>("first"));
        sharedPointerVector1.push_back(pp::SharedPointer<std::string>("second"));
        sharedPointerVector1.push_back(pp::SharedPointer<std::string>("third"));
    }

    void TearDown() override {

    }

    pp::SharedPointer<std::string> stringPointer1;
    pp::SharedPointer<std::string> stringPointer2 = pp::SharedPointer<std::string>("string");

    pp::SharedPointer<int> intPointer1;

    std::vector<pp::SharedPointer<std::string>> sharedPointerVector1;
};

TEST_F(SharedPointerTestSmpl, DefaultConstuctor) {
    EXPECT_STREQ("", stringPointer1->c_str());
    EXPECT_EQ(1, stringPointer1.getReferenceCount());

    EXPECT_EQ(0, *intPointer1);
    EXPECT_EQ(1, intPointer1.getReferenceCount());
}

TEST_F(SharedPointerTestSmpl, CopyConsturctor) {
    pp::SharedPointer<std::string> copy = stringPointer2;

    EXPECT_STREQ(copy->c_str(), stringPointer2->c_str());
    EXPECT_EQ(2, stringPointer2.getReferenceCount());
    EXPECT_EQ(2, copy.getReferenceCount());
}

TEST_F(SharedPointerTestSmpl, CopyAssignment) {
    pp::SharedPointer<std::string> copy;
    copy = stringPointer2;

    EXPECT_STREQ(copy->c_str(), stringPointer2->c_str());
    EXPECT_EQ(2, stringPointer2.getReferenceCount());
    EXPECT_EQ(2, copy.getReferenceCount());

    copy = copy;
    EXPECT_STREQ(copy->c_str(), stringPointer2->c_str());
    EXPECT_EQ(2, stringPointer2.getReferenceCount());
    EXPECT_EQ(2, copy.getReferenceCount());
}

TEST_F(SharedPointerTestSmpl, Vector) {
    std::vector<pp::SharedPointer<std::string>> vector2 = sharedPointerVector1;

    EXPECT_STREQ("first", vector2[0]->c_str());
    EXPECT_STREQ("second", vector2[1]->c_str());
    EXPECT_STREQ("third", vector2[2]->c_str());

    for (size_t i = 0; i < vector2.size(); ++i) {
        EXPECT_EQ(2, vector2[i].getReferenceCount());
        EXPECT_EQ(2, sharedPointerVector1[i].getReferenceCount());
    }

    vector2.clear();
    for (auto &element : sharedPointerVector1)
        EXPECT_EQ(1, element.getReferenceCount());
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}
