#include <gtest/gtest.h>
#include "User.h"

class TestUser : public User {
public:
    TestUser(int id, const std::string& username, const std::string& password, const std::string& role)
        : User(id, username, password, role) {}

    std::string getRole() const override {
        return role;
    }
};

TEST(UserTest, Getters) {
    TestUser user(1, "testuser", "password123", "admin");

    EXPECT_EQ(user.getId(), 1);
    EXPECT_EQ(user.getUsername(), "testuser");
    EXPECT_EQ(user.getPassword(), "password123");
    EXPECT_EQ(user.getRole(), "admin");
}
