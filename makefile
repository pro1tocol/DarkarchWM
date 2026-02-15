CXX := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS := -lstdc++fs
SRC := src
BIN := bin

CORES := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
MAKEFLAGS += -j$(CORES)
SRCS := $(wildcard $(SRC)/*.cpp)
TARGETS := $(BIN)/boot \
           $(BIN)/initramfs \
           $(BIN)/install \
           $(BIN)/sources \
           $(BIN)/fcitx5_build \
           $(BIN)/sshd_build \
           $(BIN)/zsh_build
all: $(TARGETS)
	chmod +x $(TARGETS)
COMPILE_CMD = @mkdir -p $(BIN) && $(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
$(BIN)/%: $(SRC)/%.cpp
	$(COMPILE_CMD)
$(BIN)/fcitx5_build: $(SRC)/fcitx5.cpp
	$(COMPILE_CMD)
$(BIN)/sshd_build: $(SRC)/sshd.cpp
	$(COMPILE_CMD)
$(BIN)/zsh_build: $(SRC)/zsh.cpp
	$(COMPILE_CMD)
clean:
	rm -rf $(BIN)/*

.PHONY: all clean
