Check whether an IP is a tor IP.

This program uses exonerator.torproject.org for it's working, 

Required packages to install : 

	libcurl 
 
To Install libcurl :  
	
	sudo apt-get install libcurl4-openssl-dev
 
Command :
 	
	g++ <filename.cpp> -lcurl -o <outputfile>
	./<output file> <ip to be checked>
