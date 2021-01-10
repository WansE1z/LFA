CC = g++
CFLAGS = -Wall -Wextra -g -O3
EXEC = Glypho
SRC = GlyphoError.cpp GlyphoInterpreter.cpp Main.cpp GlyphoReader.cpp GlyphoStack.cpp
OBJ = $(SRC:.cpp=.o)

build: $(OBJ)
	@$(CC) -o $(EXEC) $^ $(CFLAGS) 
	-@rm -f *.o 
	
run: 
	@./$(EXEC) $(input) $(base) 
	
%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	