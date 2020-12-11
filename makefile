

main: sensor.cpp
	 icc -O3 -o sensor -Llib -lpapi -std=c++11 sensor.cpp
perf: perf_sensor.cpp
	 icc -O3 -o perf_sensor -std=c++11 perf_sensor.cpp
all: main perf