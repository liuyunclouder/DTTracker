
Pod::Spec.new do |s|


  s.name         = "DTTracker"
  s.version      = "0.0.1"
  s.summary      = "DTTracker SDK"

  s.description  = "you can use DTTracker to track your user behavior in your app"

  s.homepage     = "https://www.dtstack.com/"


  s.license      = "MIT"


  s.author       = { "liuyunclouder" => "liuyunclouder@gmail.com" }


  s.platform     = :ios, "8.0"



  s.source       = { :git => "https://github.com/liuyunclouder/DTTracker.git", :tag => s.version }


  s.vendored_frameworks = "frameworks/cocoapods/DTTracker.framework"


  s.frameworks = "Foundation", "UIKit", "CoreTelephony"

  s.libraries = "sqlite3", "z"

  s.requires_arc = true

  s.pod_target_xcconfig = { "OTHER_LDFLAGS" => "-ObjC -all_load" }

end
