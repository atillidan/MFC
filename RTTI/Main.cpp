#include <stdio.h>
#include <string.h>

#define DECLARE_DYNAMIC_INFO()\
	private:\
		static const char* s_ClassName;\
	public:\
		virtual const char* GetClassName();

#define IMPLEMENT_DYNAMIC_INFO(CLASSNAME)\
	const char* CLASSNAME::s_ClassName = #CLASSNAME;\
	const char* CLASSNAME::GetClassName()\
	{\
		return s_ClassName;\
	}

class CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(CObject)

class A : public CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(A)

class B : public CObject
{
	DECLARE_DYNAMIC_INFO()
};
IMPLEMENT_DYNAMIC_INFO(B)

void PrintInfo(CObject* p)
{
	if (strcmp(p->GetClassName(), "A") == 0)
	{
		printf("Object is a Class of A.\n");
	}
	if (strcmp(p->GetClassName(), "B") == 0)
	{
		printf("Object is a Class of B.\n");
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