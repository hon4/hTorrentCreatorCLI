CC = gcc
SRC = src/hTorrentCreatorCLI.cpp
OUTPUT = hTorrentCreator
BINDIR ?= /usr/local/bin

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) -lstdc++ -lcrypto -s -O3

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

install: $(OUTPUT)
	mkdir -p $(BINDIR)
	cp hTorrentCreator $(BINDIR)
	ln -snf $(BINDIR)/hTorrentCreator $(BINDIR)/htc
	ln -snf $(BINDIR)/hTorrentCreator $(BINDIR)/htorrentcreator

uninstall: $(OUTPUT)
	rm -f $(BINDIR)/hTorrentCreator
	rm -f $(BINDIR)/htc
