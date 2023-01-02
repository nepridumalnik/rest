#include <http/method_handler.hpp>

class SimpleRest : public MethodHandler
{
public:
    void Get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    void Post(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
};
