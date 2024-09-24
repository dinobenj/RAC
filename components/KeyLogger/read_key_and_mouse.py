from pynput import keyboard, mouse

# Mouse functions

def mouse_move(x, y):
  print(f"Mouse moved to: {x}, {y}")


# Keyboard functions

def key_press(key):
  if key == keyboard.Key.esc:
    mouse_listener.stop()
    return False
  try:
    key_name = key.char
  except:
    key_name = key.name
  print('Key Pressed: ' + key_name)


# Running the listener

keyboard_listener = keyboard.Listener(on_press=key_press)
mouse_listener = mouse.Listener(on_move=mouse_move)

keyboard_listener.start()
# keyboard_listener.join()

mouse_listener.start()
mouse_listener.join()

