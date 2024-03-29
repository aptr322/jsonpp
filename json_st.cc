#include "json_st.hh"

using namespace std;
using namespace JSON;

Value::Value() : type_t(NIL) { }

Value::Value(const int i) : int_v(i), type_t(INT) { }

Value::Value(const float f) : float_v(f), type_t(FLOAT) { }

Value::Value(const bool b) : bool_v(b), type_t(BOOL) { }

Value::Value(const char* s) : string_v(s), type_t(STRING) { }

Value::Value(const string& s) : string_v(s), type_t(STRING) { }

Value::Value(const Object& o) : object_v(o), type_t(OBJECT) { }

Value::Value(const Array& o) : array_v(o), type_t(ARRAY) { }

Value::Value(const string&& s) : string_v(move(s)), type_t(STRING) { }

Value::Value(const Object&& o) : object_v(move(o)), type_t(OBJECT) { }

Value::Value(const Array&& o) : array_v(move(o)), type_t(ARRAY) { }

Value::Value(const Value& v)
{ 
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = v.string_v;
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = v.array_v;
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = v.object_v;
            type_t = OBJECT;
            break;
        
    }
}

Value::Value(const Value&& v)
{ 
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = move(v.string_v);
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = move(v.array_v);
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = move(v.object_v);
            type_t = OBJECT;
            break;
        
    }
}

Value& Value::operator=(const Value& v)
{
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = v.string_v;
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = v.array_v;
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = v.object_v;
            type_t = OBJECT;
            break;
        
    }
    
    return *this;

}

Value& Value::operator=(const Value&& v)
{
    switch(v.type())
    {
        /** Base types */
        case INT:
            int_v = v.int_v;
            type_t = INT;
            break;
        
        case FLOAT:
            float_v = v.float_v;
            type_t = FLOAT;
            break;
        
        case BOOL:
            bool_v = v.bool_v;
            type_t = BOOL;
            break;
        
        case NIL:
            type_t = NIL;
            break;
        
        case STRING:
            string_v = move(v.string_v);
            type_t = STRING;
            break;
        
        /** Compound types */
            case ARRAY:
            array_v = move(v.array_v);
            type_t = ARRAY;
            break;
        
        case OBJECT:
            object_v = move(v.object_v);
            type_t = OBJECT;
            break;
        
    }
    
    return *this;

}

Object::Object() { }

Object::~Object() { }

Object::Object(const Object& o) : _object(o._object) { }

Object::Object(const Object&& o) : _object(move(o._object)) { }

Object& Object::operator=(const Object& o)
{
    _object = o._object;
    return *this;
}

Object& Object::operator=(const Object&& o)
{
    _object = move(o._object);
    return *this;
}

Value& Object::operator[] (const string& key)
{
    return _object[key];
}

pair<map<string, Value>::iterator, bool> Object::insert(const pair<string, Value>& v)
{
    return _object.insert(v);
}

map<string, Value>::const_iterator Object::begin() const
{
    return _object.begin();
}

map<string, Value>::const_iterator Object::end() const
{
    return _object.end();
}

map<string, Value>::iterator Object::begin()
{
    return _object.begin();
}

map<string, Value>::iterator Object::end()
{
    return _object.end();
}

map<string, Value>::iterator Object::find(const std::string& key)
{
  return _object.find(key);
}

size_t Object::erase(const std::string& key)
{
  return _object.erase(key);
}

map<string, Value>::iterator Object::erase(map<string, Value>::const_iterator it)
{
  return _object.erase(it);
}

size_t Object::size() const
{
    return _object.size();
}

Array::Array() { }

Array::~Array() { }

Array::Array(const Array& a) : _array(a._array) { }

Array::Array(const Array&& a) : _array(move(a._array)) { }

Array& Array::operator=(const Array& a)
{
    _array = a._array;
    return *this;
}

Array& Array::operator=(const Array&& a)
{
    _array = move(a._array);
    return *this;
}


Value& Array::operator[] (size_t i)
{
    return _array[i];
}

vector<Value>::const_iterator Array::begin() const
{
    return _array.begin();
}

vector<Value>::const_iterator Array::end() const
{
    return _array.end();
}

vector<Value>::iterator Array::begin()
{
    return _array.begin();
}

vector<Value>::iterator Array::end()
{
    return _array.end();
}

size_t Array::size() const
{
    return _array.size();
}

void Array::push_back(const Value& v)
{
    _array.push_back(v);
}

/*
void JSON::indent(ostream& os)
{
    for (unsigned int i  = 0; i < ind; i++)
        os << "\t";
}
*/

ostream& operator<<(ostream& os, const Value& v)
{    
    switch(v.type())
    {
        /** Base types */
        case INT:
            os << (int)v;
            break;
        
        case FLOAT:
            os << (float)v;
            break;
        
        case BOOL:
            os << ((bool)v ? "true" : "false");
            break;
        
        case NIL:
            os << "null";
            break;
        
        case STRING:
            os << '"' << (string)v << '"';                
            break;
        
        /** Compound types */
        case ARRAY:
            os << (Array)v;                
            break;
        
        case OBJECT:
            os << (Object)v;                
            break;
        
    }
    return os;
}

ostream& operator<<(ostream& os, const Object& o)
{    
    os << "{";
    for (auto e = o.begin(); e != o.end();)
    {
        os << '"' << e->first << '"' << ":" << e->second;
        if (++e != o.end())
            os << ",";
    }    
    os << "}";
    
    return os;
}

ostream& operator<<(ostream& os, const Array& a)
{
    os << "[";
    for (auto e = a.begin(); e != a.end();)
    {
        os << (*e);
        if (++e != a.end())
            os << ",";
    }    
    os << "]";
    
    return os;
}
