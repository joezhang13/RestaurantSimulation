proj5.exe: proj5.o RestaurantClass.o EventClass.o random.o input.o
	g++ proj5.o RestaurantClass.o EventClass.o random.o input.o -o proj5.exe

proj5.o: proj5.cpp RestaurantClass.h FIFOQueueClass.h SortedListClass.h LinkedNodeClass.h EventClass.h random.h input.h constants.h
	g++ -c proj5.cpp -o proj5.o

RestaurantClass.o: RestaurantClass.cpp RestaurantClass.h FIFOQueueClass.h SortedListClass.h EventClass.h random.h input.h constants.h
	g++ -c RestaurantClass.cpp -o RestaurantClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -c EventClass.cpp -o EventClass.o

input.o: input.cpp input.h constants.h
	g++ -c input.cpp -o input.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

clean:
	rm -f proj5.exe proj5.o RestaurantClass.o EventClass.o input.o random.o
