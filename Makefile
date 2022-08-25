#
#
#

.PHONY: configure clean

BUILD_DIR=build/

configure:
	@echo "configuring..."
	@cmake \
		-S. \
		-B${BUILD_DIR} \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

clean:
	@rm -rf ${BUILD_DIR}/
	@mkdir ${BUILD_DIR}
	@echo "clean finished."
