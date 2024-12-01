from pynput import keyboard

def key_press(key):
  print(f"Key pressed: {key}")
  if key == keyboard.Key.esc:
    return False

if __name__ == "__main__":
  with keyboard.Listener(on_press=key_press) as listener:
    listener.join()
