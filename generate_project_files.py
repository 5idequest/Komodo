import platform
import subprocess

if platform.system() == 'Darwin':
  subprocess.run('cmake -B build/macOS -G Xcode', shell=True)
if platform.system() == 'Windows':
  subprocess.run('cmake -B build/Windows')
else:
  print('Operating system not supported!')
