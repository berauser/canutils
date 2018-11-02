
#ifndef SRC_BASIC_SINGELTON_H_
#define SRC_BASIC_SINGELTON_H_

#include <mutex>
#include <memory>

template <class T>
class Singleton
{
public:
	Singleton()
	{
	}

	~Singleton()
	{
	}

	T* operator->() const
	{
		std::unique_lock<std::mutex> lock(_mutex);
		if( _singleton == nullptr )
		{
			_singleton = std::make_shared<T>();
		}
		lock.unlock();
		return _singleton.get();
	}

private:
	Singleton(const Singleton&) = delete;

private:
	static std::shared_ptr<T> _singleton; // use shared_ptr for cleanup
	mutable std::mutex _mutex;
};

template <class T>
std::shared_ptr<T> Singleton<T>::_singleton = nullptr;

#endif /* SRC_BASIC_SINGELTON_H_ */
