from collections import defaultdict
import matplotlib.pyplot as plt

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


def visualize_lines(mouse_move_events):
  if not mouse_move_events:
    print("No mouse movements to visualize.")
    return

  x_coords = [event[1] for event in mouse_move_events if event[0] == "move"]
  y_coords = [event[2] for event in mouse_move_events if event[0] == "move"]

  plt.figure(figsize=(10, 6))
  plt.plot(x_coords, y_coords, marker='o', linestyle='-', color='b')
  plt.title('Mouse Movement Visualization')
  plt.xlabel('X Coordinate')
  plt.ylabel('Y Coordinate')
  plt.gca().invert_yaxis()  # Invert y-axis to match screen coordinates
  plt.grid(True)

  # Save the plot to a file instead of displaying it
  plt.savefig("Logs/mouse_movement_visualization.png")
  plt.close()
  print("Mouse movement visualization saved to 'Logs/mouse_movement_visualization.png'")

def analyze_mouse_lines():
  if not mouse_move_events:
    print("No mouse movements to analyze.")
    return

  lines = []
  last_position = None
  current_line_start = None
  last_direction = None
  direction_threshold = 0.98  # Higher threshold for dot product to determine direction consistency (less sensitive)
  distance_threshold = 50     # Higher threshold for breaking the line based on large movement distance
  consistent_change_counter = 0
  consistent_change_threshold = 10  # Number of consistent changes before determining a line break

  for event in mouse_move_events:
    x, y = event[1], event[2]
    if last_position is None and current_line_start is None:
      # Starting a new line
      current_line_start = (x, y)
      last_position = (x, y)
    else:
      dx = x - last_position[0]
      dy = y - last_position[1]
      distance = (dx ** 2 + dy ** 2) ** 0.5

      # Calculate the current direction
      if distance != 0:
        current_direction = (dx / distance, dy / distance)
      else:
        current_direction = last_direction

      # Determine if we need to start a new line segment
      if last_direction is not None:
        # Calculate dot product to see if direction changes significantly
        dot_product = current_direction[0] * last_direction[0] + current_direction[1] * last_direction[1]
        
        # If the direction changes or the distance is too large, increment the change counter
        if dot_product < direction_threshold or distance > distance_threshold:
          consistent_change_counter += 1
        else:
          consistent_change_counter = 0

        # Only start a new line if we exceed the consistent change threshold
        if consistent_change_counter >= consistent_change_threshold:
          lines.append((current_line_start, last_position))
          current_line_start = (x, y)
          consistent_change_counter = 0  # Reset the counter after creating a new line

      last_direction = current_direction
      last_position = (x, y)

  # Store the last line if applicable
  if current_line_start and last_position and current_line_start != last_position:
    lines.append((current_line_start, last_position))

  # Print the analyzed lines
  for i, line in enumerate(lines):
    print(f"Line {i + 1}: Start {line[0]}, End {line[1]}")
  print(f"Total Lines: {len(lines)}")

  visualize_lines(mouse_move_events)



if __name__ == "__main__":
  load_mouse_events()
  analyze_movements()
  analyze_mouse_lines()
  # analyze_clicks()
