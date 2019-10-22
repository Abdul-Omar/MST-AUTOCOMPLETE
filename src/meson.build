subdir('DictionaryTrie')
subdir('Util')

# TODO: Define autocomplete_exe to output executable file named 
#       autocomplete.cpp.executable

benchtrie_exe = executable('benchtrie.cpp.executable', 
    sources: ['benchtrie.cpp'],
    dependencies : [dictionary_trie_dep, util_dep],
    install : true)

autocomplete_exe = executable('autocomplete.cpp.executable',
    sources: ['autocomplete.cpp'],
    dependencies : [dictionary_trie_dep, util_dep],
    install : true)

