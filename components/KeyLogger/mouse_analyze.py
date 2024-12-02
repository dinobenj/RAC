from collections import defaultdict

mouse_log_file_path = "Logs/mouse_log_output.txt"
mouse_move_events = []
mouse_click_events = []

# Load mouse events from log file
def load_mouse_events():
  with open(mouse_log_file_path, "r") as file:
    lines = file.readlines()
    for line in lines:
      if "MOVE" in line:
        parts = line.strip().split()
        x = int(parts[2][1:-1])
        y = int(parts[3][:-1])
        timestamp = float(parts[-3][:-2])
        duration = float(parts[-1][:-1])
        mouse_move_events.append(("move", x, y, timestamp, duration))
      elif "CLICK" in line: # TODO NOT WORKING
        return
        parts = line.strip().split()
        x = int(parts[2][1:-1])
        y = int(parts[3][:-1])
        timestamp = float(parts[-3][:-2])
        duration = float(parts[-1][:-1])
        mouse_click_events.append(("click", x, y, timestamp, duration))

# Analyze mouse movements
def analyze_movements():
  total_distance = 0
  last_position = None
  move_count = 0

  for event in mouse_move_events:
    if event[0] == "move":
      move_count += 1
      x, y = event[1], event[2]
      if last_position is not None:
        total_distance += ((x - last_position[0]) ** 2 + (y - last_position[1]) ** 2) ** 0.5
      last_position = (x, y)

  avg_distance = total_distance / move_count if move_count > 0 else 0
  print(f"Total Movements: {move_count}")
  print(f"Total Distance: {total_distance:.2f}")
  print(f"Average Movement Distance: {avg_distance:.2f}")

# Analyze mouse clicks
def analyze_clicks():
  click_counts = defaultdict(int)

  for event in mouse_click_events:
    if event[0] == "click":
      click_counts[(event[1], event[2])] += 1

  print(f"Total Clicks: {sum(click_counts.values())}")
  for position, count in click_counts.items():
    print(f"Clicks at {position}: {count}")

if __name__ == "__main__":
  load_mouse_events()
  analyze_movements()
  # analyze_clicks()
