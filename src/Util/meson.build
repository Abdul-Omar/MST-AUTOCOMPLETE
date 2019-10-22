util = library('util', sources : ['util.hpp', 'util.cpp'], dependencies: [dictionary_trie_dep])
inc = include_directories('.')

util_dep = declare_dependency(include_directories : inc,
  link_with : util)