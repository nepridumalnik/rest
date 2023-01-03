#pragma once

#include <vector>

template <typename T> struct ICrud
{
    virtual void Insert(const T &) = 0;
    virtual void Update(size_t id, const T &) = 0;
    virtual void FindById(size_t, T &) = 0;
    virtual void FindAll(std::vector<T> &) = 0;
    virtual void Delete(size_t) = 0;
    virtual size_t Count() = 0;

    virtual ~ICrud() = default;
};
