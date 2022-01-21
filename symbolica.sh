#!/usr/bin/env sh
set -e

CODEGEN=1 CXXFLAGS="-fno-threadsafe-statics" PATH="$(eval echo ~/.symbolica/bin):$PATH" make OBJCACHE= OPT_GLOBAL=-O0 OPT_FAST=-O0 OPT_SLOW=-O0 SIMULATOR=verilator sim
find hardware/simulation/verilator/obj_dir -name "*.o.bc" -print0 | xargs -0 ~/.symbolica/bin/libcxx-link -o symbolica.bc
