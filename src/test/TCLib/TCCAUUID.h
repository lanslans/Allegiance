#ifndef __TCCAUUID_h__
#define __TCCAUUID_h__

/////////////////////////////////////////////////////////////////////////////
// TCCAUUID.h | Declaration and inline implementation of the TCCAUUID
// structure.


/////////////////////////////////////////////////////////////////////////////
// Encapsulates a COM CAUUID, which is a counted array of UUID's.
struct TCCAUUID : public tagCAUUID
{
// Construction / Destruction
public:
  TCCAUUID();
  ~TCCAUUID();
};


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

/////////////////////////////////////////////////////////////////////////////
// Constructs the object by initializing the base structure members as
// follows:
//
//       cElems = 0;
//       pElems = NULL;
inline TCCAUUID::TCCAUUID()
{
  cElems = 0;
  pElems = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Calls CoTaskMemFree to release the base structure member, pElems, if it is
// not NULL.
inline TCCAUUID::~TCCAUUID()
{
  if (pElems)
    CoTaskMemFree(pElems);
}

/////////////////////////////////////////////////////////////////////////////

#endif // !__TCCAUUID_h__
