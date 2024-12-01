from pynput import keyboard
from Tree import TreeNode

# Initialize the root of the tree
root = TreeNode("root")

# Keep track of the last logged character and time
last_char = None
last_time = None
current_node = root

def end():
  # print("HI")
  print(root)

def log(char, timestamp):
  print(char)
  if char == keyboard.Key.esc:
    end()
    return

  global last_char, last_time, current_node

  # If the current node is None, reset to root
  if current_node is None:
    current_node = root
  
  # If there was a previous character logged
  if last_char is not None:
    time_diff = timestamp - last_time
    
    # If the time difference is within a threshold, we consider it a cluster
    if time_diff < 0.2:  # 1 second threshold for clustering
      # Add the current character as a child of the current node
      for child in current_node.children:
        if child.name == char:
          child.strength += 1
          current_node = child
          break
      else:
        new_node = TreeNode(char)
        current_node = current_node.add_child(new_node)
    else:
      # If time difference is too large, start a new cluster
      found = False
      for child in root.children:
        if child.name == char:
          child.strength += 1
          current_node = child
          found = True
          break
      if not found:
        # Create a new cluster starting with the current character
        print("New cluster")
        new_node = TreeNode(char)
        current_node = root.add_child(new_node)
  else:
    # If this is the first character, add it to the root
    new_node = TreeNode(char)
    current_node = root.add_child(new_node)
  
  # Update the last logged character and time
  last_char = char
  last_time = timestamp