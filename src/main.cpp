#include <rest_server.hpp>

#include <Poco/Util/ServerApplication.h>

int main(int argc, char const *argv[])
{
    RestServer server;
    server.Start();

    server.WaitForTerminationRequest();

    return 0;
}
