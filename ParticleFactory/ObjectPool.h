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
};