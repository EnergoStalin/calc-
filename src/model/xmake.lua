add_requires(
  's21rules'
)

target('model')
  set_kind('static')
  add_files('*.cc')
  add_includedirs('.', { public = true })

  add_defines("USE_MATH_DEFINES")
  add_rules('@s21rules/cxxlib')
target_end()

includes('tests/xmake.lua')
