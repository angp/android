export ARCH_FLAGS=-march=armv7-a -mtune=cortex-a9 -mfloat-abi=softfp -mfpu=neon
export HOST=arm-linux-androideabi
export SYSROOT=$(TOOLCHAIN)/sysroot
export CROSSTOOLS=$(TOOLCHAIN)/bin/arm-linux-androideabi-
export LD=$(CROSSTOOLS)ld
export CC=$(CROSSTOOLS)gcc
export CXX=$(CROSSTOOLS)g++
export AR=$(CROSSTOOLS)ar
export AS=$(CROSSTOOLS)as
export NM=$(CROSSTOOLS)nm
export STRIP=$(CROSSTOOLS)strip
export RANLIB=$(CROSSTOOLS)ranlib
export OBJDUMP=$(CROSSTOOLS)objdump
export CFLAGS=$(ARCH_FLAGS) -I$(XBMCPREFIX)/include
export LDFLAGS=$(ARCH_FLAGS) -L$(XBMCPREFIX)/lib
export CPPFLAGS=$(CFLAGS)
export CXXFLAGS=$(CFLAGS)
export LIBS=-lstdc++
export PKG_CONFIG_PATH=$(XBMCPREFIX)/lib/pkgconfig
export PATH:=${XBMCPREFIX}/bin:${TOOLCHAIN}/bin:$(PATH)
export PREFIX=$(XBMCPREFIX)