#Name: Casey Bates
#Date: 9/24
#Title: Lab1 - Shell Programming
#Description: This program prints the current path, checks who the user is,
#and checks how many users are logged in. It also calculates the area of a
#rectangle (given height and width), and a circle (given radius).

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "cbates" ]
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!" #if user isn't cbates, exit the program
	exit 1
fi

#Calculates the area of a rectangle given the height and width. Loops until answe "No" is given.
response="Yes"
while [ $response != "No" ]
do
	echo "Enter height of rectangle: "
	read height
	echo "Enter width of rectangle: "
	read width
	area=`expr $height \* $width` #calculate height * width
	echo "The area of the rectangle is $area"

	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response

done

#Calculates the area of a circle given the radius. Loops until answer "No" is given.
response="Yes"
while [ $response != "No" ]
do
	echo "Enter radius of circle: "
	read radius
	area=`expr "$(($radius**2)) * 3.14159" | bc` #calculate the radius^2, then multiply it by pi
	echo "The area of the rectangle is $area"
	
	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response

done
