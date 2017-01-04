
Pod::Spec.new do |s|


  s.name         = "DTTracker"
  s.version      = "1.0.0"
  s.summary      = "DTTracker SDK"

  s.description  = "DTTracker SDK description"

  s.homepage     = "https://www.dtstack.com/"


  s.license      = "MIT"


  s.author             = { "liuyunclouder" => "liuyunclouder@gmail.com" }

  # s.platform     = :ios
  s.platform     = :ios, "6.0"



  s.source       = { :git => "https://github.com/liuyunclouder/DTTracker.git", :tag => "1.0.0" }

  s.source_files  = "DTTracker.framework/Headers/*.h"
  s.public_header_files = "DTTracker.framework/Headers/*.h"
  s.vendored_frameworks = "DTTracker.framework"


  s.preserve_paths = "DTTracker.framework"


  s.frameworks = "Foundation", "UIKit", "CoreTelephony"

  s.libraries = "sqlite3", "z"


  s.requires_arc = true

  s.pod_target_xcconfig = { "OTHER_LDFLAGS" => "-ObjC -all_load" }

end
