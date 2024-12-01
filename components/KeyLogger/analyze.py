from collections import defaultdict
from Tree import TreeNode

log_file_path = "Logs/tree_output.txt"

def analyze(root):
  general_analyze(root)
  analyze_average_branching(root)
  analyze_depth_distribution(root)
  analyze_most_frequent_nodes(root)
  analyze_path_length_distribution(root)
  analyze_leaf_node_statistics(root)

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


def analyze_average_branching(root):
  """
  Calculates the average number of children (branching factor) for each node in the tree.
  """
  total_nodes = 0
  total_children = 0

  def traverse(node):
    nonlocal total_nodes, total_children
    total_nodes += 1
    total_children += len(node.children)
    for child in node.children:
      traverse(child)

  traverse(root)
  avg_branching = total_children / total_nodes if total_nodes > 0 else 0
  with open(log_file_path, "a") as file:
    file.write("\n\nAverage Branching Factor:\n")
    file.write(f"Average Branching Factor: {avg_branching}\n")


def analyze_depth_distribution(root):
  """
  Analyzes the depth distribution of the nodes in the tree.
  """
  depth_counts = defaultdict(int)

  def traverse(node, depth=0):
    depth_counts[depth] += 1
    for child in node.children:
      traverse(child, depth + 1)

  traverse(root)
  with open(log_file_path, "a") as file:
    file.write("\n\nDepth Distribution:\n")
    for depth, count in sorted(depth_counts.items()):
      file.write(f"Depth {depth}: {count} nodes\n")


def analyze_most_frequent_nodes(root):
  """
  Identifies the nodes that appear most frequently in the tree.
  """
  node_frequency = defaultdict(int)

  def traverse(node):
    node_frequency[node.name] += 1
    for child in node.children:
      traverse(child)

  traverse(root)
  sorted_nodes = sorted(node_frequency.items(), key=lambda item: item[1], reverse=True)
  with open(log_file_path, "a") as file:
    file.write("\n\nMost Frequent Nodes:\n")
    for name, freq in sorted_nodes[:5]:
      file.write(f"Node '{name}' appears {freq} times\n")


def analyze_path_length_distribution(root):
  """
  Analyzes the distribution of path lengths from the root to each leaf node.
  """
  path_lengths = []

  def traverse(node, length=0):
    if not node.children:
      path_lengths.append(length)
    else:
      for child in node.children:
        traverse(child, length + 1)

  traverse(root)
  with open(log_file_path, "a") as file:
    file.write("\n\nPath Length Distribution:\n")
    if path_lengths:
      for length in set(path_lengths):
        count = path_lengths.count(length)
        file.write(f"Length {length}: {count} paths\n")
      avg_length = sum(path_lengths) / len(path_lengths)
      file.write(f"Average Path Length: {avg_length}\n")
    else:
      file.write("No paths in the tree.\n")


def analyze_leaf_node_statistics(root):
  """
  Provides statistics specifically about the leaf nodes in the tree.
  """
  leaf_nodes = []

  def traverse(node):
    if not node.children:
      leaf_nodes.append(node)
    for child in node.children:
      traverse(child)

  traverse(root)
  with open(log_file_path, "a") as file:
    file.write("\n\nLeaf Node Statistics:\n")
    file.write(f"Total Leaf Nodes: {len(leaf_nodes)}\n")
    if leaf_nodes:
      strengths = [leaf.strength for leaf in leaf_nodes]
      avg_strength = sum(strengths) / len(strengths)
      file.write(f"Average Strength of Leaf Nodes: {avg_strength}\n")
      max_strength = max(strengths)
      min_strength = min(strengths)
      file.write(f"Max Strength of Leaf Nodes: {max_strength}\n")
      file.write(f"Min Strength of Leaf Nodes: {min_strength}\n")
    else:
      file.write("No leaf nodes in the tree.\n")



