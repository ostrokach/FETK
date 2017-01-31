#!/bin/bash

# # We need at least the following XOrg libraries:
# libSM.so.6 => /usr/lib/x86_64-linux-gnu/libSM.so.6 (0x00007f6f11a61000)
# libICE.so.6 => /usr/lib/x86_64-linux-gnu/libICE.so.6 (0x00007f6f11847000)
# libXaw.so.7 => /usr/lib/x86_64-linux-gnu/libXaw.so.7 (0x00007f6f115d2000)
# libXmu.so.6 => /usr/lib/x86_64-linux-gnu/libXmu.so.6 (0x00007f6f113b9000)
# libXi.so.6 => /usr/lib/x86_64-linux-gnu/libXi.so.6 (0x00007f6f111a9000)
# libXt.so.6 => /usr/lib/x86_64-linux-gnu/libXt.so.6 (0x00007f6f10f3f000)
# libXext.so.6 => /usr/lib/x86_64-linux-gnu/libXext.so.6 (0x00007f6f10d2d000)
# libX11.so.6 => /usr/lib/x86_64-linux-gnu/libX11.so.6 (0x00007f6f109f3000)
# libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f6f106e9000)
# libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f6f10320000)
# libuuid.so.1 => /home/kimlab1/strokach/anaconda/bin/../lib/libuuid.so.1 (0x00007f6f1011d000)
# libXpm.so.4 => /usr/lib/x86_64-linux-gnu/libXpm.so.4 (0x00007f6f0ff0b000)
# libxcb.so.1 => /usr/lib/x86_64-linux-gnu/libxcb.so.1 (0x00007f6f0fce9000)
# libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f6f0fae4000)
# /lib64/ld-linux-x86-64.so.2 (0x000055cc55286000)
# libXau.so.6 => /usr/lib/x86_64-linux-gnu/libXau.so.6 (0x00007f6f0f8e0000)
# libXdmcp.so.6 => /usr/lib/x86_64-linux-gnu/libXdmcp.so.6 (0x00007f6f0f6da000)

yum install -y libX* mesa-libGL-devel mesa-libGLU-devel mesa-libGLw-devel

# export FETK_LIBRARY=$PREFIX/lib
# export FETK_INCLUDE=$PREFIX/include

echo 'y' | ./fetk-build all

mkdir -p "${PREFIX}/bin" "${PREFIX}/lib" "${PREFIX}/include"

cp -r build/x86_64-unknown-linux-gnu/bin/* "${PREFIX}/bin/"
cp -r build/x86_64-unknown-linux-gnu/lib/* "${PREFIX}/lib/"
cp -r build/x86_64-unknown-linux-gnu/include/* "${PREFIX}/include/"
