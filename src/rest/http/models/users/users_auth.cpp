#include <http/models/users/users_auth.hpp>

#include <http/models/users/users.hpp>

#include <service/resources/messages.hpp>

#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Transaction.h>
#include <Poco/Data/Statement.h>

#include <stdexcept>
#include <iostream>

using namespace Poco::Data::Keywords;
using namespace Poco::Data;

/// @brief Запросы к MySQL базе данных
namespace querries
{
    static const std::string CreateTable = "CREATE TABLE IF NOT EXISTS Tokens (\n"
                                           "ID INT NOT NULL UNIQUE,\n"
                                           "Token VARCHAR(255) NOT NULL UNIQUE,\n"
                                           "FOREIGN KEY (ID) REFERENCES Users(ID),\n"
                                           "INDEX (Token)\n,"
                                           "INDEX (ID)\n"
                                           ") ENGINE=InnoDB CHARSET=utf8;";
    static const std::string InsertUser = "INSERT INTO Tokens(ID, Token) "
                                          "VALUES(?, ?)";
    static const std::string SelectUserById = "SELECT DISTINCT ID, Token "
                                              "FROM Tokens WHERE ID = ?";
    static const std::string SelectUserByCondition = "SELECT DISTINCT ID, Token "
                                                     "FROM Tokens WHERE Token = ?";
    static const std::string DeleteUser = "DELETE FROM Tokens WHERE ID = ?";
} // namespace querries

UsersAuthTable::UsersAuthTable(std::shared_ptr<Poco::Data::SessionPool> pool)
    : pool_{pool}
{
    try
    {
        Session sql = pool_->get();
        Transaction transaction{sql};
        sql << querries::CreateTable;
        transaction.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

bool UsersAuthTable::Insert(UserAuthRow &auth, std::string &error)
{
    try
    {
        if (!auth.Validate())
        {
            return false;
        }

        Session sql = pool_->get();
        Transaction transaction{sql};
        Statement statement{sql};

        statement << querries::InsertUser, use(auth.id), use(auth.token);

        const size_t res = statement.execute();

        if (res != 1)
        {
            error = messages::InsertionError;
            return false;
        }

        transaction.commit();

        return true;
    }
    catch (const std::exception &e)
    {
        error = e.what();
    }

    return false;
}

bool UsersAuthTable::FindById(size_t id, UserAuthRow &auth, std::string &error)
{
    try
    {
        Session sql = pool_->get();
        Statement statement{sql};
        statement << querries::SelectUserById, use(id),
            into(auth.id), into(auth.token);

        const size_t res = statement.execute();

        if (res != 1)
        {
            error = messages::NotFound;
            return false;
        }

        return true;
    }
    catch (const std::exception &e)
    {
        error = e.what();
    }

    return false;
}

bool UsersAuthTable::Delete(size_t id, std::string &error)
{
    try
    {
        Session sql = pool_->get();
        Transaction transaction{sql};
        Statement statement{sql};
        statement << querries::DeleteUser, use(id);

        const size_t res = statement.execute();

        if (res != 1)
        {
            error = messages::DeletionError;
            return false;
        }

        transaction.commit();

        return true;
    }
    catch (const std::exception &e)
    {
        error = e.what();
    }

    return false;
}

bool UsersAuthTable::FindByCondition(std::string &token, UserAuthRow &auth, std::string &error)
{
    try
    {
        Session sql = pool_->get();
        Statement statement{sql};
        statement << querries::SelectUserByCondition,
            use(token), into(auth.id), into(auth.token);

        const size_t res = statement.execute();

        if (res != 1)
        {
            error = messages::NotFound;
            return false;
        }

        return true;
    }
    catch (const std::exception &e)
    {
        error = e.what();
    }

    return false;
}

std::shared_ptr<Poco::Data::SessionPool> UsersAuthTable::GetPool()
{
    return pool_;
}
