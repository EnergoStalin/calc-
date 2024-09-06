add_requires(
  's21rules'
)

target('controller')
  set_kind('static')
  add_files('*.cc')
  add_includedirs('.', { public = true })

  add_deps('model')

  add_rules('@s21rules/cxxlib')
target_end()
