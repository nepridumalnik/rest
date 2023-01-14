#include <http/request_handler.hpp>

#include <http/controllers/goods_controller.hpp>
#include <http/controllers/users_controller.hpp>

#include <Poco/Net/HTTPServerRequest.h>

RequestHandler::RequestHandler(std::shared_ptr<soci::session> sql)
    : sql_{sql}
{
    routing_.push_back({"/users", [this]() -> MethodHandler * { return new UsersController{sql_}; }});
    routing_.push_back({"/goods", [this]() -> MethodHandler * { return new GoodsController{sql_}; }});
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
