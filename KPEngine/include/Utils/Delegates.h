#pragma once
#include <vector>
#include <cassert>
#include <algorithm>


namespace KPEngine
{
	namespace Utils
	{
		template<class ... Params>
		class Delegate
		{
		public:
			Delegate() : m_pInstance(nullptr), m_pMethodStub(nullptr)
			{
				
			}
			~Delegate()
			{
				
			}

			bool operator==(const Delegate & i_other)
			{
				return (m_pInstance == i_other.m_pInstance) && (m_pMethodStub == i_other.m_pMethodStub);
			}

			operator bool() const
			{
				return m_pInstance != nullptr;
			}

			
			/// <summary>
			/// Creates a generic delegate holder that calls a method on being invoked. Binds to one function that can be called on invoke
			/// </summary>
			/// <param name="i_pInstance">The i p instance.</param>
			/// <returns></returns>
			template <class T, void (T::*TMethod)(Params ...)>
			static Delegate Create(T* i_pInstance)
			{
				return Delegate(i_pInstance, &method_stub<T, TMethod>);
			}

			void ExecuteIfBound(Params ... i_Parameter) const
			{
				if (m_pInstance)
				{
					assert(m_pMethodStub);
					(*m_pMethodStub)(m_pInstance, i_Parameter ...);
				}
			}
		private:
			typedef void(*tMethodStub)(void * i_pInstance, Params ... i_Parameter);

			void *			m_pInstance;
			tMethodStub		m_pMethodStub;

			explicit Delegate(void * i_pInstance, tMethodStub i_pMethodStub) :
				m_pInstance(i_pInstance),
				m_pMethodStub(i_pMethodStub)
			{
				assert(i_pInstance);
				assert(i_pMethodStub);
			}

			/// <summary>
			/// Stub (Does nothing) method is for holding function pointers. This method is when the stub is called
			/// </summary>
			/// <param name="m_pInstance">The m p instance.</param>
			/// <param name="...i_Parameters">The ...i parameters.</param>
			template <class T, void (T::*TMethod)(Params ...)>
			static void method_stub(void * m_pInstance, Params ... i_Parameters)
			{
				(static_cast<T*>(m_pInstance)->*TMethod)(i_Parameters ...);
			}
		};

		template<class ... Params>
		class MultiCastDelegate
		{
		public:
			void AddDelegate(Delegate<Params ...> & i_Delegate)
			{
				Receivers.push_back(i_Delegate);
			}

			inline MultiCastDelegate& operator+=(Delegate<Params ...> & i_Delegate)
			{
				AddDelegate(i_Delegate);
				return *this;
			}

			void RemoveDelegate(Delegate<Params ...> & i_Delegate)
			{
				Receivers.erase(std::remove_if(Receivers.begin(), Receivers.end(), [&i_Delegate](const Delegate<Params ...> & i_Entry) {return i_Entry == i_Delegate; }),
					Receivers.end());
			}

			inline MultiCastDelegate& operator-=(Delegate<Params ...> & i_Delegate)
			{
				RemoveDelegate(i_Delegate);
				return *this;
			}

			void Invoke(Params ... i_Parameters)
			{
				for (auto Receiver : Receivers)
					Receiver.ExecuteIfBound(i_Parameters ...);
			}
		private:
			std::vector< Delegate<Params ...> > Receivers;
		};
	}
}

