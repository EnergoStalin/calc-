set_project('calc-')
set_version('1.0.0')

set_xmakever('2.8.9')

add_repositories('energostalin git@github.com:EnergoStalin/xmake-repo.git')

add_requires("qtbased")

includes(
  'src/**/xmake.lua'
)
