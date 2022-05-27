#pragma once
#include <vector>
#include "Func.h"

namespace grc
{
	template <typename... ARGS>
	class EventHandler
	{
	private:
		std::vector<grc::Func<void, ARGS...>> list;

	public:
		bool operator+=(void (*function)(ARGS...))
		{
			list.push_back(function);
			return true;
		}

		bool operator+=(grc::Action<ARGS...> function)
		{
			list.push_back(function);
			return true;
		}

		bool operator-=(void (*function)(ARGS...))
		{
			//list.erase()
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == (void*)function)
				{
					list.erase(list.begin() + i, list.begin() + i + 1);
					return true;
				}
			}
			return false;
		}

		bool operator-=(grc::Action<ARGS...> function)
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == (void*)function)
				{
					list.erase(list.begin() + i, list.begin() + i + 1);
					return true;
				}
			}
			return false;
		}

		bool Clear()
		{
			for (auto i : list)
			{
				i = 0;
			}
			return true;
		}

		void BeginInvoke(void (*function)(), const ARGS... arguments) const
		{
			function();
			Invoke(arguments...);
		}
		void EndInvoke(void (*function)(), const ARGS... arguments) const
		{
			Invoke(arguments...);
			function();
		}

		void XInvoke(void (*begin)(), void (*end)()) const
		{
			begin();
			Invoke();
			end();
		}

		void Invoke(const ARGS... arguments) const
		{
			for (auto& i : list)
			{
				if (i != nullptr)
				{
					i(arguments...);
				}
			}
		}
	};
} // namespace Graphics