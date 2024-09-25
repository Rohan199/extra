# .gitpod.Dockerfile
FROM gitpod/workspace-full

# Install necessary packages
USER root

RUN apt-get update && \
    apt-get install -y \
        cmake \
        build-essential \
        libgtest-dev

# Build and install Google Test
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

USER gitpod
