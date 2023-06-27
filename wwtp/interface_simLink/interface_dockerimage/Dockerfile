FROM gcc:13.1
COPY ./test /usr/src/test
WORKDIR /usr/src/test
RUN g++ simlink.cpp -o simlink -pthread
