BUILD_DIR := build
SRC_DIR := $(wildcard src/*)
EXAMPLES_DIR := $(wildcard examples/*)

# Paths to tools needed in dependencies
CMAKE := $(shell which cmake)

# Targets
all: config src examples

config: dependencies mkdir
	@echo cmake config
	@${CMAKE} -B ${BUILD_DIR}

src: $(SRC_DIR)

examples: $(EXAMPLES_DIR)

$(SRC_DIR): dependencies mkdir
	@echo make $(notdir $@)
	@make -C ${BUILD_DIR}/$@

$(EXAMPLES_DIR): dependencies mkdir
	@echo make $(notdir $@)
	@make -C ${BUILD_DIR}/$@

mkdir:
	@echo mkdir ${BUILD_DIR}
	@install -d ${BUILD_DIR}

clean:
	@echo clean
	@rm -fr $(BUILD_DIR)

dependencies:
	@test -f "${CMAKE}" && test -x "${CMAKE}"  || (echo "Missing cmake binary" && exit 1)
