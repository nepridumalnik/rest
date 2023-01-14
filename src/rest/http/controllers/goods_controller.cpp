#include <http/controllers/goods_controller.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <nlohmann/json.hpp>

#include <iostream>

namespace net = Poco::Net;

namespace
{

static const std::string AccessControlHeaderName = "Access-Control-Allow-Origin";

static const std::string AccessControlHeaderValue = "*";

} // namespace

GoodsController::GoodsController(std::shared_ptr<soci::session> sql)
    : goods_{std::make_shared<GoodsTable>(sql)}
{
}

void GoodsController::Get(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
    response.sendBuffer(nullptr, 0);
}

void GoodsController::Post(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
    response.sendBuffer(nullptr, 0);
}
