//
//  UIControl+DTControl.h
//  DTTracker
//
//  Created by TangYunfei on 2016/12/26.
//  Copyright © 2016年 dtstack.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIControl (DTControl)



/**
 需要发送的数据，至少包含一个key:event，如下
  @{
    @"event": @"place order",
    @"price": @(30)
    }
 */
@property (nonatomic, copy) NSDictionary *dt_eventInfo;

@end
