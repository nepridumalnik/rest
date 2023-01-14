#pragma once

#include <models/tables/crud_interface.hpp>

#include <soci/session.h>
#include <soci/statement.h>

#include <memory>

struct Good
{
    size_t id;
    std::string name;
    double price;
    std::string description;
    std::string tag;
    size_t quantity;
};

class GoodsTable : public ICrud<Good>
{
public:
    explicit GoodsTable(std::shared_ptr<soci::session> session);

    void Insert(const Good &good) override;
    void Update(size_t id, const Good &good) override;
    void FindById(size_t id, Good &good) override;
    void FindAll(std::vector<Good> &users) override;
    void Delete(size_t id) override;
    size_t Count() override;

private:
    std::shared_ptr<soci::session> session_;

    soci::statement delete_;
    soci::statement insert_;
    soci::statement update_;
    soci::statement select_;
    soci::statement selectAll_;
    soci::statement count_;
};
