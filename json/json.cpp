#include "json.h"
#include <sstream>

using namespace yazi::json;

Json::Json():m_type(json_null)
{

}

Json::Json(bool value):m_type(json_bool)
{
    m_value.m_bool = value;
}

yazi::json::Json::Json(int value):m_type(json_int)
{
    m_value.m_int = value;
}
Json::Json(double value):m_type(json_double)
{   
    m_value.m_double = value;
}
Json::Json(const char* value):m_type(json_string)
{
    m_value.m_string = new std::string(value);
}
Json::Json(const std::string& value):m_type(json_string)
{
    m_value.m_string = new std::string(value);
}
Json::Json(Type type):m_type(m_type)
{
    switch (m_type)
    {
    case json_null:
        break;
    case json_bool:
        m_value.m_bool = false;
        break;
    case json_int:
        m_value.m_int = 0;
        break;
    case json_double:
        m_value.m_double = 0.0;
        break;
    case json_string:
        m_value.m_string = new std::string("");
        break;
    case json_array:
        m_value.m_array = new std::vector<Json>();
        break;
    case json_object:
        m_value.m_obecjt = new std::map<std::string,Json>();
        break;
    default:
        break;
    }
}
Json::Json(const Json& orther)
{
    m_type = orther.m_type;
    switch (m_type)
    {
    case json_null:
        break;
    case json_bool:
        m_value.m_bool = orther.m_value.m_bool;
        break;
    case json_int:
        m_value.m_int = orther.m_value.m_int;
        break;
    case json_double:
        m_value.m_double = orther.m_value.m_double;
        break;
    case json_string:
        m_value.m_string = orther.m_value.m_string;//浅拷贝

        break;
    case json_array:
        m_value.m_array = orther.m_value.m_array;
        break;
    case json_object:
        m_value.m_obecjt = orther.m_value.m_obecjt;
        break;
    default:
        break;
    }
}

Json::operator bool ()
{
    if(m_type != json_bool) {
        throw new logic_error("m_type is not bool");
    } 
    return m_value.m_bool;
}
Json::operator int  ()
{
    if(m_type != json_int) {
        throw new logic_error("m_type is not int");
    }
    return m_value.m_int;
}
Json::operator double ()
{
    if(m_type != json_double) {
        throw new logic_error("m_string is not int");
    }
    return m_value.m_double;
}
Json::operator std::string ()
{
    if(m_type != json_string) {
        throw new logic_error("m_string is not int");
    }
    return *m_value.m_string;
}

Json& Json::operator [](int index)
{
    if(m_type != json_array) 
    {
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    if(index < 0) 
    {
        throw new logic_error("array[] index < 0");
    }
    int size = (m_value.m_array)->size();
    if(index >= size) { //内存分配
        for (int i = size;i <= index; ++i) {
            (m_value.m_array)->push_back(Json());
        }
    }
    return (m_value.m_array)->at(index);
}   

void  Json::append(const Json& other)
{
    if(m_type != json_array) 
    {
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

std::string Json::str() const
{
    stringstream ss;
    switch (m_type)
    {
    case json_null:
        ss << "null";
        break;
    case json_bool:
        if(m_value.m_bool) 
        {
            ss << "true";
        } 
        else 
        {
            ss << "false";
        } 
        break;
    case json_int:
        ss << m_value.m_int;
        break;
    case json_double:
        ss << m_value.m_double;
        break;
    case json_string:
        ss << '\"' << *(m_value.m_string) << '\"';
        break;
    case json_array:
        ss << '[';
        for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end();it ++)
        {
            if(it != m_value.m_array->begin()) 
            {
                ss << ",";
            }
            ss << it->str();
        }
        ss << ']';
        break;
    case json_object:
        ss << '{';
        for (auto it = (m_value.m_obecjt)->begin(); it != (m_value.m_obecjt)->end();it ++)
        {
            if(it != m_value.m_obecjt->begin()) 
            {
                ss << ",";
            }
            ss << '\"' << it->first << '\"' << it->second.str();
        }
        ss << '}';
        break;
    default:
        break;
    }
    return ss.str();
}
