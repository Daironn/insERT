#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

namespace BusinessApp
{
    constexpr unsigned int ObjectAppUser = 0;
    constexpr unsigned int ObjectDocument = 1;
    constexpr unsigned int ObjectProduct = 2;

    std::string object_type_to_str(unsigned int type)
    {
        switch (type)
        {
        case ObjectProduct:
            return "Product";
        case ObjectDocument:
            return "Document";
        case ObjectAppUser:
            return "AppUser";
        default:
            return "Unknown";
        }
    }

    struct IBusinessObject
    {
        virtual ~IBusinessObject() = default;

        virtual long Id() const = 0;
        virtual unsigned int Type() const = 0;
        virtual void InitNew() = 0;
        virtual void Fetch(long id) = 0;
        virtual void Update() = 0;
        virtual void Delete() = 0;
        virtual void ShowWindow() = 0;
        virtual void Print() = 0;

    	// document
        virtual void SendDocumentProductsEmail() = 0;
    };

    class BusinessObject : public IBusinessObject
    {
    public:
        long m_objectId{ 0L };
        unsigned int m_objectType;

        BusinessObject() = delete;
        BusinessObject(unsigned int type) : m_objectType(type)
        {
        }

        long Id() const { return m_objectId; }
        unsigned int Type() const { return m_objectType; }

        // inicjowanie nowego obiektu
        void InitNew()
        {
            try
            {
                m_objectId = std::rand() % 1000 + 1;
                OnInitNew();
                std::cout << "InitNew impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "InitNew exception: " << e.what() << std::endl;
            }
        }

        // wczytanie obiektu z bazy danych
        void Fetch(long id)
        {
            try
            {
                m_objectId = id;
                OnFetch();
                std::cout << "Fetch impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "Fetch exception: " << e.what() << std::endl;
            }
        }

        // zapis zmian obiektu do bazy danych
        void Update()
        {
            try
            {
                OnUpdate();
                std::cout << "Update impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "Update exception: " << e.what() << std::endl;
            }
        }

        // usunięcie obiektu z bazy danych
        void Delete()
        {
            try
            {
                OnDelete();
                std::cout << "Delete impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "Delete exception: " << e.what() << std::endl;
            }
        }

        // wyświetlenie okna edycji obiektu
        void ShowWindow()
        {
            std::cout << "ShowWindow impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
        }

        // drukowanie obiektu na domyślną drukarkę
        void Print()
        {
            std::cout << "Print impl (type: " << object_type_to_str(m_objectType) << ", id: " << m_objectId << ")" << std::endl;
        }

        // wysyłanie danych dokumentu e-mailem
        virtual void SendDocumentProductsEmail()
        {
        }

        virtual void OnInitNew() {}
        virtual void OnFetch() {}
        virtual void OnUpdate() {}
        virtual void OnDelete() {}
    };

    class Product : public BusinessObject
    {
    public:
        std::string m_productName;

        Product() : BusinessObject{ ObjectProduct }
        {
        }

        void OnFetch() override
        {
            m_productName = "product_" + std::to_string(Id());
            std::cout << "Product fetched: " << m_productName << std::endl;
        }

        void OnUpdate() override
        {
            std::cout << "Product updated: " << m_productName << std::endl;
        }

        void OnDelete() override
        {
            std::cout << "Product deleted: " << m_productName << std::endl;
        }

        void SetProductName(std::string productName)
        {
            m_productName = productName;
        }
    };

    class Document : public BusinessObject
    {
    private:
        std::string m_documentNumber;
        std::vector<Product> m_products;

    public:
        Document() : BusinessObject{ ObjectDocument }
        {
        }

        void OnFetch() override
        {
            m_documentNumber = "document_" + std::to_string(Id());

            // wczytanie powiązanych towarów
            Product product{};
            product.Fetch(std::rand() % 100 + 1);
            AddProduct(product);

            std::cout << "Document fetched: " << m_documentNumber << std::endl;
        }

        void OnUpdate() override
        {
            // zapisanie powiazanych towarów
            for (auto& product : m_products)
                product.Update();

            std::cout << "Document updated: " << m_documentNumber << std::endl;
        }

        void OnDelete() override
        {
            // usunięcie powiązanych towarów
            for (auto& product : m_products)
                product.Delete();

            std::cout << "Document deleted: " << m_documentNumber << std::endl;
        }

        void SetDocumentNumber(std::string documentNumber)
        {
            m_documentNumber = documentNumber;
        }

        void AddProduct(const Product& product)
        {
            m_products.push_back(product);
        }

        void SendDocumentProductsEmail() override
        {
            std::string content;
            for (auto& product : m_products)
                content += product.m_productName + "\n";

            std::cout << "Sending document content email: " << content << std::endl;
        }
    };

    class AppUser : public BusinessObject
    {
    private:
        std::string m_login;

    public:
        AppUser() : BusinessObject{ ObjectAppUser }
        {
        }

        void OnFetch() override
        {
            m_login = "user" + std::to_string(Id());
            std::cout << "AppUser fetched: " << m_login << std::endl;
        }

        void OnUpdate() override
        {
            std::cout << "AppUser updated: " << m_login << std::endl;
        }

        void OnDelete() override
        {
            std::cout << "AppUser deleted: " << m_login << std::endl;
        }

        void SetLogin(std::string login)
        {
            m_login = login;
        }

        const std::string& Login() const { return m_login; }
    };

    class BusinessOperations
    {
    private:
        std::vector<Document> m_documents;
        AppUser m_user;

    public:
        void FetchUser(int userId)
        {
            m_user.Fetch(userId);
        }

        void AddNewDocument()
        {
            Document document{};
            {
                document.InitNew();
                document.SetDocumentNumber("document_" + std::to_string(std::rand() % 100 + 1));

                for (int j = 0; j < std::rand() % 3 + 1; j++)
                {
                    Product product{};
                    product.InitNew();
                    product.SetProductName("product_" + std::to_string(std::rand() % 100 + 1));
                    document.AddProduct(product);
                }

                document.Update();
            }

            m_documents.push_back(document);
        }

        void FetchMoreDocument()
        {
            // warunek symulujący, czy dokumenty są gotowe do pobrania (np. z webservice'u)
            if (DocumentsReady())
                return;

            for (long id : { 1000, 2000, 3000 })
            {
                Document document{};
                document.Fetch(id);
                m_documents.push_back(document);
            }
        }

        void RemoveAllDocuments()
        {
            // warunek symulujący uprawnienie, czy użytkownik ma id = 1 (administrator)
            if (m_user.Id() != 1)
                return;

            for (auto& document : m_documents)
                document.Delete();

            m_documents.clear();
        }

        bool DocumentsReady()
        {
            return std::rand() % 4 > 0;
        }
    };

    class App
    {
    private:
        BusinessOperations m_businessOperations;
        AppUser m_user;

    public:
        App()
        {
        }

        // logowanie do aplikacji
        void Login(int userId)
        {
            m_user.Fetch(userId);
            std::cout << "User login (" << userId << ")" << std::endl;
        }

        // wylogowanie 
        void Logout()
        {
            std::cout << "User logout (" << m_user.Id() << ")" << std::endl;
        }

        // operacje biznesowe
        void DoBusinessOperations()
        {
            // brak zalogowanego użytkownika
            if (!m_user.Id())
                return;

            m_businessOperations.FetchUser(m_user.Id());

            m_businessOperations.AddNewDocument();
            m_businessOperations.AddNewDocument();
            m_businessOperations.AddNewDocument();

            m_businessOperations.FetchMoreDocument();

            m_businessOperations.RemoveAllDocuments();
        }
    };
}

namespace SystemOperations
{
    void BackupDocuments()
    {
        using namespace BusinessApp;

        for (int i = 1; i < 5; i++)
        {
            try
            {
                Document document{};
                document.Fetch(i);
                std::cout << "Backup document: " << document.Id() << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "Backup exception: " << i << " " << e.what() << std::endl;
            }
        }
    }
}

int main(int argc, char** argv)
{
    using namespace BusinessApp;

    if (argc == 1)
    {
        App app{};
        app.Login(1);
        app.DoBusinessOperations();
        app.Logout();
    }
    else if (argc == 2 && std::string{ argv[1] } == "-backup")
    {
        SystemOperations::BackupDocuments();
    }

    return 0;
}