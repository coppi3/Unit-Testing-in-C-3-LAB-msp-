file(REMOVE_RECURSE
  "src/bin/lab"
  "src/bin/lab.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/lab.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
