Pod::Spec.new do |s|

# Common settings
  s.name         = "RECore"
  s.version      = "3.0.3"
  s.summary      = "C++ core implementation"
  s.description  = <<-DESC
C++ core implementation.
                      DESC
  s.homepage     = "https://github.com/OlehKulykov/RECore"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { "Oleh Kulykov" => "info@resident.name" }
  s.source       = { :git => 'https://github.com/OlehKulykov/RECore.git', :tag => s.version.to_s }

# Platforms
  s.ios.deployment_target = "7.0"
  s.osx.deployment_target = "10.7"
  s.tvos.deployment_target = '9.0'

# Build  
  s.public_header_files = 'include/*.{h}'
  
  s.source_files = 
  'include/*.{h}',
  'src/*.{h,cpp}',
  'lzma/*.{h,c}',
  'jansson/src/*.{h,c}',
  'builds/mac/*.{h}'
  
  s.compiler_flags = '-D_7ZIP_ST=1', '-DRE_BUILD_WITH_LZMA2=1', '-DHAVE_RECORE_CONFIG_H=1'
  
  s.requires_arc = false
  s.libraries = 'pthread', 'stdc++', 'z'

end
