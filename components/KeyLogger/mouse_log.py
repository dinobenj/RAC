from time import time

# Log file path for mouse events
mouse_log_file_path = "Logs/mouse_log_output.txt"

# Initialize data structures for mouse analysis
mouse_events = []

def log(event_type, x, y, duration):
  timestamp = time()
  if event_type == "move":
    mouse_events.append(("move", x, y, duration, timestamp))
    with open(mouse_log_file_path, "a") as file:
      file.write(f"MOVE to ({x}, {y}) at {timestamp:.2f}s, duration {duration:.2f}s\n")
  elif event_type == "click":
    mouse_events.append(("click", x, y, duration, timestamp))
    with open(mouse_log_file_path, "a") as file:
      file.write(f"CLICK at ({x}, {y}) at {timestamp:.2f}s, duration {duration:.2f}s\n")
