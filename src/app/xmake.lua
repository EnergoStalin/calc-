add_requires(
  's21rules'
)

target('app')
  set_default()
  set_kind('binary')
  add_files('*.cc')

  add_rules(
    'qt.widgetapp',
    '@s21rules/cxx'
  )
  set_languages('cxx17') -- Somehow it's not inheriting standart from cxx rule when compiling with qt

  add_deps('view')

  set_group('bin')
target_end()
