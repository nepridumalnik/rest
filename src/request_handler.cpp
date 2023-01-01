#include <request_handler.hpp>

#include <http/simple_rest.hpp>

#include <Poco/Net/HTTPServerRequest.h>

Poco::Net::HTTPRequestHandler *RequestHandler::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    std::cout << request.getURI() << std::endl;
    return new SimpleRest;
}
