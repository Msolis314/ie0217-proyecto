CXX := g++
CXXFLAGS := -std=c++11 -Wall -g
LDFLAGS := -L/usr/lib
LDLIBS := -lsqlite3 -lssl -lcrypto

# Source
SRCDIR := src



# Output 
OUTDIR := bin

#Crear directorio bin si no existe
$(shell mkdir -p $(OUTDIR))

SRCS := $(wildcard $(SRCDIR)/*.cpp)


OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OUTDIR)/%.o)

all: $(OUTDIR)/main.exe

$(OUTDIR)/main.exe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Target para correr el programa
run: $(OUTDIR)/main.exe
	./$(OUTDIR)/main.exe

#Target para instalar las dependencias
install:
	chmod +x install.sh
	./install.sh

clean:
	rm -f $(OUTDIR)/*.o $(OUTDIR)/main.exe

