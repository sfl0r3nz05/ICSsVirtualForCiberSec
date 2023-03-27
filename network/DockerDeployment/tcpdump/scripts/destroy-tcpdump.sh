#!/bin/bash
echo "Stopping tcpdump container"
docker compose down
sudo rm -rf ../../mysql/databases