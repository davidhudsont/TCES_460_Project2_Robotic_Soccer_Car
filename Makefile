schedule: controller_client.cpp car_server.cpp test.cpp
	g++ -o client controller_client.cpp -lwiringPi
	g++ -o server car_server.cpp -lwiringPi
	g++ -o test test.cpp -lwiringPi
