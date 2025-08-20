#pragma once
#include <memory>
#include <vector>

class Document;
class AppUser;

class BusinessOperations
{
  private:
    std::vector<std::shared_ptr<Document>> m_documents;
    std::shared_ptr<AppUser>               m_user;

  public:
    void FetchUser(int userId);
    void AddNewDocument();
    void FetchMoreDocument();
    void RemoveAllDocuments();
    bool DocumentsReady();
};
