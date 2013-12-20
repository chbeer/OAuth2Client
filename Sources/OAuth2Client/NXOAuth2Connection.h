//
//  NXOAuth2Connection.h
//  OAuth2Client
//
//  Created by Ullrich Schäfer on 27.08.10.
//
//  Copyright 2010 nxtbgthng. All rights reserved. 
//
//  Licenced under the new BSD-licence.
//  See README.md in this reprository for 
//  the full licence.
//

#import <Foundation/Foundation.h>

#import "NXOAuth2Constants.h"

@class NXOAuth2Client;
@class NXOAuth2Connection;

//#if NX_BLOCKS_AVAILABLE && NS_BLOCKS_AVAILABLE
typedef void(^NXOAuth2ConnectionFinishHandler)(NXOAuth2Connection *connection);
typedef void(^NXOAuth2ConnectionFailHandler)(NXOAuth2Connection *connection, NSError *error);
//#endif

@protocol NXOAuth2ConnectionDelegate;


/*!
 *	The connection
 *	
 *	NXOAuth2Connection is a wrapper around NXURLConnection.
 *	It's main purpose is to simplify the delegates & to provide a context
 *	ivar that can be used to put a connection object in a certain context.
 *	The context may be compared to a tag.
 *	
 *	NXOAuth2Connection only provides asynchronous connections as synchronous
 *	connections are strongly discouraged.
 *	
 *	The connection works together with the OAuth2 Client to sign a request
 *	before sending it. If no client is passed in the connection will sent
 *	unsigned requests.
 */

#ifndef NXOAuth2ConnectionDebug
#define NXOAuth2ConnectionDebug 0
#endif

@interface NXOAuth2Connection : NSObject {
@private
	NSURLConnection		*connection;
	NSMutableURLRequest	*request;
	NSURLResponse		*response;
	NSDictionary		*requestParameters;
	
	NSMutableData		*data;
    BOOL                savesData;
	
	id					context;
	NSDictionary		*userInfo;
	
	NXOAuth2Client		*client;
	
	NSObject<NXOAuth2ConnectionDelegate>	*delegate;	// assigned
    
//#if NX_BLOCKS_AVAILABLE && NS_BLOCKS_AVAILABLE
    NXOAuth2ConnectionFinishHandler finish;
    NXOAuth2ConnectionFailHandler fail;
//#endif
	
	BOOL				sendConnectionDidEndNotification;
    
#if (NXOAuth2ConnectionDebug)
    NSDate *startDate;
#endif
}

@property (assign) NSObject<NXOAuth2ConnectionDelegate>	*delegate;
@property (readonly) NSData *data;
@property (assign) BOOL savesData;
@property (readonly) long long expectedContentLength;
@property (readonly) NSInteger statusCode;
@property (retain) id context;
@property (retain) NSDictionary *userInfo;

//#if NX_BLOCKS_AVAILABLE && NS_BLOCKS_AVAILABLE
- (id)initWithRequest:(NSMutableURLRequest *)request
	requestParameters:(NSDictionary *)requestParameters
		  oauthClient:(NXOAuth2Client *)client
               finish:(NXOAuth2ConnectionFinishHandler)finishBlock 
                 fail:(NXOAuth2ConnectionFailHandler)failBlock;
//#endif


- (id)initWithRequest:(NSMutableURLRequest *)request
	requestParameters:(NSDictionary *)requestParameters
		  oauthClient:(NXOAuth2Client *)client
			 delegate:(NSObject<NXOAuth2ConnectionDelegate> *)delegate;

- (void)cancel;

- (void)retry;

@end
