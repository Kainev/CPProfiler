#include <iostream>
#include <chrono>

#define profile_scope(name) CPProfiler::ScopeProfiler cpp_scope_profiler##__LINE__(name);
#define start_profile_block(name) { CPProfiler::ScopeProfiler cpp_scope_profiler##__LINE__(name);
#define end_profile_block }

namespace CPProfiler
{
	class Timer
	{
	public:
		void start() { m_start_time = std::chrono::high_resolution_clock::now(); }
		
		template<typename T = std::chrono::microseconds>
		double elapsed_time() { return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_start_time).count(); }

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_start_time;
	};

	class ScopeProfiler
	{
	public:
		ScopeProfiler(const char* name) : m_name(name) { timer.start(); }
		~ScopeProfiler()
		{
			print_elapsed_time();
		}

		void print_elapsed_time()
		{
			using namespace std::chrono;
			std::cout << m_name << "::Duration: " << timer.elapsed_time() << "us" << std::endl;
		}


	private:
		const char* m_name;
		Timer		timer;
	};
}