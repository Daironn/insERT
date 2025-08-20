#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

constexpr unsigned int ObjectAppUser  = 0;
constexpr unsigned int ObjectDocument = 1;
constexpr unsigned int ObjectProduct  = 2;

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

    virtual long         Id() const     = 0;
    virtual unsigned int Type() const   = 0;
    virtual void         InitNew()      = 0;
    virtual void         Fetch(long id) = 0;
    virtual void         Update()       = 0;
    virtual void         Delete()       = 0;
    virtual void         ShowWindow()   = 0;
    virtual void         Print()        = 0;

    // document
    virtual void SendDocumentProductsEmail() = 0;
};
