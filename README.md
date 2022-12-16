# Supercomputing

How to run:
* Load libraries 
  ```sh
  source /usr/local/sbin/modules.sh
  module load OpenMPI/4.1.2-GCC-11.2.0
  module load FFmpeg/4.3.2-GCCcore-11.2.0
  ```
* Create program
  ```sh
  make
  ```
* Run script with path to video and amount of processors (if needed run 'chmod +x run.sh')
  ```sh
  ./run /path/to/video (e.g. ./run data/20221031_155122.mp4 4)
  ```
