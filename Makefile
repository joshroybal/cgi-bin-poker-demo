poker.cgi: driver.o poker.o
	g++ -static -s -o poker.cgi driver.o poker.o
	
driver.o: driver.cpp
	g++ -O2 -c driver.cpp
	
poker.o: poker.cpp poker.hpp
	g++ -O2 -c poker.cpp
	
install:
	sudo cp poker.cgi /srv/httpd/cgi-bin
	sudo chown apache:apache /srv/httpd/cgi-bin/poker.cgi
	
clean:
	rm poker.cgi && rm *.o
