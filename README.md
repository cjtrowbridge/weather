# Sierra College: CSCI-0046
This is a C program which fetches the current weather conditions from weather underground.

## Lab 10: Weather
In this assignment you will learn about:

* Using the C networking functions to fetch a web page
* Use string functions to extract data from the web page

## Getting Started
1. Create an empty repository on BitBucket.
1. Clone it to your development environment. You'll end up with an empty directory.
1. Do your development in that directory.

## Writing the Program
1. Use the web.c programPreview the document (on the printout) we showed in class as a starting point. Your program should be called weather.c.
1. That the one and only command line argument is the zip code you want the current conditions for. The program should display an error and usage statement if the user didn't supply a zip code.
1. The program should fetch the URL http://api.wunderground.com/api/1655f919bbcd29ed/conditions/q/ZIPCODE.json where ZIPCODE is the zip code that the user entered.
1. The program should display the following data points:
  1. Observation time
  1. City and State
  1. Current temperature (F)
  1. Relative humidity
  1. Wind speed and direction
1. The program terminates at this point. It does not go back and re-prompt the user.

## Sample Output
$ ./weather 95677  
Current Conditions  
Observation time: Last Updated on May 10, 5:18 PM PDT  
Location: Rockin, CA  
Temperature: 81.7 F  
Humidity: 40%  
Wind: SSW 5.8 mph  

Try to follow this output format as closely as possible. Make sure you remove any extraneous characters that are in the JSON document but not part of the data itself, such as quotation marks and colons.

## Parsing the JSON Document
I should emphasize that this technique is not the correct way to parse a document such as JSON. You really should use a parsing library such as json-c (Links to an external site.)Links to an external site.. The same goes for HTML, XML, CSV, and just about any other document type that has a well-defined structure. But this will get the job done for this particular application.

Once you have the socket connected, you get back an integer socket file descriptor, called sockfd in the template program. This integer is just an index into an array of opened files. File descriptors are a low-level way of accessing files; you can only read a chunk from a file or write a chunk. The chunks are often not a convenient size.

It's more convenient to use the buffered file handling functions provided by the FILE structure. It's easy to convert a file descriptor into a FILE pointer. Just call the fdopen function:

FILE *s = fdopen(sockfd, "r+");  
(You will, of course, need to check the value of s to ensure it's pointing to a valid file/socket.)

Once you have a valid FILE pointer, you can read from it using any of the stdio functions that work with files: fgets, fscanf, etc.

And you can write to it using any of the output functions: fprintf, fputs, etc.

Close the socket using fclose. This will close the raw socket file descriptor, too.

As you are reading from the socket a line at a time, you can use the string functions such as strstr to scan through the line looking for key words. Or use sscanf to do pattern matching on the line.

## Grading
Doing the above will get 8 out of 10 points. 

To earn the remaining 2 points, also display the forecasted highs and lows for the next 4 days. You can get both the current conditions and the 10-day forecast with the URL:

http://api.wunderground.com/api/1655f919bbcd29ed/conditions/forecast10day/q/ZIPCODE.json

Note that you'll get 10 days of forecast, but you should display just four of them. You should show the day of the week, the high temperature, and the low temperature, like this:

$ ./weather 95677
Current Conditions  
Observation time: Last Updated on May 12, 10:18 AM PDT  
Location: Rocklin, CA  
Temperature: 65.7 F  
Humidity: 40%  
Wind: SSW 5.8 mph  

Forecast  
Tuesday: 77 48  
Wednesday: 77 49  
Thursday: 76 51  
Friday: 76 50  
All the data you need is in the JSON document, including the days of the week. You'll see that the entries are numbered by "period." To get the next four days of forecast, use periods 1, 2, 3, and 4.

You can get 1 point instead of 2 for simply displaying the predicted high and low of any one of the next four days. In other words, if you are unable to get the program to display four days' of predictions, just do one day.

## What to Turn In
As usual, you should be committing your code periodically. When done, push your program to BitBucket and submit the URL. Be sure to add me (profbbrown) as a collaborator.

