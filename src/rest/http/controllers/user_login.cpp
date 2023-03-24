#include <http/controllers/user_login.hpp>

#include <nlohmann/json.hpp>

#include <http/models/users/users.hpp>
#include <http/models/users/users_auth.hpp>

UserLoginController::UserLoginController(std::shared_ptr<UsersTable> usersTable,
                                         std::shared_ptr<UsersAuthTable> authTable)
    : usersTable_{usersTable},
      authTable_{authTable}
{
}

void UserLoginController::handleRequest(Poco::Net::HTTPServerRequest &req,
                                        Poco::Net::HTTPServerResponse &res)
{
}

void UserLoginController::login(Poco::Net::HTTPServerRequest &req,
                                Poco::Net::HTTPServerResponse &res)
{
}

void UserLoginController::unauthorize(Poco::Net::HTTPServerRequest &req,
                                      Poco::Net::HTTPServerResponse &res)
{
}

void UserLoginController::authenticate(Poco::Net::HTTPServerRequest &req,
                                       Poco::Net::HTTPServerResponse &res)
{
}
