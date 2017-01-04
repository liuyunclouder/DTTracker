![][image-1]![MIT Licence][image-2]

DTTracker 是袋鼠云官方iOS数据埋点SDK

## 如何使用

1. 注册袋鼠云云日志帐号
2. 创建上传接口及token信息
3. 安装DTTracker SDK，并使用上传接口及token初始化


## 安装
DTTracker 支持使用CocoaPods和手工引入。

### CocoaPods

DTTracker 支持使用CocoaPods引入：

\`\`\`ruby
pod  'DTTracker'
\`\`\`

然后install：

\`\`\`bash
$ pod install
\`\`\`

###  手工引入
克隆本仓库到本地，直接拖拽DTTracker.framework到工程目录下，同时添加libsqlite3和libz.1.2.5
![][image-3]

## 版本支持
支持iOS 8.0及以上版本


## 使用说明

### 上传接口及token信息

1. 登录后进入[ https://log.dtstack.com/upload.html#/http ]() 
2. 根据指示选择解析规则（[解析规则列表][2]允许自定义规则），填写appname和tag，保存好填写的appname，这就是后续初始化时需要的token，点击下一步
	![][image-4]
3. 选择接口的协议类型，建议选择https，这样更好地保护您的数据安全，然后复制接口并保存
	![][image-5]


### 初始化

	
	DTTrackManager *trackMangar = [DTTrackManager sharedInstanceWithServerURL:@"your_upload_url" token:@"your_app_token" debugMode:DTTrackerDebugAndTrack];
your\_upload\_url为步骤3中的接口地址，your\_app\_token为步骤2中的appname，发布时debugMode一定要设置为DTTrackerDebugOff。

#### 运行模式

	
	/**
	 运行模式
	 */
	typedef NS_ENUM(NSInteger, DTTrackerDebugMode) {
	    /** 关闭DEBUG模式，线上环境使用 */
	    DTTrackerDebugOff,
	    /** DEBUG模式，但该模式下发送的数据仅用于调试，不进行数据导入 */
	    DTTrackerDebugOnly,
	    /** DEBUG模式，并将数据导入到云日志中 */
	    DTTrackerDebugAndTrack
	};
	

#### 埋点
埋点记录会根据记录条数和时间选择性上传，同时也会在APP进入后台时执行上传任务，在不影响用户体验的同时尽量保证数据的实时性。

##### 普通埋点
	
	[[DTTrackManager sharedInstance] trackEvent:@"test plain track" withProperties:@{ @"k1":@"v1"}];

##### 事务埋点
	
	NSString *transactionID = [[DTTrackManager sharedInstance] trackTransactionBeginWithEvent:@"test transaction track" withProperties:@{
	                                                                                                 @"test": @"y"
	                                                                                                 }];
	    
	    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
	        [[DTTrackManager sharedInstance] trackCommitWithTransactionID: transactionID];
	    });

##### 自动埋点
会在APP启动和进入后台，以及页面载入和退出时，自动生成埋点记录，见 DTAutoTrackProtocol。
	
	trackMangar.autoTrack = YES;

##### crash 埋点
如果设置了trackCrash为YES，DTTracker会把崩溃堆栈信息也记录下来。
	
	trackMangar.trackCrash = YES;

##### UIControl 埋点

	
	self.btn.dt_eventInfo = @{
	                           @"event": @"btn clicked",
	                           @"bus": @"311"
	                           };

##### H5
如果同时使用我们的JS SDK，需要在以下两个方法里添加几行代码，方便Native和H5通信。

UIWebView：
	
	- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
	    if ([[DTTrackManager sharedInstance] shouldInterceptRequest:request inWebView:webView withProperties:nil]) {
	        return NO;
	    }
	    return YES;
	}

WKWebView：
	
	- (void)webView:(WKWebView *)webView decidePolicyForNavigationAction:(WKNavigationAction *)navigationAction decisionHandler:(void (^)(WKNavigationActionPolicy))decisionHandler {
	    if ([[DTTrackManager sharedInstance] shouldInterceptRequest:navigationAction.request inWebView:webView withProperties:nil]) {
	        decisionHandler(WKNavigationActionPolicyCancel);
	        return;
	    }
	    
	    decisionHandler(WKNavigationActionPolicyAllow);
	}


#### 更多用法请查阅头文件

## License

MIT

[2]:	https://log.dtstack.com/setting.html#/setting/parser/list

[image-1]:	https://img.shields.io/badge/pod-v1.0.0-green.svg
[image-2]:	https://img.shields.io/badge/licence-MIT-green.svg
[image-3]:	http://d.pr/i/qsdW+
[image-4]:	http://d.pr/i/pVHb+
[image-5]:	http://d.pr/i/7hDS+