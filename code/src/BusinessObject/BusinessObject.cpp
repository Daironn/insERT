#include "BusinessObject.h"

long BusinessObject::Id() const
{
    return m_objectId;
}

unsigned int BusinessObject::Type() const
{
    return m_objectType;
}

void BusinessObject::InitNew()
{
    try
    {
        m_objectId = std::rand() % 1000 + 1;
        OnInitNew();
        std::cout << "InitNew impl (type: " << object_type_to_str(m_objectType)
                  << ", id: " << m_objectId << ")" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "InitNew exception: " << e.what() << std::endl;
    }
}

void BusinessObject::Fetch(long id)
{
    try
    {
        m_objectId = id;
        OnFetch();
        std::cout << "Fetch impl (type: " << object_type_to_str(m_objectType)
                  << ", id: " << m_objectId << ")" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Fetch exception: " << e.what() << std::endl;
    }
}

void BusinessObject::Update()
{
    try
    {
        OnUpdate();
        std::cout << "Update impl (type: " << object_type_to_str(m_objectType)
                  << ", id: " << m_objectId << ")" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Update exception: " << e.what() << std::endl;
    }
}

void BusinessObject::Delete()
{
    try
    {
        OnDelete();
        std::cout << "Delete impl (type: " << object_type_to_str(m_objectType)
                  << ", id: " << m_objectId << ")" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Delete exception: " << e.what() << std::endl;
    }
}

void BusinessObject::ShowWindow()
{
    std::cout << "ShowWindow impl (type: " << object_type_to_str(m_objectType)
              << ", id: " << m_objectId << ")" << std::endl;
}

void BusinessObject::Print()
{
    std::cout << "Print impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId
              << ")" << std::endl;
}
