#include <Poco/Net/HTTPRequestHandler.h>

struct MethodHandler : public Poco::Net::HTTPRequestHandler
{
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

    virtual void Get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) = 0;
    virtual void Post(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) = 0;

    virtual ~MethodHandler() = default;
};
