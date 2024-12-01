from pynput import keyboard
from keyboard_log import log
from time import time

start = time()

def key_press(key):
  global start
  print(f"Key pressed: {key}")
  old = start
  start = time()
  log(key, start - old)
  if key == keyboard.Key.esc:
    return False

if __name__ == "__main__":
  with keyboard.Listener(on_press=key_press) as listener:
    listener.join()
