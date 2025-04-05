CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = htorrentcreatorcli

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) -lstdc++ -lcrypto

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
