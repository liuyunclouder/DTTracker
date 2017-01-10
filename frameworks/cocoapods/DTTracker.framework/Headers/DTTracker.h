//
//  DTTracker.h
//  DTTracker
//
//  Version: @"1.0"
//
//  Created by TangYunfei on 2016/12/29.
//  Copyright © 2016年 dtstack.com. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef DTTracker_h
#define DTTracker_h



/**
 DTTracker.framework依赖以下库
 libsqlite3.tbd
 libz.1.2.5.tbd
 */



/**
 数据格式
 {
 "app_version" = "1.0";
 "available_disk_size" = "507.8 MB";
 "available_memory_size" = "773.8 MB";
 battery = "-1";
 carrier = "中国移动";
 "channel_id" = AppStore;
 "custom_data" = {
    caller = "DTMainViewController-addSuperProps";
    k1 = v1;
    "super_prop" = value;
 };
 event = "test super";
 "identity_id" = "AA78BB4A-BBDA-430B-83E8-96C96B2E6614";
 lib = iOS;
 "lib_version" = "1.000000";
 manufacturer = Apple;
 model = "iPhone 6";
 network = WIFI;
 os = iOS;
 "os_version" = "10.2";
 "session_id" = 2925cfa88b6f9a1e0f62e6237960df67;
 time = "1483081849765.983154";
 "total_disk_size" = "11.1 GB";
 "total_memory_size" = "989.0 MB";
 "user_id" = 123456789;
 }
 
 custom_data中的是用户自定义数据，caller为调用者路径
 */




#import "DTTrackManager.h"
#import "DTIdentity.h"

#endif /* DTTracker_h */
