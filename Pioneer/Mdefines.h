#pragma once

#ifndef __M_DEFINES_H__
#define __M_DEFINES_H__

#define	SAFE_RELEASE(p)		if(p){ p->Release();	delete p;	p = nullptr;	}
#define SAFE_DELETE(p)		if(p){					delete p;	p = nullptr;	}

#define SAFE_DELETE_VECTOR(p)	\
{								\
	for(auto i : p)				\
	{							\
		delete i;				\
	}							\
	p.clear();					\
}

#endif