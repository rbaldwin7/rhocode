FILE(REMOVE_RECURSE
  "../msg_gen"
  "../srv_gen"
  "../src/simple/msg"
  "../src/simple/srv"
  "../msg_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/setGoal.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_setGoal.lisp"
  "../srv_gen/lisp/set_goal.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_set_goal.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
