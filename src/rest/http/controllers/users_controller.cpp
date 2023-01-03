#include <http/controllers/users_controller.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <iostream>
#include <sstream>

namespace net = Poco::Net;

UsersController::UsersController(std::shared_ptr<soci::session> sql)
    : users_{std::make_shared<UsersTable>(sql)}
{
}

void UsersController::Get(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    std::cout << "Get" << std::endl;

    const std::string ss = "<h1>Hello, rest</h1>";
    response.sendBuffer(ss.c_str(), ss.size());
}

void UsersController::Post(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    std::cout << "Post" << std::endl;

    net::HTMLForm form{request, request.stream()};

    for (const auto &parameter : form)
    {
        std::cout << "it->first: " << parameter.first << std::endl;
        std::cout << "it->second: " << parameter.second << std::endl;
    }

    response.sendBuffer(nullptr, 0);
}
