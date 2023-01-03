#include <rest_server.hpp>

#include <http/request_handler.hpp>

#include <soci/sqlite3/soci-sqlite3.h>

namespace
{

static const std::string DefaultDB = "default_base.db";

} // namespace

RestServer::RestServer(std::shared_ptr<soci::session> sql)
{
    if (!sql)
    {
        sql_ = std::make_shared<soci::session>(soci::sqlite3, ::DefaultDB);
    }

    requestHandler_ = Poco::makeShared<RequestHandler>(sql_);
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
