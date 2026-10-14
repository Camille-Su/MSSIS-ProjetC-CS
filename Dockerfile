FROM gcc:4.9
COPY ./ /usr/src/app/
WORKDIR /usr/src/app
RUN apt install libssl-dev -y
CMD [ "gcc", "src/main.c", "-o", "t3c", "-I", "src" ] 