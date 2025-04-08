CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = hTorrentCreator
BINDIR ?= /usr/local/bin

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) -lstdc++ -lcrypto

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

install: $(OUTPUT)
	mkdir -p $(BINDIR)
	cp hTorrentCreator $(BINDIR)

uninstall: $(OUTPUT)
	rm -f $(BINDIR)/hTorrentCreator
