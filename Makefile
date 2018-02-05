schedule: car_client.cpp controller_server.cpp
	g++ -o client car_client.cpp
	g++ -o server controller_server.cpp
	#g++ -o serial wiringPiSerial.cpp -lwiringPi
