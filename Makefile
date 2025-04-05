CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = htc

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) -lstdc++ -lcrypto

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
