from pynput import mouse
from mouse_log import log
from time import time

start = time()

def mouse_event(x, y, button=None, action=None):
  global start
  old = start
  start = time()
  if action == "move":
    print(f"Mouse moved to: ({x}, {y})")
    log("move", x, y, start - old)
  elif action == "click":
    print(f"Mouse {button} {'pressed' if action else 'released'} at: ({x}, {y})")
    log("click", button, x, y, start - old)

# Define mouse callbacks
def on_move(x, y):
  mouse_event(x, y, action="move")

def on_click(x, y, button, pressed):
  action = "pressed" if pressed else "released"
  mouse_event(x, y, button=button, action=action)


if __name__ == "__main__":
  with mouse.Listener(
    on_move=on_move,
    on_click=on_click,
  ) as listener:
    listener.join()
