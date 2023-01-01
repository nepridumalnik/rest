#include <rest_server.hpp>

#include <request_handler.hpp>

RestServer::RestServer()
{
    requestHandler_ = Poco::makeShared<RequestHandler>();

    server_ = Poco::makeShared<Poco::Net::HTTPServer>(requestHandler_);
}

void RestServer::Start()
{
    server_->start();
}

void RestServer::WaitForTerminationRequest()
{
    waitForTerminationRequest();
}
