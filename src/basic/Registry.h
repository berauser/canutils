
#ifndef SRC_BASIC_REGISTRY_H_
#define SRC_BASIC_REGISTRY_H_

#include "platform.h"

#include <map>
#include <list>
#include <memory>
#include <functional>

/*************************************************************************//***
 *
 * Generic excpetion for registry
 * 
 * ***************************************************************************/
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

/*************************************************************************//***
 *
 * Generic registry base class
 * 
 * ***************************************************************************/
template<typename Base, typename Key, typename ...Args>
class Registry
{
public:
    typedef std::function< Base*(Args...) > Constructor; 

    Registry() = default;
    ~Registry() = default;

    template<typename Derived>
    void registerClass(const Key &key)
    {
        m_map[key] = [](Args... args)->Base*{ return new Derived(args...); };
    }
    
    void unregisterClass(const Key &key)
    {
        m_map.erase(key);
    }

    bool isRegisteredClass(const Key &key)
    {
        return ( m_map.find( key ) != m_map.end() );
    }

    std::list<Key> registeredClassKeys() const
    {
        std::list<Key> keys;
        for( auto k : m_map )
        {
                keys.push_back( k.first );
        }
        return keys;
    }
    
    void clear()
    {
            m_map.clear();
    }
    
    std::shared_ptr<Base> get(const Key &key, Args... args)
    {
        try
        {
            return std::shared_ptr<Base>(m_map.at(key)(std::forward<Args>(args)...));
        }
        catch(const std::out_of_range &e)
        {
            throw UndefinedKeyException<Key>(key);
        }
    }

private:
    std::map<Key, Constructor > m_map;
};

/*************************************************************************//***
 *
 * Priorities for construcotr/destructor functions
 * 
 * ***************************************************************************/
#define FACTORY_PRIORITY  1000
#define REGISTER_PRIORITY 2000

/*************************************************************************//***
 *
 * Macros to register/unregister types on loading/unloading
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

#endif /* SRC_BASIC_REGISTRY_H_ */
