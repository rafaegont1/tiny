CXX=gcc
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=tinyi
OBJS=src/tinyi.o \
		src/lexical/Lexeme.o \
		src/lexical/LexicalAnalysis.o \
		src/lexical/SymbolTable.o \
		src/lexical/TokenType.o \
		src/syntatic/SyntaticAnalysis.o \
		src/interpreter/util/Memory.o \
		src/interpreter/expr/expr.o \
		src/interpreter/command/block.o \
		src/interpreter/command/command.o \
		src/map/map.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

src/tinyi.o: src/lexical/LexicalAnalysis.h src/syntatic/SyntaticAnalysis.h src/interpreter/command/command.h

src/lexical/SymbolTable.o: src/lexical/TokenType.h

src/lexical/Lexeme.o: src/lexical/Lexeme.h

src/lexical/LexicalAnalysis.o: src/lexical/LexicalAnalysis.h src/lexical/Lexeme.h src/lexical/SymbolTable.h src/map/map.h

src/lexical/TokenType.o: src/lexical/TokenType.h

src/syntatic/SyntaticAnalysis.o: src/syntatic/SyntaticAnalysis.h src/interpreter/expr/*.h src/interpreter/command/*.h

src/interpreter/util/Memory.o: src/interpreter/util/Memory.h

src/interpreter/expr/expr.o: src/interpreter/expr/expr.h

src/interpreter/command/block.o: src/interpreter/command/block.h src/interpreter/command/command.h

src/interpreter/command/command.o: src/interpreter/command/command.h src/interpreter/expr/expr.h

src/map/map.o: src/map/map.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
