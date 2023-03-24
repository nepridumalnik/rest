#include <http/controllers/user_search.hpp>

#include <http/models/users/users.hpp>

#include <nlohmann/json.hpp>

UserSearchController::UserSearchController(std::shared_ptr<UsersTable> usersTable)
    : usersTable_{usersTable}
{
}

void UserSearchController::handleRequest(Poco::Net::HTTPServerRequest &req,
                                         Poco::Net::HTTPServerResponse &res)
{
}

void UserSearchController::searchUsers(Poco::Net::HTTPServerRequest &req,
                                       Poco::Net::HTTPServerResponse &res)
{
}
