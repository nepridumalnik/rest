#include <request_handler.hpp>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <Poco/StreamCopier.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <sstream>
#include <vector>

using json = nlohmann::json;

struct FormData
{
    std::string name;
    std::string password;
};

class Handler : public Poco::Net::HTTPRequestHandler
{
public:
    Handler()
    {
        data_.push_back({"name", "password"});
    }

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override
    {
        std::cout << request.getMethod() << std::endl;
        std::cout << "clientAddress: " << request.clientAddress() << std::endl;
        std::cout << "serverAddress: " << request.serverAddress() << std::endl;

        const std::string method = request.getMethod();

        if ("GET" == method)
        {
            get(request, response);
        }
        else if ("POST" == method)
        {
            post(request, response);
        }
    }

    void get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
    {
        json respondObject;

        size_t count = 0;
        for (const auto &d : data_)
        {
            json object;
            object["id"] = count++;
            object["name"] = d.name;
            object["password"] = d.password;

            respondObject.push_back(object);
        }

        const std::string buffer = respondObject.dump();
        response.sendBuffer(buffer.c_str(), buffer.size());
    }

    void post(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
    {
        std::string data;
        Poco::StreamCopier::copyToString(request.stream(), data);
        std::stringstream ss{data};

        while (std::getline(ss, data, '&'))
        {
            // std::stringstream arg{data};
            // std::string name = getArg(arg).second;
            // std::string password = getArg(arg).second;

            // data_.push_back({name, password});
        }
    }

    std::pair<std::string, std::string> getArg(std::stringstream &ss)
    {
        std::pair<std::string, std::string> result;

        std::string data;
        std::stringstream arg{data};

        std::getline(ss, result.first, '=');
        std::getline(ss, result.second);

        return result;
    }

private:
    std::vector<FormData> data_;
};

Poco::Net::HTTPRequestHandler *RequestHandler::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    std::cout << request.getURI() << std::endl;
    return new Handler;
}
