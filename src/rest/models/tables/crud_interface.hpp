#pragma once

template <typename T> struct ICrud
{
    virtual void Insert(const T &) = 0;
    virtual void Update(size_t id, const T &) = 0;
    virtual void Select(size_t, T &) = 0;
    virtual void Delete(size_t) = 0;

    virtual ~ICrud() = default;
};
