all: 
		g++ -std=c++11 -o test_lambda test_lambda.cpp 
		g++ -std=c++11 -pthread -o package_task package_task.cpp 
		g++ -std=c++11 -pthread -o mem_fn mem_fn.cpp 
		g++ -std=c++11 -pthread -o std_bind std_bind.cpp 
		g++ -std=c++11 -pthread -o std_function std_function.cpp 


clean:
		rm -rf test_lambda package_task mem_fn std_bind std_function
