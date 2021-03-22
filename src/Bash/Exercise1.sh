# Create a bash script which accepts as input a string representing an arithmetic operation composed by the following
# operations and paretheses: +,-,*,^, /, (, ).
# 
# The script must return the result of such operation rounded to 4 decimal digits.
#
# Some example inputs are:
#  - 5+50*3/20 + (17*2)/7
#  - (91.5*7+50*3)/20 + (17^2)/7
#  - 91+50*3/20 + (17^2)/7

#### Solution ########



bc <<< "scale = 4 ; $1"