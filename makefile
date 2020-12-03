

main: sensor.cpp
	 g++ -o sensor -Llib -lpapi -std=c++11 sensor.cpp
perf: perf_sensor.cpp
	 g++ -o perf_sensor -std=c++11 perf_sensor.cpp