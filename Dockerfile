FROM gcc:13
COPY ./ /usr/src/app/
WORKDIR /usr/src/app
RUN apt-get update && apt-get install -y libssl-dev
CMD [ "make"]