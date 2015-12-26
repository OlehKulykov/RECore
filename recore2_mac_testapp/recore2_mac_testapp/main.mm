//
//  main.m
//  recore2_mac_testapp
//
//  Created by Resident evil on 9/8/15.
//  Copyright (c) 2015 Resident evil. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "REBufferRW.h"

int t1()
{
	REBufferR r;
	REBufferRW rw;

	rw.fileWrite("hello", 5);
	rw.fileWrite(" world", 7);



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
