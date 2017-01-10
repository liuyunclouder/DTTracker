//
//  DTIdentity.h
//  DTTracker
//
//  Created by TangYunfei on 2016/12/29.
//  Copyright © 2016年 dtstack.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@class DTTrackManager;
@interface DTIdentity : NSObject

@property (nonatomic, assign) BOOL useIDFA;

/**
 设备ID
 */
@property (nonatomic, readonly) NSString *identityID;


/**
 用户ID
 */
@property (nonatomic, copy) NSString *userID;


/**
 渠道ID，默认为AppStore
 */
@property (nonatomic, copy) NSString *channelID;


/**
 会话ID
 */
@property (nonatomic, copy) NSString *sessionID;


/**
 所有ID数据

 @return @{
    @"identity_id": identityID,
    @"user_id": userID,
    @"session_id": sessionID,
    @"channel_id": channelID
 };
 */
- (NSDictionary *)completeIDProps;

@end
