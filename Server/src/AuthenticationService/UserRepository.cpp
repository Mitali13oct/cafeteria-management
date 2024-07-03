
#include "UserRepository.h"

    std::string UserRepository::getUserRole(const std::string& username) {
    std::map<std::string, std::string> filter = {
        {"username", username}
    };
    sql::ResultSet* res = dbRepo.selectOne("Users", filter);
    std::string role;
    if (res->next()) {
        role = res->getString("role");
    }
    delete res;
    return role;
}

    void UserRepository::saveUser(const User& user) {
        std::map<std::string, std::string> data = {
            {"username", user.getUsername()},
            {"password", user.getPassword()},
            {"role", user.getRole()}
        };
        dbRepo.insert("Users", data);
    }

    bool UserRepository::authenticateUser(const std::string& username, const std::string& password) {
        std::map<std::string, std::string> filter = {
            {"username", username},
            {"password", password}
        };
        sql::ResultSet* res = dbRepo.selectOne("Users", filter);
        bool authenticated = res->next();
        delete res;
        return authenticated;
    }

    User* UserRepository::getUserByUsername(const std::string& username) {
        std::map<std::string, std::string> filter = {{"username", username}};
        sql::ResultSet* res = dbRepo.selectOne("Users", filter);

        if (res->next()) {
            int id = res->getInt("id");
            std::string user_username = res->getString("username");
            std::string password = res->getString("password");
            std::string role = res->getString("role");
    
            User* user = nullptr;
            if (role == "Admin") {
                user = new Admin(id, user_username, password);
            } else if (role == "Chef") {
                user = new Chef(id, user_username, password);
            } else if (role == "Employee") {
                user = new Employee(id, user_username, password);
            } else {
                delete res;
            }

            delete res;
            return user;
        } else {
            delete res;
            throw std::runtime_error("User not found");
        }
    }


