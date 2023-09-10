import platform
import subprocess

if platform.system() == 'Darwin':
  subprocess.run("cmake -B build/macOS -G Xcode", shell=True)
