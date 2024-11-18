mkdir -p /share/suh-scrap2/ph448/EzPC/tmpdir
export TMPDIR=/share/suh-scrap2/ph448/EzPC/tmpdir

# Set environment variables
export NVCC_PATH="$CONDA_PREFIX/bin/nvcc"
export CUDA_VERSION=11.7  # Update based on your CUDA version
export GPU_ARCH=86        # Update based on your GPU architecture

# # echo "Updating submodules"
# git submodule update --init --recursive

# # # Install dependencies via Conda
# echo "Installing g++-9"
# conda install -c conda-forge gxx_linux-64=9

# # echo "Installing other dependencies"
# conda install -c conda-forge gmp openssl cmake=3.27 gmp mpfr eigen

# # # Install Python dependencies via Conda
# # conda install -c conda-forge python=3.8 pip
# # conda install -c conda-forge matplotlib

# # Install CUTLASS
# echo "Building CUTLASS"
# cd ext/cutlass
# git stash
# if [ -n "$1" ]; then 
#     git checkout $1
# fi
# mkdir -p build && cd build
# cmake .. -DCUTLASS_NVCC_ARCHS=$GPU_ARCH -DCMAKE_CUDA_COMPILER_WORKS=1 -DCMAKE_CUDA_COMPILER=$NVCC_PATH -DCMAKE_CUDA_ARCHITECTURES=86
# ranlib /share/suh-scrap2/ph448/EzPC/GPU-MPC/ext/cutlass/build/lib/libgtest.a 
# make -j
# cd ../../..

# # Build Sytorch
# echo "Building Sytorch"
# cd ext/sytorch
# mkdir -p build && cd build
# cmake -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Release ../ -DCUDAToolkit_ROOT="$CONDA_PREFIX"
# make sytorch -j
# cd ../../..

# # Download CIFAR-10 dataset
# cd experiments/orca/datasets/cifar-10
# sh download-cifar10.sh
# cd ../../../..

# Make shares of data
make share_data
cd experiments/orca
./share_data
cd ../..


# Set up output directories
echo "Setting up output directories"
mkdir -p experiments/orca/output/P0/training
mkdir -p experiments/orca/output/P1/training
mkdir -p experiments/orca/output/P0/inference
mkdir -p experiments/orca/output/P1/inference
mkdir -p experiments/sigma/output/P0
mkdir -p experiments/sigma/output/P1

# Install matplotlib (if not already installed)
pip install matplotlib  # Conda-installed pip should not require sudo
