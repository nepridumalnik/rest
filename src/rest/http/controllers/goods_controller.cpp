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
    std::cout << "Get " << request.getURI() << std::endl;
    const std::string requestUri = request.getURI();

    const auto delimiter = requestUri.rfind('/');

    if (0 != delimiter && std::string::npos != delimiter)
    {
        const auto id = std::stoul(&requestUri[delimiter + 1]);

        Good good;
        goods_->FindById(id, good);

        nlohmann::json object;

        object["id"] = good.id;
        object["name"] = good.name;
        object["price"] = good.price;
        object["description"] = good.description;
        object["tag"] = good.tag;
        object["quantity"] = good.quantity;

        const std::string serializedUser = object.dump();
        response.sendBuffer(serializedUser.c_str(), serializedUser.size());
    }
    else
    {
        std::vector<Good> goods;
        goods_->FindAll(goods);

        nlohmann::json array = nlohmann::json::array();

        for (const auto &good : goods)
        {
            nlohmann::json object;

            object["id"] = good.id;
            object["name"] = good.name;
            object["price"] = good.price;
            object["description"] = good.description;
            object["tag"] = good.tag;
            object["quantity"] = good.quantity;

            array.push_back(object);
        }

        const std::string usersArray = array.dump();

        response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
        response.sendBuffer(usersArray.c_str(), usersArray.size());
    }
}

void GoodsController::Post(net::HTTPServerRequest &request, net::HTTPServerResponse &response)
{
    response.set(::AccessControlHeaderName, ::AccessControlHeaderValue);
    response.sendBuffer(nullptr, 0);
}
