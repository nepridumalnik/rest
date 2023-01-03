#pragma once

#include <http/method_handler.hpp>

#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include <soci/session.h>

#include <functional>
#include <memory>
#include <vector>

class RequestHandler : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    explicit RequestHandler(std::shared_ptr<soci::session> sql);

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

private:
    std::shared_ptr<soci::session> sql_;
    std::vector<std::pair<std::string, std::function<MethodHandler *()>>> routing_;
};
