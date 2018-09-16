docker build -t instance .
docker system prune
docker run -v /home/ec2-user/environment:/home/environment -it instance