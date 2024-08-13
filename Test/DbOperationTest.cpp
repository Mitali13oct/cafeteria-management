#include <gtest/gtest.h>
#include "DbOperation.h"

TEST(DatabaseRepositoryTest, InsertTest) {
    DatabaseRepository dbRepo("RecommendationEngine", "mitalijain", "Mishu@777");
    std::map<std::string, std::string> data = {{"username", "testuser"}, {"password", "password123"}};

    EXPECT_NO_THROW(dbRepo.insert("Users", data));
}

TEST(DatabaseRepositoryTest, SelectOneTest) {
    DatabaseRepository dbRepo("RecommendationEngine", "mitalijain", "Mishu@777");
    std::map<std::string, std::string> filter = {{"username", "testuser"}};

    sql::ResultSet *resultSet = dbRepo.selectOne("Users", filter);
    ASSERT_NE(resultSet, nullptr);
    EXPECT_TRUE(resultSet->next());
    EXPECT_EQ(resultSet->getString("username"), "testuser");
    
    delete resultSet;
}
