#include <http/method_handler.hpp>

#include <models/tables/users.hpp>

#include <soci/session.h>

#include <memory>

class UsersController : public MethodHandler
{
public:
    explicit UsersController(std::shared_ptr<soci::session> sql);

    void Get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    void Post(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    std::shared_ptr<UsersTable> users_;
};
