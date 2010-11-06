
srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  # conf.check_cfg(package='gmp', mandatory=1, args='--cflags --libs')
  # conf.env.append_value('CXXFLAGS', ['-lgmpxx', '-lgmp'])
  conf.env['LIBPATH_GMP'] = '/usr/local/include'
  conf.env['LIB_GMP'] = 'gmp'

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'gmp'
  obj.source = 'node_gmp.cc'
  obj.uselib = 'GMP'
