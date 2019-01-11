//=============================================================================
//
//  Example.h
//
//  Copyright 2006 Possibility Space Incorporated.
//
//  Comments
//  Comments
//  Comments
//  Comments
//
//=============================================================================


#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


//-----------------------------------------------------------------------------
//  Class Example
//-----------------------------------------------------------------------------
template <class T> class Example
{
public:
	//-- Construction/Destruction
	Example(_ulong Parameter = DEFAULT_VALUE);
	Example();
	~Example();

	//-- Interface
	_void  Func01();
	_void  Func02(_ulong Param, _ulong* pParam);
	_ulong Func03() const;

	//-- Operators
	T&          operator[](_ulong Index);
	Example<T>& operator= (const Example<T>& Array);
	_bool       operator==(const Example<T>& Array);

private:
	//-- Private Data
	T*     m_pMember;
	_ulong m_Member;
	_ulong m_Member;
};


//=============================================================================
//  CONSTRUCTION/DESTRUCTION
//=============================================================================
template <class T> Example<T>::Example(_ulong Parameter)
{
	//-- Make sure we have valid parameter.
	if (Parameter == 0) Parameter = 1;

	//-- Initialize members.
	m_pMember = NULL;
	m_Member  = 0;
	m_Member  = 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <class T> Example<T>::Example()
{
	//-- Initialize members.
	m_pArray      = NULL;
	m_AllocedSize = 0;
	m_InitialSize = 0;
	m_GrowSize    = 0;
	m_CurSize     = 0;
	Copy(Array);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <class T> Example<T>::~Example()
{
	//-- Kill the old array.
	if (m_pArray)
		delete [] m_pArray;

	//-- Reset members.
	m_pMember = NULL;
	m_Member  = 0;
	m_Member  = 0;
}


//=============================================================================
//  INTERFACE
//=============================================================================
template <class T> _void Example<T>::Func01()
{
	L_ASSERT(m_InitialSize);

	//-- Kill the old array.
	if (m_pArray)
		delete [] m_pArray;

	//-- Make a new one.
	m_pArray      = new T[m_InitialSize];
	m_AllocedSize = m_InitialSize;
	m_CurSize     = 0;
}


#endif


