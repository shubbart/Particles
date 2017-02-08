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

	size_t openHead, fillHead;
public:
	ObjectPool(size_t a_size) : m_size(a_size), openHead(0), fillHead(m_size)
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
		size_t	    m_idx;

		friend class ObjectPool;

		// ONLY the object pool can properly construct an iterator.
		iterator(ObjectPool *a_ref, size_t a_idx) : m_ref(a_ref), m_idx(a_idx) {}
	public:
		iterator() : m_ref(nullptr), m_idx(0) { }

		particle &operator* () { return  m_ref->m_data[m_idx].data; } // *this (Dereference operator)
		particle *operator->() { return &m_ref->m_data[m_idx].data; } // this->(Indirection operator)

		const particle &operator* () const { return  m_ref->m_data[m_idx].data; } // (constant dereference)
		const particle *operator->() const { return &m_ref->m_data[m_idx].data; } // (constant indirection)

		iterator &operator++() { m_idx = m_ref->m_data[m_idx].next; return *this; } // (prefix increment)
		iterator operator++(int) { auto that = *this;  operator++();  return  that; } // (postfix increment)

		bool operator==(const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!=(const iterator &O) const { return !operator==(O); }

		operator bool() const { m_ref != nullptr && m_idx < m_ref->m_size && !m_ref->m_data[m_idx].open; }
	};

	iterator push(const particle &val)
	{
		if (openHead >= m_size) return iterator();
		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;

		openHead = m_data[openHead].next;

		if (idx <= fillHead)
		{
			m_data[idx].next = fillHead;
			fillHead = idx;
		}
		else
		{
			size_t left = idx;
			while (m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}
		return iterator(this, idx);
	}

	iterator pop(const iterator &it)
	{

	}

};