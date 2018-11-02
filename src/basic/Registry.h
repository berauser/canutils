
#ifndef SRC_BASIC_REGISTRY_H_
#define SRC_BASIC_REGISTRY_H_

#include <map>
#include <list>
#include <memory>
#include <functional>

/*************************************************************************//***
 *
 * Generic excpetion for registry
 * 
 * ***************************************************************************/
 /**
  * Exception for undefined keys.
  * The Undefined key excpetion is thrown when the key is not registered
  * in the registry.
  */
template<typename Key>
class UndefinedKeyException : public std::exception
{
 public:
    /**
     * Constructor
     * @param key The key that is not found in the registry
     */
    UndefinedKeyException(const Key &key) : _key(key) {}

    /**
     * Returns the excpetion description.
     * @return Describtion of the exception.
     */
    const char *what()const throw() { return "Key is not defined"; }
    /**
     * Returns the key that is not registered.
     * @return Key that is not registered.
     */
    const Key   key() const         { return _key; }

private:
    const Key _key;   //!< key
};

/*************************************************************************//***
 *
 * Generic registry base class
 * 
 * ***************************************************************************/
 /**
  * A generic registry
  * @tparam Base The base class sof the types that should be registered
  * @tparam Key  The key type to search for the registered class
  * @tparam Args The argument list types thats should be used to create the registered type
  */
template<typename Base, typename Key, typename ...Args>
class Registry
{
public:
    /**
     * Constructor function pointer
     */
    typedef std::function< Base*(Args...) > Constructor;

    Registry() = default;
    ~Registry() = default;

    /**
     * Register a derived class.
     * @tparam Derived The type of the derived class that should be registered.
     * @param key The key that should be used to find the type.
     */
    template<typename Derived>
    void registerClass(const Key &key)
    {
        m_map[key] = [](Args... args)->Base*{ return new Derived(args...); };
    }

    /**
     * Unregister type.
     * @param key The key of the registered type that should be unregistered.
     */
    void unregisterClass(const Key &key)
    {
        m_map.erase(key);
    }

    /**
     * Check if a class is registered
     * @param key The key of the type that should be checked
     * @return true if registered, otherwise false
     */
    bool isRegisteredClass(const Key &key)
    {
        return ( m_map.find( key ) != m_map.end() );
    }

    /**
     * Get a list of keys of all registered types
     * @return List of registered types
     */
    std::list<Key> registeredClassKeys() const
    {
        std::list<Key> keys;
        for( auto k : m_map )
        {
                keys.push_back( k.first );
        }
        return keys;
    }

    /**
     * Clears the registry
     */
    void clear()
    {
            m_map.clear();
    }

    /**
     * Creates an instances of the registered type
     * @param key THe of of the type, that should be created
     * @param args The argument(s) that should passed to the constructor.
     * @return A shared_ptr to the created object.
     * @exception UndefinedKeyException When the key is undefined
     *
     */
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
    std::map<Key, Constructor > m_map; //!< map of registered types
};

#endif /* SRC_BASIC_REGISTRY_H_ */
