//
//  DTTrackManager.h
//  DTTracker
//
//  Created by TangYunfei on 16/12/2.
//  Copyright © 2016年 dtstack.com. All rights reserved.
//


#import "UIControl+DTControl.h"



/**
 运行模式
 */
typedef NS_ENUM(NSInteger, DTTrackerDebugMode) {
    /** 关闭DEBUG模式 */
    DTTrackerDebugOff,
    /** DEBUG模式，但该模式下发送的数据仅用于调试，不进行数据导入 */
    DTTrackerDebugOnly,
    /** DEBUG模式，并将数据导入到云日志中 */
    DTTrackerDebugAndTrack
};


/**
 优先采用ID类型，如果无法获取，则取UUID
 */
typedef NS_ENUM(NSInteger, DTTrackerIDType) {
    /** IDFA */
    DTTrackerIDTypeIDFA,
    /** IDFV */
    DTTrackerIDTypeIDFV
};




@class DTIdentity;
@interface DTTrackManager : NSObject

@property (nonatomic, readonly, strong) NSString *version;

/**
 标示信息，见DTIdentity.h
 */
@property (nonatomic, readonly, strong) DTIdentity *identity;


/**
 默认值为 100，在每次调用trackEvent等接口的时候，都会检查如下条件，以判断是否向服务器上传数据:
 1. 是否WIFI/3G/4G网络
 2. 是否满足以下数据发送条件之一:
    1) 与上次发送的时间间隔是否大于 flushInterval
    2) 本地缓存日志数目是否达到 flushBulkSize
 如果同时满足这两个条件，则向服务器发送一次数据；如果不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 */
@property (nonatomic, assign) NSUInteger flushBulkSize;


/**
 默认值为 100，在每次调用trackEvent等接口的时候，都会检查如下条件，以判断是否向服务器上传数据:
 1. 是否WIFI/3G/4G网络
 2. 是否满足以下数据发送条件之一:
    1) 与上次发送的时间间隔是否大于 flushInterval
    2) 本地缓存日志数目是否达到 flushBulkSize
 如果同时满足这两个条件，则向服务器发送一次数据；如果不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 */
@property (nonatomic, assign) NSUInteger flushInterval;


/**
 当前的superProps的副本
 */
@property (nonatomic, readonly) NSDictionary *superProps;


/**
 是否开启对应用启动、进入后台，以及UIViewController等进入和退出的事件追踪
 */
@property (nonatomic, assign) BOOL autoTrack;


/**
 是否追踪crash事件
 */
@property (nonatomic, assign) BOOL trackCrash;


/**
 设置需要过滤的controller，如
 @[@"DTMainController", @"DTDetailController"]
 */
@property (nonatomic, copy) NSArray *filterControllers;


/**
 设置需要过滤的controller，如
  @{
    @"main": @[@"DTMainController", @"DTDetailController"]
    }
 */
@property (nonatomic, copy) NSDictionary *controllerMap;


/**
 初始化DTTrackManager单例，IDType默认为DTTrackerIDTypeIDFA
 
 @param serverURL 上传接口，从 https://log.dtstack.com/upload.html#/http 生成
 @param token token，取应用名称，与 https://log.dtstack.com/upload.html#/http 填写的保持一致
 @param debugMode 开发模式
 @return DTTrackManager单例
 */
+ (DTTrackManager *)sharedInstanceWithServerURL:(NSString *)serverURL
                                          token:(NSString *)token
                                      debugMode:(DTTrackerDebugMode)debugMode;

/**
 初始化DTTrackManager单例

 @param serverURL 上传接口，从 https://log.dtstack.com/upload.html#/http 生成
 @param token token，取应用名称，与 https://log.dtstack.com/upload.html#/http 填写的保持一致
 @param IDType ID类型，见DTTrackerIDType
 @param debugMode 开发模式
 @return DTTrackManager单例
 */
+ (DTTrackManager *)sharedInstanceWithServerURL:(NSString *)serverURL
                                   token:(NSString *)token
                                       preferredID:(DTTrackerIDType)IDType
                                 debugMode:(DTTrackerDebugMode)debugMode;


/**
 调用前必须先调用
 + (DTTrackManager *)sharedInstanceWithServerURL:(NSString *)serverURL
                                         token:(NSString *)token
                                       debugMode:(DTTrackerDebugMode)debugMode;
 or
 + (DTTrackManager *)sharedInstanceWithServerURL:(NSString *)serverURL
                                            token:(NSString *)token
                                        preferredID:(DTTrackerIDType)IDType
                                            debugMode:(DTTrackerDebugMode)debugMode;
 
 @return DTTrackManager单例
 */
+ (DTTrackManager *)sharedInstance;


/**
 普通追踪

 @param event 事件名称
 @param props 自定义属性
 */
- (void)trackEvent:(NSString *)event withProperties:(NSDictionary *)props;


/**
 普通追踪

 @param event 事件名称
 */
- (void)trackEvent:(NSString *)event;


/**
 开始事务追踪

 @param event 事件名称
 @param props 自定义属性
 @return 事务ID
 */
- (NSString *)trackTransactionBeginWithEvent:(NSString *)event withProperties:(NSDictionary *)props;


/**
 回滚事务

 @param transactionID 事务ID
 */
- (void)trackRollbackWithTransactionID:(NSString *)transactionID;


/**
 提交事务

 @param transactionID 事务ID
 */
- (void)trackCommitWithTransactionID:(NSString *)transactionID;


/**
 上传现有数据
 */
- (void)flush;


/**
 添加自定义全局数据
 一旦设置后，自定义全局数据会在每次的数据发送都会带上，除非通过removeSuperProps或clearSuperProps清除

 @param props 全局数据，比如
 @{
    @"activity": @"place order"
 }
 */
- (void)addSuperProps:(NSDictionary *)props;


/**
 删除部分自定义全局数据

 @param propKeys 全局数据key名称，比如
 @[@"activity"]
 */
- (void)removeSuperProps:(NSArray *)propKeys;


/**
 清空自定义全局数据
 */
- (void)clearSuperProps;


/**
 是否需要拦截请求，主要为与H5做数据交换时使用

 @param request 当前请求
 @param webView 当前webview
 @param propertyDict 需要添加的额外数据
 @return 是否已拦截
 */
- (BOOL)shouldInterceptRequest:(NSURLRequest *)request inWebView:(id)webView withProperties:(NSDictionary *)propertyDict;

@end







/**
 autoTrack为YES，即开启自动追踪时，如果UIViewController实现了DTAutoTrackProtocol，发送数据时会从加上自定义数据
 */
@protocol DTAutoTrackProtocol <NSObject>

/**
 需要带上的自定义数据
 */
- (NSDictionary *)propsToTrack;

/**
 需要带上的当前界面的URL
 */
- (NSString *)curViewURL;

@end





/**
 开发环境中可能的异常
 */
@interface DTTrackerDebugException : NSException

@end









