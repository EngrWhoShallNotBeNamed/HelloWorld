# ------------------------------------------------------------------------------
# The image we are building with THIS Dockerfile is based on the ubuntu:18.04
# Docker image from dockerhub (hub.docker.com).
# ------------------------------------------------------------------------------
FROM ubuntu:18.04

# ------------------------------------------------------------------------------
# Install Trick Dependencies identified at
# https://nasa.github.io/trick/documentation/install_guide/Install-Guide#ubuntu
# ------------------------------------------------------------------------------
ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && apt-get install -y \
bison \
clang \
flex \
git \
llvm \
make \
maven \
swig \
cmake \
curl \
g++ \
libx11-dev \
libxml2-dev \
libxt-dev \
libmotif-common \
libmotif-dev \
python3-dev \
python3-pip \
zlib1g-dev \
llvm-dev \
libclang-dev \
libudunits2-dev \
libgtest-dev \
openjdk-11-jdk \
zip \
sudo \
vim \
gitk

ENV PYTHON_VERSION=3

# Install user packages outside of Trick
RUN python3 -m pip install ipython

