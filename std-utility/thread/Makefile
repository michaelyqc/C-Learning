test:thread spawning_thread get_thread_id joinable_thread thread_sleep thread_yield

thread:thread.cpp
		g++ -std=c++11 -pthread -o thread thread.cpp 

spawning_thread:spawning_thread.cpp
		g++ -std=c++11 -pthread -o spawning_thread spawning_thread.cpp 

get_thread_id:get_thread_id.cpp
		g++ -std=c++11 -pthread -o get_thread_id get_thread_id.cpp 

joinable_thread:joinable_thread.cpp
		g++ -std=c++11 -pthread -o joinable_thread joinable_thread.cpp 

thread_sleep:thread_sleep.cpp
		g++ -std=c++11 -pthread -o thread_sleep thread_sleep.cpp 

thread_yield:thread_yield.c
		g++ -std=c11 -pthread -o thread_yield thread_yield.c


clean:
		rm -f thread spawning_thread get_thread_id joinable_thread thread_sleep thread_yield
