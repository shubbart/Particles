#pragma once
#include <vector>
#include "particles.h"

class ObjectPool
{
	// Interleaved type, Array of Structures
	struct _intern
	{
		bool open;
		size_t next;
		particle data;

	};
	_intern *m_data;

	// Three seperate arrays / Structure of Arrays
	/*bool *m_open;
	particle *m_data;
	size_t *m_next;*/
	
	size_t m_size;
public:
	ObjectPool(size_t a_size) : m_size(a_size)
	{
		m_data = new _intern[m_size];

		for (int i = 0; i < m_size; ++i)
		{
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}

	class iterator
	{
		ObjectPool *m_ref;
		size_t m_idx;
		friend class ObjectPool;
		iterator(ObjectPool *a_ref = nullptr, size_t a_idx = 0) : m_ref(a_ref), m_idx(a_idx) {}
	public:
		iterator() : m_ref(nullptr), m_idx(0) {}
		particle &operator*() {return m_ref->m_data[m_idx].data; }
		particle *operator->() { return &m_ref->m_data[m_idx].data; }
		const particle &operator*() const { return m_ref->m_data[m_idx].data; }
		const particle *operator->() const { return &m_ref->m_data[m_idx].data; }
		iterator &operator++() { m_idx = m_ref->m_data[m_idx].next;  return *this; }
		iterator operator++(int) { auto that = *this; operator++(); return that; }

		bool operator==(const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!=(const iterator &O) const { return !(*this == O); }

		operator bool() const {m_ref != nullptr && m_idx < m_ref->m_size && !m_ref->m_data[m_idx].open; }
	};

};