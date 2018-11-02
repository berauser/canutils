

#ifndef SRC_BUFFER_CANBUFFERREGISTRY_H_
#define SRC_BUFFER_CANBUFFERREGISTRY_H_

#include "Registry.h"
#include "Singleton.h"
#include "CanBuffer.h"

namespace CanUtils
{

#define CAN_BUFFER_REGISTRATION registrationCanBuffer
extern Singleton<Registry<CanBuffer, std::string, unsigned int>> CAN_BUFFER_REGISTRATION;

template<typename T>
class RegistryMaker
{
public:
    RegistryMaker(const std::string& key) : _key(key)
    {
        CAN_BUFFER_REGISTRATION->registerClass<T>( _key );
    }
    ~RegistryMaker()
    {
        CAN_BUFFER_REGISTRATION->unregisterClass( _key );
    }
private:
    std::string _key;
};

#define REGISTER_CANBUFFER(   type, key ) static RegistryMaker<type> maker##type(key)

} /* namespace CanUtils */

#endif /* SRC_BUFFER_CANBUFFERREGISTRY_H_ */
