#include <cstring>
#include <cstdlib>

#include "AttributeValue.h"

using namespace TS_CPP;

AttributeValue::AttributeValue(const char* strPtr)
{
    if(strPtr != nullptr)
    {
        // Equivalente a strdup, pero estandar (strdup no es C++ estandar)
        size_t len = strlen(strPtr) + 1;
        this->data.strPtr = (char*) malloc(len);
        memcpy(this->data.strPtr, strPtr, len);
        this->type = STRING;
    }
    else
    {
        this->data.strPtr = nullptr;
        this->type = NOATRIB;
    }
}

AttributeValue::AttributeValue(long long int integer)
{
    this->data.integer = integer;
    this->type = INT;
}

AttributeValue::~AttributeValue()
{
    if(this->type == STRING)
    {
        free(this->data.strPtr);
    }
}

bool AttributeValue::operator==(const AttributeValue& other)
{
    if(this->type != other.type)
    {
        return false;
    }

    if(this->type == STRING)
    {
        return strcmp(this->data.strPtr, other.data.strPtr) == 0;
    }

    return this->data.integer == other.data.integer;
}

bool AttributeValue::operator!= (const AttributeValue& other)
{
    return ! (*this == other);
}

std::pair<AttributeValue::AttributeType, AttributeValue::DataUnion> AttributeValue::getValue()
{
    return {type,data};
}

bool AttributeValue::isAValidAttributeValue()
{
    return this->type != NOATRIB;
}