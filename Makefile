CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = hTorrentCreator
BINDIR ?= /usr/local/bin

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) -lstdc++ -lcrypto -s -O2

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

install: $(OUTPUT)
	mkdir -p $(BINDIR)
	cp $(OUTPUT) $(BINDIR)
	ln -snf $(OUTPUT) $(BINDIR)/htc
	ln -snf $(OUTPUT) $(BINDIR)/htorrentcreator

uninstall:
	rm -f $(BINDIR)/$(OUTPUT)
	rm -f $(BINDIR)/htc
	rm -f $(BINDIR)/htorrentcreator
