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
{
    try
    {
        soci::transaction transaction{*session_};
        *session_ << querries::CreateTable;
        transaction.commit();
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
        *session_ << querries::InsertUser, soci::use(user.name), soci::use(user.password);
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
        *session_ << querries::UpdateUser, soci::use(user.name), soci::use(user.password), soci::use(id);
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
        *session_ << querries::SelectUser, soci::use(id), soci::into(user.name), soci::into(user.password);
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
        *session_ << querries::DeleteUser, soci::use(id);
        transaction.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}
