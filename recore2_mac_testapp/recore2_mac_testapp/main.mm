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

	const char * inText = "I am trying to create a function that uncompresses";

	RELZMA2Compressor compr;
	const RESizeT len = strlen(inText);
	compr.compress(inText, len);

	RELZMA2Decompressor decompr;
	decompr.decompress(compr.data(), compr.size());

	if (strncmp(inText, (const char *)compr.data(), len) == 0)
	{
		fprintf(stderr, "");
	}

	NSLog(@"[%s]", (char*)decompr.data());

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
