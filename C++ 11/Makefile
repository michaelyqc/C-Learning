test:left_value_and_right_value move_or_forword functor_object counter_thread weak_ptr shared_ptr unique_ptr

left_value_and_right_value:left_value_and_right_value.cpp
		g++  -std=c++11  -o left_value_and_right_value left_value_and_right_value.cpp

move_or_forword:move_or_forword.cpp
		g++  -std=c++11  -o move_or_forword move_or_forword.cpp

weak_ptr:weak_ptr.cpp
		g++  -std=c++11  -o weak_ptr weak_ptr.cpp

unique_ptr:unique_ptr.cpp
		g++  -std=c++11 -pthread -o unique_ptr unique_ptr.cpp

shared_ptr:shared_ptr.cpp
		g++  -std=c++11 -pthread -o shared_ptr shared_ptr.cpp

functor_object:functor_object.cpp
		g++  -std=c++11 -pthread  -o functor_object functor_object.cpp

counter_thread:counter_thread.cpp
		g++  -std=c++11 -pthread  -o counter_thread counter_thread.cpp

clean:
		rm -f left_value_and_right_value move_or_forword functor_object counter_thread weak_ptr shared_ptr unique_ptr
