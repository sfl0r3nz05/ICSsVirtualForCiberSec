FROM ubuntu
# ...
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && \
    apt-get -y install python && \
    apt-get -y install libpcap-dev &&\
    apt-get -y install hping3 &&\
    rm -rf /var/lib/apt/lists/*