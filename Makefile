LIBS=./lib
# Uncomment the line below for 32-bit
# LIBS=./lib32

weather: weather.o
	clang++ -L $(LIBS) weather.o -o weather -Wall && ./weather 95603
	
weather.o: weather.c
	clang -c weather.c -Wall

clean:
	rm -f *.o weather
