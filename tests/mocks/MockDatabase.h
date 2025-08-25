#pragma once
#include <gmock/gmock.h>

#include "Database/IDatabase.h"

class MockDatabase : public insERT::database::IDatabase
{
  public:
    MOCK_METHOD(std::shared_ptr<insERT::object::IBusinessObject>,
                Create,
                (insERT::common::ObjectType type, const std::string& payload),
                (override));
    MOCK_METHOD(std::shared_ptr<insERT::object::IBusinessObject>,
                Fetch,
                (insERT::common::Id id),
                (override));
    MOCK_METHOD(bool,
                Delete,
                (insERT::common::Id id, std::optional<insERT::common::Id> currentUserId),
                (override));
    MOCK_METHOD(bool,
                Update,
                (const std::shared_ptr<insERT::object::IBusinessObject>& obj),
                (override));
    MOCK_METHOD(std::vector<insERT::common::Id>, GetAllIds, (), (const, override));
};
