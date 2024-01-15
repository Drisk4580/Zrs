project('Zrs', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

src_files = ['src/main.cpp']

glfw_dep = dependency('glfw3')
vulkan_dep = dependency('vulkan')

executable('Zrs', src_files, dependencies : [vulkan_dep, glfw_dep])

