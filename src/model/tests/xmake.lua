add_requires(
  's21rules',
  'gtest'
)

target('model-tests')
  set_kind('binary')
  add_files('*.cc')

  add_deps('model')

  add_rules(
    '@s21rules/cxxtest',
    '@s21rules/libreport'
  )

  set_group('test')
target_end()
