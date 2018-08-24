FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y apt-utils
RUN apt-get install -y git
RUN apt-get install -y cmake
RUN apt-get install -y clang
RUN apt-get install -y vim

ADD external/radcli/radcli-1.2.10.tar.gz /radcli_lib

WORKDIR /radcli_lib/radcli-1.2.10

RUN ["/bin/bash", "./configure"]
RUN make VERBOSE=1
RUN make VERBOSE=1 install
RUN ldconfig

WORKDIR /ag-radius

