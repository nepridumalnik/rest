#include <http/request_handler.hpp>

#include <http/controllers/user_get.hpp>
#include <http/controllers/user_login.hpp>
#include <http/controllers/user_register.hpp>
#include <http/controllers/user_search.hpp>

#include <models/users/users.hpp>
#include <models/users/users_auth.hpp>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Data/SessionPool.h>

RequestHandler::RequestHandler(std::shared_ptr<Poco::Data::SessionPool> pool)
    : pool_{pool}
{
    usersTable_ = std::make_shared<UsersTable>(pool_);
    authTable_ = std::make_shared<UsersAuthTable>(pool_);

    routing_.push_back({"/user/get", [&usersTable = usersTable_, this]()
                        { return new UserGetController{usersTable}; }});

    routing_.push_back({"/login", [&usersTable = usersTable_, &authTable = authTable_, this]()
                        { return new UserLoginController{usersTable, authTable}; }});

    routing_.push_back({"/user/register", [&usersTable = usersTable_, this]()
                        { return new UserRegisterController{usersTable}; }});

    routing_.push_back({"/user/search", [&usersTable = usersTable_, this]()
                        { return new UserSearchController{usersTable}; }});
}

Poco::Net::HTTPRequestHandler *RequestHandler::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    const std::string requestedUri = request.getURI();

    for (const auto &it : routing_)
    {
        if (0 == requestedUri.find(it.first))
        {
            return it.second();
        }
    }

    return nullptr;
}
