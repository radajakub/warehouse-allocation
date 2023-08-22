#!/bin/bash

for file in $(ls ../res/)
do
    python toline.py "../res/$file" > "./transoformed/$file"
done

