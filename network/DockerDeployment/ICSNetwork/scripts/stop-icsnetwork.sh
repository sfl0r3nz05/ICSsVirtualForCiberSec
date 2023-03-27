#!/bin/bash
echo "Stopping ics network container"
#docker rm -f $(docker ps -aq)
docker compose stop