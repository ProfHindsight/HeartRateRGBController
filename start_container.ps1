docker build --tag hrrgb-dev .
docker run -it --rm -v $pwd/:/home/root/ --name hrrgb-container hrrgb-dev
