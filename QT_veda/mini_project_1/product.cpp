#include "product.h"


Product::Product(int id, const string &name, double price) : m_id(id), m_name(name), m_price(price) {}

int Product::getId() const
{
    return m_id;
}

string Product::getName() const
{
    return m_name;
}

double Product::getPrice() const
{
    return m_price;
}

void Product::setName(const string &name)
{
    m_name = name;
}

void Product::setPrice(double price)
{
    m_price = price;
}

