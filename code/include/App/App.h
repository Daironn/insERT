#pragma once
#include <memory>
#include <string>

class AppUser;
class Database;
class Document;
class App
{
  private:
    std::weak_ptr<AppUser>    m_user;
    std::shared_ptr<Database> m_database;

  public:
    App();

    void      Login(int userId);
    void      Logout();
    void      DoBusinessOperations();
    Document* CreateDocument(const std::string& number);
    void      AddProductToDocument(Document* doc, const std::string& productName);
    void      RemoveAllDocuments();
};
