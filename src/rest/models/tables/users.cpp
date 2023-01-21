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

    static const std::string SelectAllUsers = "SELECT ID, User, Password FROM Users";

    static const std::string UpdateUser = "UPDATE Users SET User = :User, Password = :Password WHERE ID = :ID";

    static const std::string DeleteUser = "DELETE FROM Users WHERE ID = :ID";

    static const std::string CountUsers = "SELECT COUNT(ID) FROM Users";

} // namespace querries

UsersTable::UsersTable(std::shared_ptr<soci::session> session)
    : session_{session}, delete_{*session_}, insert_{*session_}, update_{*session_}, select_{*session_}, selectAll_{*session_}, count_{*session_}
{
    try
    {
        soci::transaction transaction{*session_};
        *session_ << querries::CreateTable;
        transaction.commit();

        insert_.prepare(querries::InsertUser);
        update_.prepare(querries::UpdateUser);
        select_.prepare(querries::SelectUser);
        selectAll_.prepare(querries::SelectAllUsers);
        delete_.prepare(querries::DeleteUser);
        count_.prepare(querries::CountUsers);
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

void UsersTable::FindById(size_t id, User &user)
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

void UsersTable::FindAll(std::vector<User> &users)
{
    try
    {
        users.clear();

        const size_t count = Count();

        if (0 == count)
        {
            return;
        }

        std::vector<size_t> ids;
        std::vector<std::string> names;
        std::vector<std::string> passwords;

        ids.resize(count);
        names.resize(count);
        passwords.resize(count);

        selectAll_.exchange(soci::into(ids));
        selectAll_.exchange(soci::into(names));
        selectAll_.exchange(soci::into(passwords));

        selectAll_.define_and_bind();
        selectAll_.execute(true);
        selectAll_.bind_clean_up();

        users.resize(count);
        for (size_t i = 0; i < users.size(); ++i)
        {
            users[i].id = ids[i];
            users[i].name = std::move(names[i]);
            users[i].password = std::move(passwords[i]);
        }
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

size_t UsersTable::Count()
{
    try
    {
        size_t count = 0;
        count_.exchange(soci::into(count));

        count_.define_and_bind();
        count_.execute(true);
        count_.bind_clean_up();

        return count;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}
