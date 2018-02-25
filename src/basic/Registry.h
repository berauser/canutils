
#ifndef SRC_REGISTRY_H
#define SRC_REGISTRY_H

#include "platform.h"

#include <map>
#include <functional>

template<typename Key>
class UndefinedKeyException : public std::exception
{
 public:
    UndefinedKeyException(const Key &key) : _key(key) {}

    const char *what()const throw() { return "Key is not defined"; }
    const Key   key() const         { return _key; }
    
private:    
    const Key _key;   
};

template<typename Base, typename Key, typename ...Args>
class Registry
{
public:
    typedef std::function< Base*(Args...) > Constructor; 

    Registry() = default;
    ~Registry() = default;

    template<typename Derived>
    void registerClass(const Key &key);
    void unregisterClass(const Key &key);
    bool isRegisteredClass( const Key &key);
    // TODO method to get all registered types in a list?
    
    Base* get(const Key &key, Args... args);

private:
    std::map<Key, Constructor > m_map;
};

template<typename Base, typename Key, typename... Args>
template<typename Derived>
void Registry<Base, Key, Args...>::registerClass(const Key &key)
{
	m_map[key] = [](Args... args)->Base*{ return new Derived(args...); };
}

template<typename Base, typename Key, typename... Args> 
void Registry<Base, Key, Args...>::unregisterClass(const Key &key)
{
	m_map.erase(key);
}

template<typename Base, typename Key, typename... Args> 
bool Registry<Base, Key, Args...>::isRegisteredClass(const Key &key)
{
	return ( m_map.find( key ) != m_map.end() );
}

template<typename Base, typename Key, typename... Args>
Base* Registry<Base, Key, Args...>::get(const Key &key, Args... args)
{
    try
    {
        return m_map.at(key)(std::forward<Args>(args)...);
    }
    catch(const std::out_of_range &e)
    {
        throw UndefinedKeyException<Key>(key);
    }
}

/*************************************************************************//***
 *
 * 
 * 
 * ***************************************************************************/
#define FACTORY_PRIORITY  1000
#define REGISTER_PRIORITY 2000

/*************************************************************************//***
 *
 * 
 * 
 * ***************************************************************************/
#define REGISTER_TYPE( type, key, database )    \
    CONSTRUCTOR(REGISTER_PRIORITY)              \
    static void register_##type(void)           \
    {                                           \
        (database)->registerClass<type>( key ); \
    }

#define UNREGISTER_TYPE( type, key, database )  \
    DESTRUCTOR(REGISTER_PRIORITY)               \
    static void unregister_##type(void)         \
    {                                           \
        (database)->unregisterClass( key );     \
    }    

#endif /* SRC_REGISTRY_H */
