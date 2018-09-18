docker build -t instance .
docker system prune
docker run -v `dirname "$(readlink -f "$0")"`:/home/environment -it instance