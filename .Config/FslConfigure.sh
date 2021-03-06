#!/bin/bash
if [ ! -n "${FSL_PLATFORM_NAME+1}" ]; then
  # Crude platform check, but it works for now.
  if [ -n "${BUILDDIR+1}" ]; then
    export FSL_PLATFORM_NAME=Yocto
  elif [ -n "${SDKTARGETSYSROOT+1}" ]; then
    export FSL_PLATFORM_NAME=Yocto
    if [ -z "${ROOTFS}" ]; then
      export ROOTFS=$SDKTARGETSYSROOT
    fi
  elif [ -n "${QNX_TARGET+1}" ]; then
    export FSL_PLATFORM_NAME=QNX
  else
    export FSL_PLATFORM_NAME=Ubuntu
  fi
fi
echo PlatformName: $FSL_PLATFORM_NAME
