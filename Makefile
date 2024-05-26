# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = mini_projet
SRC = mini_projet.c

# Cible par defaut
all : $(TARGET)

# Regle pour construire l'executable cible
$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regle pour nettoyer les fichiers de construction
clean :
	rm -f $(TARGET)

# Regle pour executer le programme
run : $(TARGET)
	./$(TARGET)

.PHONY : all clean run
