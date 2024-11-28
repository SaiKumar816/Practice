// Employee.cpp : Defines the entry point for the console application.
//


#include<iostream>
#include<memory>
#include<string>
#include<functional>


using namespace std;

/*
	Can you please define your own smart pointer as a generic which reference count of object?
*/

namespace SmartPointer
{
	class Person
	{
		string m_name;
	public:
		Person(string name) :m_name(name)
		{

		}

		string GetName()
		{
			return m_name;
		}
	};

	class RC
	{
		int count;
	public:
		RC() :count(0)
		{}

		int GetCount()
		{
			return count;
		}
		void AddRef()
		{
			count++;
		}
		int Release()
		{
			return --count;
		}
	};

	template<class T>
	class SP
	{
		T* m_Ptr;
		RC* m_refCount;
	public:

		SP(T* pObject = nullptr) :m_Ptr(pObject)
		{
			m_refCount = new RC;
			m_refCount->AddRef();
		}

		T* operator*()
		{
			return m_Ptr;
		}
		T* operator-> ()
		{
			return m_Ptr;
		}

		SP<T>& operator= (const SP<T>& pObject)
		{
			if (this != &pObject)
			{
				m_Ptr = pObject.m_Ptr;
				m_refCount = pObject.m_refCount;

				m_refCount->AddRef();
			}
			return *this;
		}

		int usecount()
		{
			return m_refCount->GetCount();
		}

		SP<T>(const SP<T>& pObject)
		{
			m_Ptr = pObject.m_Ptr;
			m_refCount = pObject.m_refCount;

			m_refCount->AddRef();
		}

		~SP<T>()
		{
			if (m_refCount->Release() == 0)
			{
				delete m_Ptr;
				m_Ptr = nullptr;
				cout << "Heap object destroyed" << endl;
			}
		}
	};

}

///////////////////////////////////////////////////
using namespace SmartPointer;

int main()
{
	SP<Person> pObj1(new Person("Ashok"));
	cout << pObj1->GetName() << endl;

	{
		SP<Person> pObj2;
		pObj2 = pObj1;
		cout << pObj2->GetName() << endl;

		SP<Person> pObj3(pObj1);
		cout << "No.Of objects referred by smart pointer:" << pObj1.usecount() << endl;
	}

	cout << "No.Of objects referred by smart pointer:" << pObj1.usecount() << endl;
	cout << pObj1->GetName() << endl;

	return 0;
}
