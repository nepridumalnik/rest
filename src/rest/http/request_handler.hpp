#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include <soci/session.h>

#include <functional>
#include <memory>
#include <unordered_map>

class RequestHandler : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    explicit RequestHandler(std::shared_ptr<soci::session> sql);

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

private:
    std::shared_ptr<soci::session> sql_;
};
