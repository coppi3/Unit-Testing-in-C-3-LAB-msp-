file(REMOVE_RECURSE
  "src/lib/libipv4.pdb"
  "src/lib/libipv4.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/ipv4.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
