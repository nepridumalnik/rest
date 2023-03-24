#include <http/controllers/user_get.hpp>

#include <http/models/users/users.hpp>

#include <nlohmann/json.hpp>

UserGetController::UserGetController(std::shared_ptr<UsersTable> usersTable)
    : usersTable_{usersTable}
{
}

void UserGetController::handleRequest(Poco::Net::HTTPServerRequest &req,
                                      Poco::Net::HTTPServerResponse &res)
{
}

void UserGetController::getUserById(const size_t id,
                                    Poco::Net::HTTPServerRequest &req,
                                    Poco::Net::HTTPServerResponse &res)
{
}
