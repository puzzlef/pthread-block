#!/usr/bin/env bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --mem=30gb
#SBATCH --job-name slurm
#SBATCH --output=slurm.out
# source scl_source enable gcc-toolset-11
# module load hpcx-2.7.0/hpcx-ompi
# module load openmpi/4.1.5
src="pagerank-barrierfree-mpi-dynamic"
out="$HOME/Logs/$src$1.log"
if [[ "$1" == "-mpi" ]]; then
  module load hpcx-2.7.0/hpcx-ompi
fi
ulimit -s unlimited
printf "" > "$out"

# Download program
if [[ "$DOWNLOAD" != "0" ]]; then
  rm -rf $src
  git clone https://github.com/puzzlef/$src
fi
cd $src

# Fixed config
: "${MAX_THREADS:=32}"
: "${ENABLED_MPI:=0}"
if [[ "$1" == "-mpi" ]]; then
  ENABLED_MPI="1"
fi
# Define macros (dont forget to add here)
DEFINES=(""
"-DMAX_THREADS=$MAX_THREADS"
"-DENABLED_MPI=$ENABLED_MPI"
)

# Run
if [[ "$1" == "-mpi" ]]; then
  GCC="mpic++"
  RUN="mpirun -np $SLURM_NTASKS --map-by node --bind-to none --report-bindings"
else
  GCC="g++"
  RUN=""
fi
$GCC ${DEFINES[*]} -std=c++17 -O3 -fopenmp main.cxx -o "a$1.out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/soc-Epinions1.mtx   2>&1 | tee -a "$out"
stdbuf --output=L $RUN ./"a$1.out" ~/Data/indochina-2004.mtx  2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/uk-2002.mtx         2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/arabic-2005.mtx     2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/uk-2005.mtx         2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/webbase-2001.mtx    2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/it-2004.mtx         2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/sk-2005.mtx         2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/com-LiveJournal.mtx 2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/com-Orkut.mtx       2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/asia_osm.mtx        2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/europe_osm.mtx      2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/kmer_A2a.mtx        2>&1 | tee -a "$out"
# stdbuf --output=L $RUN ./"a$1.out" ~/Data/kmer_V1r.mtx        2>&1 | tee -a "$out"
