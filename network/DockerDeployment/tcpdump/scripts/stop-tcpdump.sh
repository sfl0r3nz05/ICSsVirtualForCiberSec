#!/bin/bash
echo "Stopping tcpdump container"
#docker rm -f $(docker ps -aq)
docker-compose stop