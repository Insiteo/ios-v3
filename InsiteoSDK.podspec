Pod::Spec.new do |s|

  s.name         = 'InsiteoSDK'
  s.version      = '3.6.11'
  s.summary      = 'Official Insiteo SDK for iOS to access Insiteo indoor location based services core features'

  s.description  = <<-DESC
                   The Insiteo SDK indoor location based services for iOS provides:
                   * 2D/3D map rendering
                   * Indoor location
                   * Itinerary
                   * Geofencing
                   DESC

  s.homepage     = 'https://github.com/Insiteo/ios-v3'
  s.license      = "Copyright 2015-present Insiteo SAS - All Rights Reserved"
  s.author       = "Insiteo"

  s.platform     = :ios, '8.0'

  s.source = { :http => 'https://github.com/Insiteo/ios-v3/releases/download/3.6.11/InsiteoSDK-v3.6.11.zip', :flatten => true }
  s.preserve_paths = '**/*'

  s.public_header_files = 'include/*.h'

  s.resources = 'InsiteoSDK.bundle', 'glsl/**/*.{fsh,vsh}'

  s.frameworks = 'CoreBluetooth', 'CoreGraphics', 'CoreLocation', 'CoreMotion', 'CoreTelephony', 'CoreText', 'Foundation', 'OpenAL', 'OpenGLES', 'QuartzCore', 'UIKit'

  s.libraries = 'c++', 'z', 'sqlite3'

  s.vendored_libraries = 'libInsiteoSDK.a'

  s.requires_arc = false

end
