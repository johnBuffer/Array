#pragma once
#include <vector>

template<typename T>
struct Ptr;

template<typename T>
struct Array
{
	Array() :
		data_size(0)
	{}

	uint64_t push_back(const T& obj);
	void erase(uint64_t id);

	T& operator[](uint64_t i);
	const T& operator[](uint64_t i) const;
	Ptr<T> getPtr(uint64_t id);

	uint64_t size() const;

private:
	std::vector<T> data;
	std::vector<uint64_t> ids;
	std::vector<uint64_t> rids;
	uint64_t data_size;

	uint64_t createNewSlot(const T& obj);
	uint64_t reuseSlot(const T& obj);
	const T& getAt(uint64_t i) const;
};

template<typename T>
inline uint64_t Array<T>::push_back(const T& obj)
{
	if (data_size == data.size()) {
		return createNewSlot(obj);
	}

	return reuseSlot(obj);
}

template<typename T>
inline void Array<T>::erase(uint64_t id)
{
	--data_size;
	uint64_t current_data_id = ids[id];
	std::swap(data[data_size], data[current_data_id]);
	rids[data_size] = id;

	const uint64_t last_obj_id = rids[data_size];
	rids[current_data_id] = last_obj_id;
	ids[last_obj_id] = current_data_id;
}

template<typename T>
inline T& Array<T>::operator[](uint64_t i)
{
	return const_cast<T&>(getAt(i));
}

template<typename T>
inline const T& Array<T>::operator[](uint64_t i) const
{
	return getAt(i);
}

template<typename T>
inline Ptr<T> Array<T>::getPtr(uint64_t id)
{
	return Ptr<T>(id, *this);
}

template<typename T>
inline uint64_t Array<T>::size() const
{
	return data_size;
}

template<typename T>
inline uint64_t Array<T>::createNewSlot(const T& obj)
{
	data.push_back(obj);
	ids.push_back(data_size);
	rids.push_back(data_size);
	return data_size++;
}

template<typename T>
inline uint64_t Array<T>::reuseSlot(const T& obj)
{
	const uint64_t reuse_id = rids[data_size];
	data[reuse_id] = obj;
	++data_size;
	return reuse_id;
}

template<typename T>
inline const T& Array<T>::getAt(uint64_t i) const
{
	return data[ids[i]];
}


template<typename T>
struct Ptr
{
	Ptr(uint64_t id_, Array<T>& a)
		: id(id_)
		, array(a)
	{}

	T* operator->()
	{
		return &array[id];
	}

	T& operator*()
	{
		return array[id];
	}

private:
	uint64_t id;
	Array<T>& array;
};
