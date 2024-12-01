from collections import defaultdict
from Tree import TreeNode

log_file_path = "Logs/tree_output.txt"

def analyze(root):
  general_analyze(root)


def general_analyze(root):
  global LOG
  # Analyze the tree structure
  total_nodes = 0
  total_strength = 0
  max_depth = 0
  frequent_paths = defaultdict(int)

  def traverse(node, depth=0, current_path=None):
    nonlocal total_nodes, total_strength, max_depth
    if current_path is None:
      current_path = []

    # Update analysis metrics
    total_nodes += 1
    total_strength += node.strength
    max_depth = max(max_depth, depth)

    # Track the current path
    current_path.append(str(node.name))
    if not node.children:
      # If it's a leaf node, add the current path to frequent_paths
      path_str = " -> ".join(current_path)
      frequent_paths[path_str] += 1
    else:
      # Recursively traverse the children
      for child in node.children:
        traverse(child, depth + 1, current_path.copy())

  # Start traversal from root
  traverse(root)

    # Write analysis results to the log file
  with open("Logs/tree_output.txt", "a") as file:
    file.write("\n\nGeneral Analysis of Tree:\n")
    file.write(f"Total Nodes: {total_nodes}\n")
    file.write(f"Total Strength: {total_strength}\n")
    file.write(f"Max Depth: {max_depth}\n")
    file.write("Most Frequent Paths:\n")
    for path, freq in sorted(frequent_paths.items(), key=lambda item: item[1], reverse=True)[:5]:
      file.write(f"{path} (Frequency: {freq})\n")


