CUDA_VERSION ?= $(value CUDA_VERSION)
ifeq ($(CUDA_VERSION),)
	CUDA_VERSION = 11.7
endif

CXX=$(CONDA_PREFIX)/bin/nvcc

make: try.o
	g++ -o gpu_monitor try.cpp -lnvidia-ml -pthread