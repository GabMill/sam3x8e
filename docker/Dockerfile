# Dockerfile — sam3x8e cross-compiler build environment
# Builds arm-none-eabi GCC + Binutils from source for a reproducible toolchain.

ARG BINUTILS_VERSION=2.46.0
ARG GCC_VERSION=16.1.0

FROM debian:latest

ARG BINUTILS_VERSION
ARG GCC_VERSION

RUN set -x \
        && apt-get update \
        && apt-get upgrade -y \
        && apt-get install -y --no-install-recommends \
                ca-certificates wget gcc libgmp3-dev libmpfr-dev libisl-dev libmpc-dev \
                texinfo bison flex make bzip2 patch build-essential bear

# Download source tarballs in a separate layer so Docker can cache them independently
RUN set -x \
        && mkdir -p /usr/local/src \
        && cd /usr/local/src \
        && wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz \
        && wget -q https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz \
        && tar zxf binutils-${BINUTILS_VERSION}.tar.gz \
        && tar zxf gcc-${GCC_VERSION}.tar.gz \
        && rm binutils-${BINUTILS_VERSION}.tar.gz gcc-${GCC_VERSION}.tar.gz \
        && chown -R root:root binutils-${BINUTILS_VERSION} gcc-${GCC_VERSION} \
        && chmod -R o-w,g+w binutils-${BINUTILS_VERSION} gcc-${GCC_VERSION}

COPY docker/src/ /usr/local/src/

RUN set -x \
        && cd /usr/local/src \
        && bash build-binutils.sh ${BINUTILS_VERSION} \
        && bash build-gcc.sh ${GCC_VERSION}

VOLUME /root/env
WORKDIR /root/env
