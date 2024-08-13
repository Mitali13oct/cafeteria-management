#include <gtest/gtest.h>
#include "UserRepository.h"
#include "User.h"

class TestUser : public User {
public:
    TestUser(int id, const std::string& username, const std::string& password, const std::string& role)
        : User(id, username, password, role) {}

    std::string getRole() const override {
        return role;
    }
};

TEST(UserRepositoryTest, SaveUserTest) {
    UserRepository userRepo;
    TestUser user(1, "testuser", "password123", "admin");

    EXPECT_NO_THROW(userRepo.saveUser(user));
}

TEST(UserRepositoryTest, AuthenticateUserTest) {
    UserRepository userRepo;
    bool isAuthenticated = userRepo.authenticateUser("testuser", "password123");
    EXPECT_TRUE(isAuthenticated);

    isAuthenticated = userRepo.authenticateUser("testuser", "wrongpassword");
    EXPECT_FALSE(isAuthenticated);
}

TEST(UserRepositoryTest, GetUserRoleTest) {
    UserRepository userRepo;

    std::string role = userRepo.getUserRole("testuser");
    EXPECT_EQ(role, "admin");
}
