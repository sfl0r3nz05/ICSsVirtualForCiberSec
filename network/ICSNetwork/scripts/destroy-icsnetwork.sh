#!/bin/bash
echo "Stopping ics network container"
docker-compose down
sudo rm -rf ../../mysql/databases