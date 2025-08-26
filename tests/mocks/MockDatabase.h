#pragma once
#include <gmock/gmock.h>

#include "Database/IDatabase.h"

class MockDatabase : public IDatabase
{
  public:
    MOCK_METHOD(std::shared_ptr<IBusinessObject>,
                Create,
                (ObjectType type, const std::string& payload),
                (override));
    MOCK_METHOD(std::shared_ptr<IBusinessObject>, Fetch, (Id id), (override));
    MOCK_METHOD(bool, Delete, (Id id, std::optional<Id> currentUserId), (override));
    MOCK_METHOD(bool, Update, (const std::shared_ptr<IBusinessObject>& obj), (override));
    MOCK_METHOD(std::vector<Id>, GetAllIds, (), (const, override));
};
