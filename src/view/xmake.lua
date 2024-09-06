add_requires(
  's21rules',
  'qcustomplot'
)

target('view')
  set_kind('static')
  add_includedirs('./include', { public = true })
  add_files(
    'src/*.cc',
    'ui/*.ui',
    'include/*.h'
  )

  add_rules(
    'qt.static',
    '@s21rules/cxx'
  )
  set_languages('cxx17') -- Somehow it's not inheriting standart from cxx rule when compiling with qt

  add_deps('controller')

  add_frameworks('QtCore', 'QtGui', 'QtWidgets')

  add_packages('qcustomplot')
target_end()
