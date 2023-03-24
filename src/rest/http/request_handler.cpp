#include <http/request_handler.hpp>

#include <http/controllers/user_get.hpp>

#include <http/models/users/users.hpp>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Data/SessionPool.h>

RequestHandler::RequestHandler(std::shared_ptr<Poco::Data::SessionPool> pool)
    : pool_{pool}
{
    usersTable_ = std::make_shared<UsersTable>(pool_);

    routing_.push_back({"/user/get", [&usersTable = usersTable_, this]()
                        { return new UserGetController{usersTable}; }});
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
