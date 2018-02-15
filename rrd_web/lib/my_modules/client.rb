require 'ffi'

module MyModules
  module Client
  	extend FFI::Library
  	ffi_lib 'c'
  	ffi_lib '../rrd_cpp/web_client.so'
 	attach_function :send_from_web, [ :pointer, :int, :pointer ], :void
  end
end