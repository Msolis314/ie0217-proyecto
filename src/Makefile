CXX := g++
CXXFLAGS := -std=c++11 -Wall -g
LDFLAGS := -L/usr/lib
LDLIBS := -lsqlite3 -lssl -lcrypto

all: main.exe

main.exe: main.o db.o menu.o banco.o tools.o entidadBancaria.o cliente.o transaciones.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

db.o: db.cpp
	$(CXX) $(CXXFLAGS) -c $<

menu.o: menu.cpp
	$(CXX) $(CXXFLAGS) -c $<

banco.o: banco.cpp
	$(CXX) $(CXXFLAGS) -c $<

tools.o: tools.cpp
	$(CXX) $(CXXFLAGS) -c $<

entidadBancaria.o: entidadBancaria.cpp
	$(CXX) $(CXXFLAGS) -c $<

client.o: cliente.cpp
	$(CXX) $(CXXFLAGS) -c $<

transaciones.o: transaciones.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o main.exe


