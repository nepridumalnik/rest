#include <models/tables/goods.hpp>

#include <soci/transaction.h>

#include <iostream>

namespace querries
{

    static const std::string CreateTable = "CREATE TABLE IF NOT EXISTS Goods (\n"
                                           "ID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                           "Name VARCHAR(50) NOT NULL,\n"
                                           "Price INTEGER NOT NULL,\n"
                                           "Description VARCHAR(500),\n"
                                           "Tag VARCHAR(500),\n"
                                           "Quantity INTEGER NOT NULL"
                                           ")";

    static const std::string InsertGood = "INSERT INTO Goods(Name, Price, Description, Tag, Quantity) "
                                          "VALUES(:Name, :Price, :Description, :Tag, :Quantity)";

    static const std::string SelectGood = "SELECT Name, Price, Description, Tag, Quantity "
                                          "FROM Goods WHERE ID = :ID";

    static const std::string SelectAllGoods = "SELECT ID, Name, Price, Description, Tag, Quantity FROM Goods";

    static const std::string UpdateGood = "UPDATE Goods SET Name = :Name, Price = :Price, "
                                          "Description = :Description, Tag = :Tag, Quantity = :Quantity "
                                          "WHERE ID = :ID";

    static const std::string DeleteGood = "DELETE FROM Goods WHERE ID = :ID";

    static const std::string CountGood = "SELECT COUNT(ID) FROM Goods";

} // namespace querries

GoodsTable::GoodsTable(std::shared_ptr<soci::session> session)
    : session_{session}, delete_{*session_}, insert_{*session_}, update_{*session_}, select_{*session_}, selectAll_{*session_}, count_{*session_}
{
    try
    {
        soci::transaction transaction{*session_};
        *session_ << querries::CreateTable;
        transaction.commit();

        insert_.prepare(querries::InsertGood);
        update_.prepare(querries::UpdateGood);
        select_.prepare(querries::SelectGood);
        selectAll_.prepare(querries::SelectAllGoods);
        delete_.prepare(querries::DeleteGood);
        count_.prepare(querries::CountGood);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void GoodsTable::Insert(const Good &good)
{
    try
    {
        soci::transaction transaction{*session_};

        insert_.exchange(soci::use(good.name));
        insert_.exchange(soci::use(good.price));
        insert_.exchange(soci::use(good.description));
        insert_.exchange(soci::use(good.tag));
        insert_.exchange(soci::use(good.quantity));

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

void GoodsTable::Update(size_t id, const Good &good)
{
    try
    {
        soci::transaction transaction{*session_};

        update_.exchange(soci::use(good.name));
        update_.exchange(soci::use(good.price));
        update_.exchange(soci::use(good.description));
        update_.exchange(soci::use(good.tag));
        update_.exchange(soci::use(good.quantity));

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

void GoodsTable::FindById(size_t id, Good &good)
{
    try
    {
        select_.exchange(soci::use(id));
        select_.exchange(soci::use(good.name));
        select_.exchange(soci::use(good.price));
        select_.exchange(soci::use(good.description));
        select_.exchange(soci::use(good.tag));
        select_.exchange(soci::use(good.quantity));

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

void GoodsTable::FindAll(std::vector<Good> &goods)
{
    try
    {
        goods.clear();

        const size_t count = Count();

        if (0 == count)
        {
            return;
        }

        std::vector<size_t> ids;
        std::vector<std::string> names;
        std::vector<double> prices;
        std::vector<std::string> descriptions;
        std::vector<std::string> tags;
        std::vector<size_t> quantities;

        names.resize(count);
        prices.resize(count);
        descriptions.resize(count);
        tags.resize(count);
        quantities.resize(count);

        selectAll_.exchange(soci::into(ids));
        selectAll_.exchange(soci::into(names));
        selectAll_.exchange(soci::into(prices));
        selectAll_.exchange(soci::into(descriptions));
        selectAll_.exchange(soci::into(tags));
        selectAll_.exchange(soci::into(quantities));

        selectAll_.define_and_bind();
        selectAll_.execute(true);
        selectAll_.bind_clean_up();

        goods.resize(count);
        for (size_t i = 0; i < goods.size(); ++i)
        {
            goods[i].id = ids[i];
            goods[i].name = std::move(names[i]);
            goods[i].price = std::move(prices[i]);
            goods[i].description = std::move(descriptions[i]);
            goods[i].tag = std::move(tags[i]);
            goods[i].quantity = std::move(quantities[i]);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void GoodsTable::Delete(size_t id)
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

size_t GoodsTable::Count()
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
