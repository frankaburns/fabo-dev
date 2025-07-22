# FC number converter
# This python program inputs a decimal number
# from the console as an ASCII string, then converts the
# string to an integer.
#
# The program then first converts the deciman number to 
# hexidecimal(base 16), octal(base 8) and binary (base 2)
# Then print the results to the console.
# The program then loops back to the input line, to exit
# enter -1

# Declare and initialize program scope variables
# The hex_digits list is used to print the hex digits
# since they extend from 0 - 15 (decimal)
#
# Note: I could of used the %x print modifier to achieve
#       the same output, but this further illustrates what
#       is happening.
#
# Note2: The input string conversion uses the ord function
#        and then subtracts (48) from the result illustrating
#        that an ASCII digits(0, 1, 2, 3...) is stored in memory
#        as decimal (48, 49, 50...)
#
number = 0

# Define the characters for hexidecimal numbers
# 0 - F, where A represents 10, B - 11, C - 12 etc.
# up to the number of hex digits.
#
hex_digits = [ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' ]

# Main input loop while the input number is greater
# than -1.
#
while number > -1:

# Get the digit string from the console.
#
   str_number = input('\nenter a number (-1 to exit): ')

# if the input string equals -1 ASCII
# break out of the main loop and exit.
#
   if str_number == '-1':
      break

# convert each input ASCII digit to a decimal number
# and assign the result to number.
# Note: The highest order digit is converted first so
#       the digit must be shifted up one order of magnitude
#       (multiply by 10) each time through the loop.
#          
   for n in str_number:
      number = number*10         
      number = number + (ord(n)-48)
# Clear the input string for the next input request.
#
   str_number = None

# Initialize our the numbers to operate on for each
# conversion.
#
   b_num = number          
   o_num = number          
   h_num = number          

# Convert the input number to hexidecimal.
#
   int_array = []
   while h_num > 0: 
      int_array.append(h_num%16)
      temp = h_num/16
      h_num = int(temp)

# Print the array elements out backwards (i.e. from len(array) - 0
# this is a side effect from the conversion since the converted digits
# are derived from the least magnitude to the greatest magnitude.
#
   idx = len(int_array)
   print (number, "in hex    := ", end="")
   while idx > 0:   
      idx -= 1
      print(hex_digits[int_array[idx]], end="")
   print ('') 


   int_array = []
   while o_num > 0: 
      int_array.append(o_num%8)
      temp = o_num/8
      o_num = int(temp)

# Print the array elements out backwards (i.e. from len(array) - 0
# this is a side effect from the conversion since the converted digits
# are derived from the least magnitude to the greatest magnitude.
#
   idx = len(int_array)
   print (number, "in octal  := ", end="")
   while idx > 0:   
      idx -= 1
      print(int_array[idx], end="")
   print ('') 

# Convert the input number to hexidecimal.
#
   int_array = []
   while b_num > 0: 
      int_array.append(b_num%2)
      temp = b_num/2
      b_num = int(temp)

# Print the array elements out backwards (i.e. from len(array) - 0
# this is a side effect from the conversion since the converted digits
# are derived from the least magnitude to the greatest magnitude.
#
   idx = len(int_array)
   print (number, "in binary := ", end="")
   while idx > 0:   
      idx -= 1
      print(int_array[idx], end="")
   print ('') 

   number = 0
