//
//  main.m
//  recore2_mac_testapp
//
//  Created by Resident evil on 9/8/15.
//  Copyright (c) 2015 Resident evil. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RELZMA2.h"

int t1()
{

	const char * inText = "I am trying to create a function that uncompresses LZAM2 compressed data. I inspired myself from this tutorial which works great for LZMA and I tried to adapt it for LZMA2. I successfully created the compression function for LZMA2, but i have no success for the uncompression one. Here is the compression function:"
	"A temporary workaround would be to replace SRes res = Lzma2Dec_Allocate(&dec, outBuf.size(), &SzAllocForLzma); with SRes res = Lzma2Dec_Allocate(&dec, 8, &SzAllocForLzma); in Uncompress2Inc function where 8 is a magic number..."
	"However this is not the right way to solve the problem..."
	"First mistake is that Lzma2Enc_WriteProperties doesn't return a result but a property byte which will have to be used as the second parameter of the Lzma2Dec_Allocate call in the Uncompress2Inc function. As a result we replace the magic number 8 with the property byte and everything works as expected."
	"In order to achieve this a 5 byte header must be added to the encoded data which will be extracted in the decoding function. Here is an example that works in VS2008(not the most perfect code but it works...I will get back later, when I have time, with a better example):";

	RELZMA2Compressor compr;
	compr.compress(inText, strlen(inText));

	return 0;
}

int main(int argc, const char * argv[])
{
	@autoreleasepool
	{
		t1();
	    // insert code here...
	    NSLog(@"Hello, World!");
	}
    return 0;
}
