# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    # Comandos Windows
    RM := del /Q
    CP := copy
    MKDIR := if not exist
    EXE := .exe
    PATH_SEP := \\
    SFML_PATH := C:\\Users\\Caio\\Documents\\SFML-2.6.2
else
    DETECTED_OS := Linux
    # Comandos Linux
    RM := rm -f
    CP := cp
    MKDIR := mkdir -p
    EXE :=
    PATH_SEP := /
    SFML_PATH := /usr/include
endif

# Diretórios e arquivos
SRC_DIR = arquivos.cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

.PHONY: all compile link resources clean

all: compile link resources

compile:
ifeq ($(DETECTED_OS),Windows)
	g++ -c $(SOURCES) -I"$(SFML_PATH)\\include" -I"arquivos.h" -g
else
	g++ -c $(SOURCES) -I/usr/include -I"arquivos.h" -g
endif

link:
ifeq ($(DETECTED_OS),Windows)
	g++ $(OBJECTS) -o main$(EXE) -L"$(SFML_PATH)\\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -mconsole -g
else
	g++ $(OBJECTS) -o main$(EXE) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g
endif

resources:
ifeq ($(DETECTED_OS),Windows)
	if not exist "Audios" mkdir "Audios"
	if not exist "Imagens" mkdir "Imagens"
	copy "Audios\*.ogg" "." 2>nul
	copy "Imagens\*.png" "." 2>nul
	copy "Dlls\*.dll" "." 2>nul
else
	mkdir -p Audios Imagens
	cp Audios/*.ogg . 2>/dev/null || true
	cp Imagens/*.png . 2>/dev/null || true
endif

clean:
ifeq ($(DETECTED_OS),Windows)
	@echo Limpando arquivos...
	@del /Q *.o 2>nul
	@del /Q *.exe 2>nul
	@del /Q *.ogg 2>nul
	@del /Q *.png 2>nul
	@del /Q *.dll 2>nul
	@echo Limpeza concluida!
else
	@echo "Limpando arquivos..."
	@rm -f *.o main *.ogg *.png
	@echo "Limpeza concluida!"
endif