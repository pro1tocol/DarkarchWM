CXX := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS := -lstdc++fs

SRC := src
BIN := bin
SRCS := $(wildcard $(SRC)/*.cpp)
TARGETS := $(BIN)/boot \
           $(BIN)/fcitx5_build \
           $(BIN)/initramfs \
           $(BIN)/install \
           $(BIN)/sources \
           $(BIN)/sshd_build \
           $(BIN)/zsh_build
all: $(TARGETS)
$(BIN)/%: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
$(BIN)/fcitx5_build: $(SRC)/fcitx5.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
$(BIN)/sshd_build: $(SRC)/sshd.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
$(BIN)/zsh_build: $(SRC)/zsh.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
clean:
	rm -rf $(BIN)/*

.PHONY: all clean
