#include <stdio.h>
#include <string.h>


//1-- ÿ����� _RuntimeInfo �������ֲ�һ������ʽΪ�� _##CLASSNAME##_ri
//2-- ÿ����� _RuntimeInfo ����Ϊ public ��Ϊ��ʹ�ú꣺_RUNTIMEINFO(CLASSNAME)
//3-- �����麯�� CObject::IsChildOf() �� �麯�� CObject::GetRuntimeInfo() ��ʹ�á�
//4-- CObject��û��ʹ�ú�ԭ�������ĸ���Ϊ�գ���Ҫ���⴦���ⲿ�ֲ�û�м���궨���С�

/****************************************************************************************************************
 *    Date    : 2017/10/25 10:19
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : RuntimeInfo
 *
 ****************************************************************************************************************/
class CObject;

typedef CObject* (* CreateFunc)();

class _RuntimeInfo
{
private:
	const _RuntimeInfo* pParent;
	const char* pClassName;
	const CreateFunc pCreateFunc;

public:
	_RuntimeInfo(const _RuntimeInfo* parent, const char* className, const CreateFunc createFunc);
	virtual ~_RuntimeInfo();
	CObject* CreateObject() const;
	bool IsChildOf(const _RuntimeInfo* pParent) const;
};

_RuntimeInfo::_RuntimeInfo(const _RuntimeInfo* parent, const char* className, const CreateFunc createFunc)
	:pParent(parent), pClassName(className), pCreateFunc(createFunc)
{
	//...
}

_RuntimeInfo::~_RuntimeInfo()
{
	//...
}

CObject* _RuntimeInfo::CreateObject() const
{
	if (pCreateFunc)
		return (*pCreateFunc)();
	
	return NULL;
}

bool _RuntimeInfo::IsChildOf(const _RuntimeInfo* pParent) const
{
	const _RuntimeInfo* pCur = this;
	while (pCur)
	{
		if (pCur == pParent)
			return true;

		pCur = pCur->pParent;
	}
	return false;
}


/****************************************************************************************************************
 *    Date    : 2017/10/25 10:20
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : CObject
 *
 ****************************************************************************************************************/
class CObject
{
public:
	static const _RuntimeInfo _CObject_ri;
public:
	static CObject* Create();
	virtual const _RuntimeInfo* GetRuntimeInfo();

public:
	bool IsChildOf(const _RuntimeInfo* pParent);
	virtual void PrintfInfo() { printf("This is a class of CObject"); }
};

const _RuntimeInfo CObject::_CObject_ri(NULL, "CObject", Create);
CObject* CObject::Create()
{
	return new CObject;
}
const _RuntimeInfo* CObject::GetRuntimeInfo()
{
	return &_CObject_ri;
}

bool CObject::IsChildOf(const _RuntimeInfo* pParent)
{
	const _RuntimeInfo* pRuntimeInfo = GetRuntimeInfo();
	return pRuntimeInfo->IsChildOf(pParent);
}


/****************************************************************************************************************
 *    Date    : 2017/10/25 10:36
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : �궨��
 *
 ****************************************************************************************************************/
#define _RUNTIMEINFO(CLASSNAME) ((_RuntimeInfo*)&CLASSNAME::_##CLASSNAME##_ri)

#define _DECLARE_DYNAMIC_INFO(CLASSNAME)\
	public:\
		static const _RuntimeInfo _##CLASSNAME##_ri;\
	public:\
		static CObject* Create();\
		virtual const _RuntimeInfo* GetRuntimeInfo();

#define _IMPLEMENT_DYNAMIC_INFO(CLASSNAME, BASECLASSNAME)\
	const _RuntimeInfo CLASSNAME::_##CLASSNAME##_ri(&BASECLASSNAME::_##BASECLASSNAME##_ri, #CLASSNAME, Create);\
	CObject* CLASSNAME::Create()\
	{\
		return new CLASSNAME;\
	}\
	const _RuntimeInfo* CLASSNAME::GetRuntimeInfo()\
	{\
		return &_##CLASSNAME##_ri;\
	}


/****************************************************************************************************************
 *    Date    : 2017/10/25 10:20
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : Others
 *
 ****************************************************************************************************************/
class A : public CObject
{
	_DECLARE_DYNAMIC_INFO(A)
public:
	virtual void PrintfInfo() { printf("This is a class of A"); }
};
_IMPLEMENT_DYNAMIC_INFO(A, CObject)

class B : public A
{
	_DECLARE_DYNAMIC_INFO(B)
public:
	virtual void PrintfInfo() { printf("This is a class of B"); }
};
_IMPLEMENT_DYNAMIC_INFO(B, A)

class C : public CObject
{
	_DECLARE_DYNAMIC_INFO(C)
public:
	virtual void PrintfInfo() { printf("This is a class of C"); }
};
_IMPLEMENT_DYNAMIC_INFO(C, CObject)


/****************************************************************************************************************
 *    Date    : 2017/10/25 10:37
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : Test
 *
 ****************************************************************************************************************/
int main()
{
	//��̬���ʹ���
	const _RuntimeInfo* pRuntimeInfo = _RUNTIMEINFO(B);
	CObject* pObject = pRuntimeInfo->CreateObject(); 
	pObject->PrintfInfo();

	//��̬����ʶ��
	bool res1 = pObject->IsChildOf(_RUNTIMEINFO(CObject));
	bool res2 = pObject->IsChildOf(_RUNTIMEINFO(A));
	bool res3 = pObject->IsChildOf(_RUNTIMEINFO(C));

	delete pObject;

	getchar();
	return 0;
}