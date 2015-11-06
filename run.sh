#!/bin/bash
nohup mpiexec -n 2 --machinefile machines krig 5 &
