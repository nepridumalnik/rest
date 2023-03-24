#include <http/controllers/user_register.hpp>

#include <models/users/users.hpp>

#include <nlohmann/json.hpp>

UserRegisterController::UserRegisterController(std::shared_ptr<UsersTable> usersTable)
    : usersTable_{usersTable}
{
}

void UserRegisterController::handleRequest(Poco::Net::HTTPServerRequest &req,
                                           Poco::Net::HTTPServerResponse &res)
{
}
