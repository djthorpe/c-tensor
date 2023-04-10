BUILD_DIR := build
SRC_DIR := $(wildcard src/*)
EXAMPLES_DIR := $(wildcard examples/*)
TESTS_DIR := $(wildcard test/*)

# Paths to tools needed in dependencies
CMAKE := $(shell which cmake)

# Targets
all: config src tests examples

config: dependencies mkdir
	@echo cmake config
	@${CMAKE} -B ${BUILD_DIR}

src: $(SRC_DIR)

examples: $(EXAMPLES_DIR)

tests: $(TESTS_DIR)

$(SRC_DIR): dependencies mkdir
	@echo make src $(notdir $@)
	@make -C ${BUILD_DIR}/$@

$(EXAMPLES_DIR): dependencies mkdir
	@echo make examples $(notdir $@)
	@make -C ${BUILD_DIR}/$@


$(TESTS_DIR): dependencies mkdir
	@echo make tests $(notdir $@)
	@make -C ${BUILD_DIR}/$@
# Run the tests
	@${BUILD_DIR}/test/tensor/test_tensor 

mkdir:
	@echo mkdir ${BUILD_DIR}
	@install -d ${BUILD_DIR}

clean:
	@echo clean
	@rm -fr $(BUILD_DIR)

dependencies:
	@test -f "${CMAKE}" && test -x "${CMAKE}"  || (echo "Missing cmake binary" && exit 1)
