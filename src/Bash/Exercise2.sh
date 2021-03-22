# Create a shell script able to accept as an input a file with one number per line and return their average.
# It must support an arbitrary file length.

filename="TextFile.txt"
awk '{s+=$1} END {printf "AVG: %.3f\n",s/FNR}' $filename
