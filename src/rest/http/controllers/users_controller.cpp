#include <http/controllers/users_controller.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <sstream>

namespace net = Poco::Net;

namespace
{

static const std::string AccessControlHeaderName = "Access-Control-Allow-Origin";

static const std::string AccessControlHeaderValue = "*";

} // namespace

UsersController::UsersController(std::shared_ptr<soci::session> sql)
    : users_{std::make_shared<UsersTable>(sql)}
{
}

void UsersController::Get(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    std::cout << "Get " << request.getURI() << std::endl;
    const std::string requestUri = request.getURI();

    const auto delimiter = requestUri.rfind('/');

    if (0 != delimiter && std::string::npos != delimiter)
    {
        const auto id = std::stoul(&requestUri[delimiter + 1]);

        User user;
        users_->FindById(id, user);

        nlohmann::json object;

        object["id"] = id;
        object["name"] = user.name;
        object["password"] = user.password;

        const std::string serializedUser = object.dump();
        response.sendBuffer(serializedUser.c_str(), serializedUser.size());
    }
    else
    {
        std::vector<User> users;
        users_->FindAll(users);

        nlohmann::json object = nlohmann::json::array();

        for (const auto &user : users)
        {
            nlohmann::json u;

            u["id"] = user.id;
            u["name"] = user.name;
            u["password"] = user.password;

            object.push_back(u);
        }

        const std::string usersArray = object.dump();

        response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
        response.sendBuffer(usersArray.c_str(), usersArray.size());
    }
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

    response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
    response.sendBuffer(nullptr, 0);
}
