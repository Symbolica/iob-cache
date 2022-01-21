#!/usr/bin/env sh
set -e

PATH="$(eval echo ~/.symbolica/bin):$PATH" \
CODEGEN=1 CC=~/.symbolica/bin/cc CFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC" CXX=~/.symbolica/bin/cxx CXXFLAGS="-O0 -Xclang -disable-O0-optnone -fPIC -fno-threadsafe-statics" \
make OBJCACHE= OPT_GLOBAL=-O0 OPT_FAST=-O0 OPT_SLOW=-O0 SIMULATOR=verilator sim
find hardware/simulation/verilator/obj_dir -name "*.o.bc" -print0 | xargs -0 ~/.symbolica/bin/libcxx-link -o symbolica.bc
