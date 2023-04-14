BUILD_DIR := build
SRC_DIR := $(filter-out src/tensor_private.h, $(wildcard src/*))
EXAMPLES_DIR := $(wildcard examples/*)
TESTS_DIR := $(filter-out tests/test.h, $(wildcard tests/*))

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
	@echo run tests
	@${BUILD_DIR}/tests/tensor/test_tensor 
	@${BUILD_DIR}/tests/string/test_string
	@${BUILD_DIR}/tests/math/test_math

$(SRC_DIR): dependencies mkdir
	@echo make src $(notdir $@)
	@make -C ${BUILD_DIR}/$@

$(EXAMPLES_DIR): dependencies mkdir
	@echo make examples $(notdir $@)
	@make -C ${BUILD_DIR}/$@


$(TESTS_DIR): dependencies mkdir
	@echo make tests $(notdir $@)
	@make -C ${BUILD_DIR}/$@

mkdir:
	@echo mkdir ${BUILD_DIR}
	@install -d ${BUILD_DIR}

clean:
	@echo clean
	@rm -fr $(BUILD_DIR)

dependencies:
	@test -f "${CMAKE}" && test -x "${CMAKE}"  || (echo "Missing cmake binary" && exit 1)
