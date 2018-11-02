test:add_people list_people

add_people:add_person.cpp protoMid
		c++  add_person.cpp person.pb.cc -o add_people `pkg-config --cflags --libs protobuf`

list_people: list_person.cpp protoMid   
		c++  list_person.cpp person.pb.cc -o list_people `pkg-config --cflags --libs protobuf`  

protoMid: person.proto
		protoc -I=. --cpp_out=. ./person.proto

clean:
		rm -f add_people list_people protoMid
		rm -f person.pb.cc person.pb.h
