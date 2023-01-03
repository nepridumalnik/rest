#include <http/request_handler.hpp>

#include <http/controllers/users_controller.hpp>

#include <Poco/Net/HTTPServerRequest.h>

RequestHandler::RequestHandler(std::shared_ptr<soci::session> sql)
    : sql_{sql}
{
    routing_["/users"] = [this]() -> MethodHandler * { return new UsersController{sql_}; };
}

Poco::Net::HTTPRequestHandler *RequestHandler::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    const std::string requestedUri = request.getURI();

    const auto it = routing_.find(requestedUri);

    if (routing_.end() != it)
    {
        return it->second();
    }

    return nullptr;
}
