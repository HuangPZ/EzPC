conda install -c conda-forge cudatoolkit=11.7 cudatoolkit-dev
sudo apt-get install nvidia-driver-515
MINICONDA_DIR=~/miniconda3
mkdir -p $MINICONDA_DIR
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O $MINICONDA_DIR/miniconda.sh
bash $MINICONDA_DIR/miniconda.sh -b -u -p $MINICONDA_DIR
rm $MINICONDA_DIR/miniconda.sh



MINICONDA_DIR=~/miniconda3
source $MINICONDA_DIR/bin/activate
conda activate cuda
export LD_LIBRARY_PATH=/home/cc/miniconda3/envs/cuda/lib64:$LD_LIBRARY_PATH