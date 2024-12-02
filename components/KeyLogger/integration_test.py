from pynput import keyboard, mouse
from keyboard_test import key_press
from mouse_test import on_move, on_click # , on_scroll

global mouse_listener

def through_key_press(key):
  global mouse_listener
  
  # Call the real key_press
  key_press(key)

  # Still check if we should stop the program
  if key == keyboard.Key.esc:
    if mouse_listener is not None:
      mouse_listener.stop()
      print("Mouse listener stopped.")
    return False


if __name__ == "__main__":
  keyboard_listener = keyboard.Listener(on_press=through_key_press)

  mouse_listener = mouse.Listener(
    on_move=on_move,
    on_click=on_click,
    # on_scroll=on_scroll
  )

  keyboard_listener.start()
  mouse_listener.start()

  keyboard_listener.join()
  mouse_listener.join()
