#pragma once

class ISystemOperations
{
  public:
    virtual ~ISystemOperations()   = default;
    virtual void BackupDocuments() = 0;
};
