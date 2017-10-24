#include <stdio.h>
#include <string.h>

#define DECLARE_DYNAMIC_INFO()\
	protected:\
		static const char* s_ClassName;\
	public:\
		virtual const char* GetClassName();\
		virtual const char* GetBaseClassName();

#define IMPLEMENT_DYNAMIC_INFO(CLASSNAME, BASECLASSNAME)\
	const char* CLASSNAME::s_ClassName = #CLASSNAME;\
	const char* CLASSNAME::GetClassName()\
	{\
		return s_ClassName;\
	}\
	const char* CLASSNAME::GetBaseClassName()\
	{\
		return BASECLASSNAME::s_ClassName;\
	}

class CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(CObject, CObject)

class A : public CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(A, CObject)

class B : public CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(B, CObject)

void PrintInfo(CObject* p)
{
	if (strcmp(p->GetClassName(), "A") == 0)
	{
		printf("Object is a Class of %s.\n", p->GetClassName());
		printf("Base Class of %s is %s\n", p->GetClassName(), p->GetBaseClassName());
	}
	if (strcmp(p->GetClassName(), "B") == 0)
	{
		printf("Object is a Class of %s.\n", p->GetClassName());
		printf("Base Class of %s is %s\n", p->GetClassName(), p->GetBaseClassName());
	}
}

int main()
{
	CObject* p1 = new A;
	CObject* p2 = new B;

	PrintInfo(p1);
	PrintInfo(p2);

	getchar();
	return 0;
}