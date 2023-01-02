#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class HTTPServerRequest;

class RequestHandler : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request);
};
