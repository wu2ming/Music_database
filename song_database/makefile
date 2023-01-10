CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

database_test: database.o database_menu.o song.o main.o 
	g++ -o database_test database.o database_menu.o song.o main.o 

database:
	g++ -c $(CPPFLAGS) database.cpp
	
database_menu:
	g++ -c $(CPPFLAGS) database_menu.cpp

song:
	g++ -c $(CPPFLAGS) song.cpp	

main:
	g++ -c $(CPPFLAGS) main.cpp


clean:
	rm -f database_test database.o database_menu.o song.o main.o 