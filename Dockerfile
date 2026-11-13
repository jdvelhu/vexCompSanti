# Use a stable Debian/Ubuntu base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools, make, and the ARM GNU toolchain for cross-compilation
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-arm-none-eabi \
    gdb-arm-none-eabi \
    make \
    git \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /workspace

# Copy your project source files (including your source files, Makefile, and vex.h) into the container
COPY . /workspace

# Default command to run when the container starts (e.g., building with make)
CMD ["make"]
