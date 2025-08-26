#pragma once

namespace insERT::ops
{
    class ISystemOperations
    {
      public:
        virtual ~ISystemOperations()   = default;
        virtual void BackupDocuments() = 0;
    };
} // namespace insERT::ops
