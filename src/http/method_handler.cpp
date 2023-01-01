#include <http/method_handler.hpp>

#include <Poco/Net/HTTPServerRequest.h>

#include <functional>
#include <string>
#include <unordered_map>

namespace net = Poco::Net;

namespace
{

using MethodPtr = void (MethodHandler::*)(net::HTTPServerRequest &, net::HTTPServerResponse &);

static const std::string Post = "POST";
static const std::string Get = "GET";

static const std::unordered_map<std::string, MethodPtr> MethodMapping{
    {Post, &MethodHandler::Post},
    {Get, &MethodHandler::Get},
};

} // namespace

void MethodHandler::handleRequest(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    const auto method = ::MethodMapping.find(request.getMethod());

    if (::MethodMapping.end() != method)
    {
        // Колдунство
        (this->*(method->second))(request, response);
    }
    else
    {
        throw std::runtime_error{"Unknown HTTP method"};
    }
}
