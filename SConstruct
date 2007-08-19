# SCONS build script

env = Environment ( )

# Check for debug
debug = ARGUMENTS.get( 'debug', 0 )
if int(debug):
	env.Append(CXXFLAGS = '-g')

env['CPPPATH'] = [ '#.', '#Lua', '#include', '/usr/include/SDL' ]
env['CPPDEFINES'] = {'LUABIND_NO_EXCEPTIONS':1}
Export ( 'env' )

SConscript( ['src/SConstruct',
			 'MiniUI/SConstruct',
			 'Lua/SConstruct',
 			 'OpenGLRenderer/SConstruct',
 			 'SDLInput/SConstruct',
 			 'luabind/SConstruct' ] )

Depends ( 'build/miniui', 'lib/libminiui.a' )
Depends ( 'build/miniui', 'lib/liblua.a' )
Depends ( 'lib/libOpenGLRenderer.a', 'lib/libminiui.a' )
Depends ( 'build/miniui', 'lib/libOpenGLRenderer.a' )
Depends ( 'build/miniui', 'lib/libSDLInput.a' )
Depends ( 'lib/libminiui.a', 'lib/liblua.a' )
Depends ( 'lib/luabind.a', 'lib/liblua.a' )