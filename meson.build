project('hello-world', 'c', default_options: ['c_std=gnu18', 'warning_level=3', 'default_library=static'])

is_playdate_build = meson.get_cross_property('is_playdate_build', false)
playdate_sdk_path = get_option('playdate_sdk_path')
playdate_sdk_incdir = playdate_sdk_path / 'C_API'
playdate_sdk_dep = declare_dependency(include_directories: playdate_sdk_incdir)
playdate_glue_code_src = [playdate_sdk_path / 'C_API' / 'buildsupport' / 'setup.c']
playdate_bin_c_flags = [
  '-DTARGET_PLAYDATE=1',
  '-DTARGET_EXTENSION=1',
  '-mthumb',
  '-mcpu=cortex-m7',
  '-mfloat-abi=hard',
  '-mfpu=fpv5-sp-d16',
  '-D__FPU_USED=1',
  '-falign-functions=16',
  '-fomit-frame-pointer',
  '-gdwarf-2',
  '-fverbose-asm',
  '-ffunction-sections',
  '-fdata-sections',
  '-mword-relocations',
  '-fno-common',
  '-fno-exceptions',
  '-Wno-unknown-pragmas',
  '-Wdouble-promotion',
  '-O2',
]
playdate_sim_bin_c_flags = [
  '-DTARGET_SIMULATOR=1',
  '-DTARGET_EXTENSION=1',
]
playdate_bin_link_args = [
  '-nostartfiles',
  '-mthumb', 
  '-mcpu=cortex-m7', 
  '-mfloat-abi=hard', 
  '-mfpu=fpv5-sp-d16',
  '-D__FPU_USED=1',
  '-T@0@'.format(playdate_sdk_path / 'C_API' / 'buildsupport' / 'link_map.ld'),
  '-Wl,-Map=game.map,--cref,--gc-sections,--no-warn-mismatch,--emit-relocs',
  '--specs=nosys.specs'
]

sim_bin = shared_library(
  'pdex', 
  playdate_glue_code_src +  ['src/main.c'],  
  dependencies: [playdate_sdk_dep], 
  c_args: playdate_sim_bin_c_flags, 
  name_prefix: '', 
  name_suffix: 'so', 
  native: true
)

sh = find_program('sh')

sim_pdx_name = meson.project_name() + '-sim.pdx'
sim_pdx = custom_target(
  sim_pdx_name,
  output: sim_pdx_name,
  command: [sh, [meson.project_source_root() / 'scripts' / 'generate-sim-pdx.sh', meson.project_name() + '-sim', playdate_sdk_path]],
  depends: sim_bin,
  build_always_stale: true,
  build_by_default: true
)

playdate_simulator = find_program('PlaydateSimulator')
run_target(
  'run-sim',
  command: [playdate_simulator, sim_pdx_name],
)
run_target(
  'build-run-sim',
  command: [playdate_simulator, sim_pdx_name],
  depends: [sim_pdx]
)


if is_playdate_build
playdate_bin = executable(
  'pdex.elf',  
  playdate_glue_code_src +  ['src/main.c'],  
  c_args: playdate_bin_c_flags, 
  link_args: playdate_bin_link_args, 
  dependencies: [playdate_sdk_dep], 
)

playdate_pdx = custom_target(
  meson.project_name() + '.pdx',
  output: meson.project_name() + '.pdx',
  command: [sh, [meson.project_source_root() / 'scripts' / 'generate-pdx.sh', meson.project_name()]],
  depends: playdate_bin,
  build_always_stale: true,
  build_by_default: true
)
endif

