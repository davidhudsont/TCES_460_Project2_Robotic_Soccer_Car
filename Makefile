schedule: simple_continous_client.cpp simple_continous_server.cpp wiringPiSerial.cpp
#	gcc -o server server.c
#	gcc -o client client.c
#	gcc -o continous_client continous_client.c
#	gcc -o continous_server continous_server.c
	g++ -o client simple_continous_client.cpp
	g++ -o server simple_continous_server.cpp
	g++ -o serial wiringPiSerial.cpp -lwiringPi
