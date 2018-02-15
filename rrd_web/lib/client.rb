require 'ffi'

module Client
   extend FFI::Library
   ffi_lib_flags :now, :global
   ffi_lib 'api.so', '/home/parallels/course/rrd_web/lib/rrd_c/libweb_client.so'
   attach_function :send_from_web, [ :strptr , :int ], :strptr 
end