#pragma once

#include <models/tables/users.hpp>

#include <helpers/macro.hpp>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>

#include <soci/session.h>

#include <memory>

class RestServer : public Poco::Util::ServerApplication
{
public:
    EXPORT RestServer(std::shared_ptr<soci::session> sql = nullptr);
    void EXPORT Start();
    void EXPORT WaitForTerminationRequest();

private:
    Poco::SharedPtr<Poco::Net::HTTPServer> server_;
    Poco::Net::HTTPRequestHandlerFactory::Ptr requestHandler_;

    std::shared_ptr<soci::session> sql_;
    std::shared_ptr<UsersTable> users_;
};
