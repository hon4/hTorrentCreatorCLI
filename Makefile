CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = htc
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
	cp htc $(BINDIR)

uninstall: $(OUTPUT)
	rm -f $(BINDIR)/htc
