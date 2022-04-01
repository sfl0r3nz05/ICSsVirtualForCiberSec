FROM ubuntu
# ...
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && \
    apt-get -y install gcc g++ mono-mcs && \
    rm -rf /var/lib/apt/lists/*