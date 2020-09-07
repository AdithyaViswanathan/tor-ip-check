Check whether an IP is a tor IP.

I have used a program where we would get information from exonerator.torproject.org where it would give us some information anout whether the IP was used as an exit node . 
I have used curl function in C++ to extract the information of the website.

required packages to install : libcurl 
 
To Install libcurl :  
	sudo apt-get install libcurl4-openssl-dev
 
Command :
 	g++ <filename.cpp> -lcurl -o <outputfile>
	./<output file> <ip to be checked>
