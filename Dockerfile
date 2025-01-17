# Use GCC official image
FROM gcc:11

COPY ./src ./usr/src/api

WORKDIR ./usr/src/api

# Create objects folder used by the makefile
RUN mkdir -p build/json
RUN mkdir build/server
RUN mkdir build/utility

RUN make

CMD ["./main.g"]