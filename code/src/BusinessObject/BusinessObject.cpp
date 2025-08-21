#include "BusinessObject.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

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
        LOG_INFO("Initialized {} with id {}", object_type_to_str(m_objectType), m_objectId);
    }
    catch (std::exception& e)
    {
        std::cerr << "InitNew exception: " << e.what() << std::endl;
        LOG_WARNING("InitNew exception: {}", e.what());
    }
}

void BusinessObject::Fetch(long id)
{
    try
    {
        m_objectId = id;
        OnFetch();
        LOG_INFO("Fetched {} with id {}", object_type_to_str(m_objectType), m_objectId);
    }
    catch (std::exception& e)
    {
        LOG_ERROR("Fetch exception: {}", e.what());
    }
}

void BusinessObject::Update()
{
    try
    {
        OnUpdate();
        LOG_INFO("Updated {} with id {}", object_type_to_str(m_objectType), m_objectId);
    }
    catch (std::exception& e)
    {
        LOG_WARNING("Update exception: {}", e.what());
    }
}

void BusinessObject::Delete()
{
    try
    {
        OnDelete();
        LOG_INFO("Deleted {} with id {}", object_type_to_str(m_objectType), m_objectId);
    }
    catch (std::exception& e)
    {
        LOG_WARNING("Delete exception: {}", e.what());
    }
}

void BusinessObject::ShowWindow()
{
    LOG_INFO("ShowWindow called for {} with id {}", object_type_to_str(m_objectType), m_objectId);
}

void BusinessObject::Print()
{
    LOG_INFO("Print called for {} with id {}", object_type_to_str(m_objectType), m_objectId);
}
