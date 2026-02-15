CXX := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS := -lstdc++fs

SRC := src
BIN := bin
SRCS := $(wildcard $(SRC)/*.cpp)
TARGETS := $(BIN)/boot \
           $(BIN)/fcitx5 \
           $(BIN)/initramfs \
           $(BIN)/install \
           $(BIN)/sources \
           $(BIN)/sshd \
           $(BIN)/zsh
all: $(TARGETS)
$(BIN)/%: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BIN)/*

.PHONY: all clean
