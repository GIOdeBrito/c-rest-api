# Use GCC official image
FROM gcc:11

COPY ./src ./usr/src/api

WORKDIR ./usr/src/api

# Create objects folder used by the makefile
RUN mkdir objects

RUN make

CMD ["./main.g"]