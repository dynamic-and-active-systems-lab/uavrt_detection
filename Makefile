all:
	rm -f uavrt_detection
	rm -f *.o
	rm -f codegen/exe/uavrt_detection/*.o
	make -f matlab-coder-utils/Makefile PRODUCT_NAME=uavrt_detection -j4
