
EnsureSConsVersion( 1, 1, 0 )

compile_source_message = 'Compiling $SOURCE'
link_program_message = 'Linking $TARGET'
link_library_message = 'Linking Static Library $TARGET'
link_shared_library_message = 'Linking Shared Library $TARGET'

VariantDir('build', 'src', duplicate=0)

env = Environment()

env['CCCOMSTR'] = compile_source_message
env['CXXCOMSTR'] = compile_source_message
env['ARCOMSTR'] = link_library_message
env['SHLINKCOMSTR'] = link_shared_library_message
env['LINKCOMSTR'] = link_program_message

env.Append(CCFLAGS = ['-std=c++11'])
env.Append(CCFLAGS = ['-g', '-Wall'])
env.Append(CPPPATH = ['/usr/include']) # Boost

sources = Glob('./build/*.cpp')
sources.extend(Glob('./build/elements/*.cpp'))
sources.extend(Glob('./build/logic/*.cpp'))
sources.extend(Glob('./build/draw/*.cpp'))

gl_libs = ['GL', 'GLU', 'glut']
boost_libs = ['boost_signals']

env.Prepend(LIBS = [gl_libs + boost_libs])
prog = env.Program('overload', sources)

