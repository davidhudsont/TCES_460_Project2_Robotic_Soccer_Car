schedule: controller_client.cpp car_server.cpp
	g++ -o client controller_client.cpp -lwiringPi
	g++ -o server car_server.cpp
	#g++ -o serial wiringPiSerial.cpp -lwiringPi
