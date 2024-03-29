#ifndef JSON_ST_HH
#define JSON_ST_HH

#include <iostream>
#include <map>
#include <vector>
#include <stack>

namespace JSON 
{

    /** Possible JSON type of a value (array, object, bool, ...). */
    enum ValueType
    {
        INT,        // JSON's int
        FLOAT,      // JSON's float 3.14 12e-10
        BOOL,       // JSON's boolean (true, false)
        STRING,     // JSON's string " ... " or (not really JSON) ' ... '
        OBJECT,     // JSON's object { ... }
        ARRAY,      // JSON's array [ ... ]
        NIL         // JSON's null
    };

    // Forward declaration
    class Value;

    /** A JSON object, i.e., a container whose keys are strings, this
    is roughly equivalent to a Python dictionary, a PHP's associative
    array, a Perl or a C++ map (depending on the implementation). */
    class Object
    {
    public:

        /** Constructor. */
        Object();
    
        /** Copy constructor. 
            @param o object to copy from
        */
        Object(const Object& o);
    
        /** Move constructor. */
        Object(const Object&& o);
    
        /** Assignment operator. 
            @param o object to copy from
        */
        Object& operator=(const Object& o);
    
        /** Move operator. 
            @param o object to copy from
        */
        Object& operator=(const Object&& o);
    
        /** Destructor. */
        ~Object();

        /** Subscript operator, access an element by key.
            @param key key of the object to access
        */
        Value& operator[] (const std::string& key);

        /** Retrieves the starting iterator (const).
            @remark mainly for printing
        */
        std::map<std::string, Value>::const_iterator begin() const;

        /** Retrieves the ending iterator (const).
            @remark mainly for printing
        */
        std::map<std::string, Value>::const_iterator end() const;
    
        /** Retrieves the starting iterator */
        std::map<std::string, Value>::iterator begin();

        /** Retrieves the ending iterator */
        std::map<std::string, Value>::iterator end();
    
        /** Inserts a field in the object.
            @param v pair <key, value> to insert
            @return an iterator to the inserted object
        */
        std::pair<std::map<std::string, Value>::iterator, bool> insert(const std::pair<std::string, Value>& v);

        /** Finds an element with a key */
        std::map<std::string, Value>::iterator find(const std::string& key);

        /** Erase an element with a key */
        size_t erase(const std::string& key);
        std::map<std::string, Value>::iterator erase(std::map<std::string, Value>::const_iterator it);

        /** Size of the object. */
        size_t size() const;

    protected:

        /** Inner container. */
        std::map<std::string, Value> _object;
    };

    /** A JSON array, i.e., an indexed container of elements. It contains
    JSON values, that can have any of the types in ValueType. */
    class Array
    {
    public:

        /** Constructor. */
        Array();
    
        /** Destructor. */
        ~Array();
    
        /** Copy constructor. 
            @param o the object to copy from
        */
        Array(const Array& a);
    
        /** Assignment operator. 
            @param a array to copy from
        */
        Array& operator=(const Array& a);
    
        /** Copy constructor. 
            @param o the object to copy from
        */
        Array(const Array&& a);

        /** Assignment operator. 
            @param a array to copy from
        */
        Array& operator=(const Array&& a);

        /** Subscript operator, access an element by index. 
            @param i index of the element to access
        */
        Value& operator[] (size_t i);

        /** Retrieves the starting iterator (const).
            @remark mainly for printing
        */
        std::vector<Value>::const_iterator begin() const;

        /** Retrieves the ending iterator (const).
            @remark mainly for printing
        */
        std::vector<Value>::const_iterator end() const;

        /** Retrieves the starting iterator. */
        std::vector<Value>::iterator begin();

        /** Retrieves the ending iterator */
        std::vector<Value>::iterator end();

        /** Inserts an element in the array.
            @param n (a pointer to) the value to add
        */
        void push_back(const Value& n);
    
        /** Size of the array. */
        size_t size() const;

    protected:

        /** Inner container. */
        std::vector<Value> _array;

    };

    /** A JSON value. Can have either type in ValueTypes. */
    class Value
    {
    public:
    
        /** Default constructor (type = NIL). */
        Value();
    
        /** Copy constructor. */
        Value(const Value& v);
    
        /** Constructor from int. */
        Value(const int i);
    
        /** Constructor from float. */
        Value(const float f);
    
        /** Constructor from bool. */
        Value(const bool b);
    
        /** Constructor from pointer to char (C-string).  */
        Value(const char* s);

        /** Constructor from STD string  */
        Value(const std::string& s);
    
        /** Constructor from pointer to Object. */
        Value(const Object& o);
    
        /** Constructor from pointer to Array. */
        Value(const Array& a);
    
        /** Move constructor. */
        Value(const Value&& v);
    
        /** Move constructor from STD string  */
        Value(const std::string&& s);
    
        /** Move constructor from pointer to Object. */
        Value(const Object&& o);
    
        /** Move constructor from pointer to Array. */
        Value(const Array&& a);
    
        /** Type query. */
        ValueType type() const
        {
            return type_t;
        }
    
        /** Assignment operator. */
        Value& operator=(const Value& v);
    
        /** Move operator. */
        Value& operator=(const Value&& v);
    
        /** Cast operator for float */
        operator float() const { return float_v; }
    
        /** Cast operator for float */
        operator int() const { return int_v; }
    
        /** Cast operator for float */
        operator bool() const { return bool_v; }
    
        /** Cast operator for float */
        operator std::string () const { return string_v; }
    
        /** Cast operator for Object */
        operator Object () const { return object_v; }
    
        /** Cast operator for Object */
        operator Array () const { return array_v; }


    protected:
    
        float           float_v;
        int             int_v;
        bool            bool_v;
        std::string     string_v;
    
        Object          object_v;
        Array           array_v;
    
        ValueType       type_t;
    };
    
    /** Indentation counter */
    // static unsigned int ind;

    /** Print correct indentation before printing anything */
    // static void indent(std::ostream& os = std::cout);
}

/** Output operator for Values */
std::ostream& operator<<(std::ostream&, const JSON::Value&);

/** Output operator for Objects */
std::ostream& operator<<(std::ostream&, const JSON::Object&);

/** Output operator for Arrays */
std::ostream& operator<<(std::ostream&, const JSON::Array&);



#endif
