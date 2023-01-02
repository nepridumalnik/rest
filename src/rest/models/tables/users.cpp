#include <models/tables/users.hpp>

#include <soci/transaction.h>

#include <iostream>

namespace querries
{

static const std::string CreateTable = "CREATE TABLE IF NOT EXISTS Users (\n"
                                       "ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                       "User VARCHAR(50) NOT NULL,\n"
                                       "Password VARCHAR(50) NOT NULL\n"
                                       ")";

static const std::string InsertUser = "INSERT INTO Users(User, Password) VALUES(:User, :Password)";

static const std::string SelectUser = "SELECT User, Password FROM Users WHERE ID = :ID";

static const std::string UpdateUser = "UPDATE Users SET User = :User, Password = :Password WHERE ID = :ID";

static const std::string DeleteUser = "DELETE FROM Users WHERE ID = :ID";

} // namespace querries

UsersTable::UsersTable(std::shared_ptr<soci::session> session)
    : session_{session}
    , delete_{*session_}
    , insert_{*session_}
    , update_{*session_}
    , select_{*session_}
{
    try
    {
        soci::transaction transaction{*session_};
        *session_ << querries::CreateTable;
        transaction.commit();

        insert_.prepare(querries::InsertUser);
        update_.prepare(querries::UpdateUser);
        select_.prepare(querries::SelectUser);
        delete_.prepare(querries::DeleteUser);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void UsersTable::Insert(const User &user)
{
    try
    {
        soci::transaction transaction{*session_};

        insert_.exchange(soci::use(user.name));
        insert_.exchange(soci::use(user.password));

        insert_.define_and_bind();
        insert_.execute(true);
        insert_.bind_clean_up();

        transaction.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void UsersTable::Update(size_t id, const User &user)
{
    try
    {
        soci::transaction transaction{*session_};

        update_.exchange(soci::use(user.name));
        update_.exchange(soci::use(user.password));
        update_.exchange(soci::use(id));

        update_.define_and_bind();
        update_.execute(true);
        update_.bind_clean_up();

        transaction.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void UsersTable::Select(size_t id, User &user)
{
    try
    {
        select_.exchange(soci::use(id));
        select_.exchange(soci::into(user.name));
        select_.exchange(soci::into(user.password));

        select_.define_and_bind();
        select_.execute(true);
        select_.bind_clean_up();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void UsersTable::Delete(size_t id)
{
    try
    {
        soci::transaction transaction{*session_};

        delete_.exchange(soci::use(id));

        delete_.define_and_bind();
        delete_.execute(true);
        delete_.bind_clean_up();

        transaction.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}
