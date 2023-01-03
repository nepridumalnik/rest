#pragma once

#include <models/tables/crud_interface.hpp>

#include <soci/session.h>
#include <soci/statement.h>

#include <memory>

struct User
{
    size_t id;
    std::string name;
    std::string password;
};

class UsersTable : public ICrud<User>
{
public:
    explicit UsersTable(std::shared_ptr<soci::session> session);

    void Insert(const User &user) override;
    void Update(size_t id, const User &user) override;
    void FindById(size_t id, User &user) override;
    void FindAll(std::vector<User> &users) override;
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
