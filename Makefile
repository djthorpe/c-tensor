BUILD_DIR := build

# Paths to tools needed in dependencies
CMAKE := $(shell which cmake)

# Targets
all: config

config: dependencies mkdir
	@echo cmake config
	@${CMAKE} -B ${BUILD_DIR} -D CMAKE_BUILD_TYPE=Debug

test: config
	@echo make all test
	@make -C ${BUILD_DIR} all test

mkdir:
	@echo mkdir ${BUILD_DIR}
	@install -d ${BUILD_DIR}

clean:
	@echo clean
	@rm -fr $(BUILD_DIR)

dependencies:
	@test -f "${CMAKE}" && test -x "${CMAKE}"  || (echo "Missing cmake binary" && exit 1)
