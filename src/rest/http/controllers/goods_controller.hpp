#pragma once

#include <http/method_handler.hpp>

#include <models/tables/goods.hpp>

#include <soci/session.h>

#include <memory>

class GoodsController : public MethodHandler
{
public:
    explicit GoodsController(std::shared_ptr<soci::session> sql);

    void Get(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    void Post(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    std::shared_ptr<GoodsTable> goods_;
};
