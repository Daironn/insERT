#pragma once
#include "IBusinessObject.h"

class BusinessObject : public IBusinessObject
{
  public:
    long         m_objectId{0L};
    unsigned int m_objectType;

    BusinessObject() = default;
    BusinessObject(unsigned int type) : m_objectType(type) {}

    long         Id() const;
    unsigned int Type() const;
    // inicjowanie nowego obiektu
    void InitNew();

    // wczytanie obiektu z bazy danych
    void Fetch(long id);

    // zapis zmian obiektu do bazy danych
    void Update();

    // usunięcie obiektu z bazy danych
    void Delete();
    // wyświetlenie okna edycji obiektu
    void ShowWindow();
    // drukowanie obiektu na domyślną drukarkę
    void Print();

    // wysyłanie danych dokumentu e-mailem
    virtual void SendDocumentProductsEmail() {}

    virtual void OnInitNew() {}
    virtual void OnFetch() {}
    virtual void OnUpdate() {}
    virtual void OnDelete() {}
};
