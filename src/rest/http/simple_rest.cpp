#include <http/simple_rest.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <iostream>
#include <sstream>

namespace net = Poco::Net;

void SimpleRest::Get(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    std::cout << "Get" << std::endl;

    const std::string ss = "<head><link rel=\"shortcut icon\" href=\"/favicon.ico\"></head>";
    response.sendBuffer(ss.c_str(), ss.size());
}

void SimpleRest::Post(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    std::cout << "Post" << std::endl;

    net::HTMLForm form{request, request.stream()};
    auto it = form.begin();

    for (; it != form.end(); ++it)
    {
        std::cout << "it->first: " << it->first << std::endl;
        std::cout << "it->second: " << it->second << std::endl;
    }

    response.sendBuffer(nullptr, 0);
}
