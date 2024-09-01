project('spelunky', 'c',
  version : '0.1',
  default_options : ['warning_level=3']
)

pwd = meson.current_source_dir()
cc = meson.get_compiler('c')

src_files = [
    'src/util.c',
    'src/vector.c',
    'src/matrix.c',
    'src/context.c',
    'src/sprites.c',
    'src/polygon.c',
    'src/font.c',
    'src/fastRandom.c',
    'src/entity.c',
    'src/map.c',
    'src/data.c',
    'src/renderer.c',
    'src/game.c',
    'src/menu.c',
    'src/tests.c',
    'src/srcLevelGen.c',
    'src/srcRoomGen1.c',
    # 'src/srcEntityGen.c',
    'src/characters/snake.c',
    'src/characters/spider.c',
    'src/characters/bat.c',
    'src/characters/player.c',
    # 'src/characters/player/characterStepEvent.c',
    'src/blocks/pushBlock.c',
    'src/items/whip.c',
]

src_includes = include_directories(
    'include'
)

m_dep = cc.find_library('m', required : true, disabler: true)
sdl2_dep = dependency('SDL2', required: true, disabler: true)
sdl2_image_dep = dependency('SDL2_image', required: true, disabler: true)

executable('spelunky',
    'src/main.c',
    src_files,
    include_directories: [ src_includes ],
    dependencies: [ m_dep, sdl2_dep, sdl2_image_dep ]
)
