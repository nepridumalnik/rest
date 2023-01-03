#include <http/request_handler.hpp>

#include <http/controllers/users_controller.hpp>

#include <Poco/Net/HTTPServerRequest.h>

#include <iostream>

RequestHandler::RequestHandler(std::shared_ptr<soci::session> sql)
    : sql_{sql}
{
}

Poco::Net::HTTPRequestHandler *RequestHandler::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    const std::string requestedUri = request.getURI();

    if ("/users" == requestedUri)
    {
        return new UsersController{sql_};
    }

    return nullptr;
}
