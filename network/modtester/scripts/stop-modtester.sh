#!/bin/bash

echo "Stopping attacker container"

#docker rm -f $(docker ps -aq)
docker-compose stop