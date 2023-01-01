#pragma once

#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>

class RestServer : public Poco::Util::ServerApplication
{
public:
    RestServer();
    void Start();
    void WaitForTerminationRequest();

private:
    Poco::SharedPtr<Poco::Net::HTTPServer> server_;

    Poco::Net::HTTPRequestHandlerFactory::Ptr requestHandler_;
};
