def count_passengers(node):
    # Count the number of passengers, ignoring whether they are entering or leaving
    return sum(1 for part in node.split(',') if part.strip() not in ['0', ''])

def process_dot_code(dot_code):
    clusters = {}  # Dictionary to hold nodes for each cluster
    edges = []  # List to hold edges

    for line in dot_code.split('\n'):
        line = line.strip()
        if '->' in line:  # It's an edge
            edges.append(line)
        elif '"' in line:  # It's a node
            node = line.strip('"')
            num_passengers = count_passengers(node)
            clusters.setdefault(num_passengers, []).append(node)

    # Construct the final DOT code with reordered clusters
    processed_lines = ['digraph G {']
    for num_passengers in sorted(clusters.keys()):
        processed_lines.append(f'    subgraph cluster_{num_passengers} {{')
        processed_lines.append('        peripheries=0;')
        for node in clusters[num_passengers]:
            processed_lines.append(f'        "{node}";')
        processed_lines.append('    }')
    # Add edges
    for edge in edges:
        processed_lines.append(f'    {edge}')
    processed_lines.append('}')

    return '\n'.join(processed_lines)

# Example usage
dot_code = '''

ddigraph G {
    edge [color="#08415C"];
    subgraph cluster_0 {
        peripheries=0;
        node [style=filled fontcolor="white" fillcolor="#08415C" color="#08415C"];
        "0, 0, 0";
    }
    
    subgraph cluster_1 {
        peripheries=0
        node [style=filled fontcolor="#08415C" fillcolor="#D6DCE4" color="#D6DCE4"];
        "0, 0, 0" -> "1⁺, 0, 0";
        "0, 0, 0" -> "2⁺, 0, 0";
        "0, 0, 0" -> "3⁺, 0, 0";
        "1⁺, 0, 0" -> "1⁻, 0, 0";
        "2⁺, 0, 0" -> "2⁻, 0, 0";
        "3⁺, 0, 0" -> "3⁻, 0, 0";

        "1⁻, 0, 0" -> "0, 0, 0";
        "1⁻, 0, 0" -> "2⁺, 0, 0";
        "1⁻, 0, 0" -> "3⁺, 0, 0";
        "2⁻, 0, 0" -> "0, 0, 0";
        "2⁻, 0, 0" -> "1⁺, 0, 0";
        "2⁻, 0, 0" -> "3⁺, 0, 0";
        "3⁻, 0, 0" -> "0, 0, 0";
        "3⁻, 0, 0" -> "1⁺, 0, 0";
        "3⁻, 0, 0" -> "2⁺, 0, 0";
    }
    
    subgraph cluster_2 {
        peripheries=0
        node [style=filled fontcolor="#08415C" fillcolor="#f3f3f3" color="#D6DCE4"];
        "1⁺, 0, 0" -> "2⁺, 1, 0";
        "1⁺, 0, 0" -> "3⁺, 1, 0";
        "2⁺, 0, 0" -> "1⁺, 2, 0";
        "2⁺, 0, 0" -> "3⁺, 2, 0";
        "3⁺, 0, 0" -> "1⁺, 3, 0";
        "3⁺, 0, 0" -> "2⁺, 3, 0";
        
        "1⁺, 2, 0" -> "2⁻, 1, 0";
        "1⁺, 2, 0" -> "1⁻, 2, 0";
        "1⁺, 3, 0" -> "3⁻, 1, 0";
        "1⁺, 3, 0" -> "1⁻, 3, 0";
        "2⁺, 1, 0" -> "2⁻, 1, 0";
        "2⁺, 1, 0" -> "1⁻, 2, 0";
        "2⁺, 3, 0" -> "3⁻, 2, 0";
        "2⁺, 3, 0" -> "2⁻, 3, 0";
        "3⁺, 1, 0" -> "1⁻, 3, 0";
        "3⁺, 1, 0" -> "3⁻, 1, 0";
        "3⁺, 2, 0" -> "2⁻, 3, 0";
        "3⁺, 2, 0" -> "3⁻, 2, 0";

        "1⁻, 2, 0" -> "2⁻, 0, 0";
        "1⁻, 3, 0" -> "3⁻, 0, 0";
        "2⁻, 3, 0" -> "3⁻, 0, 0";
        "2⁻, 1, 0" -> "1⁻, 0, 0";
        "3⁻, 1, 0" -> "1⁻, 0, 0";
        "3⁻, 2, 0" -> "2⁻, 0, 0";
        
        "1⁻, 2, 0" -> "3⁺, 2, 0";
        "1⁻, 3, 0" -> "2⁺, 3, 0";
        "2⁻, 3, 0" -> "1⁺, 3, 0";
        "2⁻, 1, 0" -> "3⁺, 1, 0";
        "3⁻, 1, 0" -> "2⁺, 1, 0";
        "3⁻, 2, 0" -> "1⁺, 2, 0";
    }
    subgraph cluster_3 {
        node [fontcolor="#08415C" color="#08415C"];
        "1⁺, 2, 0" -> "3⁺, 2, 1";
        "1⁺, 3, 0" -> "2⁺, 1, 3";
        "2⁺, 1, 0" -> "3⁺, 1, 2";
        "2⁺, 3, 0" -> "1⁺, 2, 3";
        "3⁺, 1, 0" -> "2⁺, 3, 1";
        "3⁺, 2, 0" -> "1⁺, 3, 2";
        
        
        //ChatGPT:
        "3⁺, 2, 1" -> "3⁻, 2, 1"; // Passenger 3 leaves
        "3⁺, 2, 1" -> "2⁻, 3, 1"; // Passenger 2 leaves
        "3⁺, 2, 1" -> "1⁻, 3, 2"; // Passenger 1 leaves
        
        "2⁺, 1, 3" -> "2⁻, 1, 3"; // Passenger 2 leaves
        "2⁺, 1, 3" -> "1⁻, 2, 3"; // Passenger 1 leaves
        "2⁺, 1, 3" -> "3⁻, 1, 2"; // Passenger 3 leaves
        
        "3⁺, 1, 2" -> "3⁻, 1, 2"; // Passenger 3 leaves
        "3⁺, 1, 2" -> "1⁻, 3, 2"; // Passenger 1 leaves
        "3⁺, 1, 2" -> "2⁻, 3, 1"; // Passenger 2 leaves
        
        "1⁺, 2, 3" -> "1⁻, 2, 3"; // Passenger 1 leaves
        "1⁺, 2, 3" -> "2⁻, 1, 3"; // Passenger 2 leaves
        "1⁺, 2, 3" -> "3⁻, 2, 1"; // Passenger 3 leaves
        
        "2⁺, 3, 1" -> "2⁻, 3, 1"; // Passenger 2 leaves
        "2⁺, 3, 1" -> "3⁻, 2, 1"; // Passenger 3 leaves
        "2⁺, 3, 1" -> "1⁻, 2, 3"; // Passenger 1 leaves
        
        "1⁺, 3, 2" -> "1⁻, 3, 2"; // Passenger 1 leaves
        "1⁺, 3, 2" -> "3⁻, 1, 2"; // Passenger 3 leaves
        "1⁺, 3, 2" -> "2⁻, 1, 3"; // Passenger 2 leaves
    
    
        //Highly unclear
        "3⁻, 2, 1" -> "2⁻, 1, 0"; // Passenger 2 leaves
        "3⁻, 2, 1" -> "1⁻, 2, 0"; // Passenger 1 leaves
        "2⁻, 3, 1" -> "3⁻, 2, 0"; // Passenger 3 leaves
        "2⁻, 3, 1" -> "1⁻, 3, 0"; // Passenger 1 leaves
        "1⁻, 3, 2" -> "3⁻, 1, 0"; // Passenger 3 leaves
        "1⁻, 3, 2" -> "2⁻, 3, 0"; // Passenger 2 leaves
        "2⁻, 1, 3" -> "1⁻, 2, 0"; // Passenger 1 leaves
        "2⁻, 1, 3" -> "3⁻, 2, 0"; // Passenger 3 leaves
        "1⁻, 2, 3" -> "2⁻, 1, 0"; // Passenger 2 leaves
        "1⁻, 2, 3" -> "3⁻, 1, 0"; // Passenger 3 leaves
        "3⁻, 1, 2" -> "1⁻, 3, 0"; // Passenger 1 leaves
        "3⁻, 1, 2" -> "2⁻, 3, 0"; // Passenger 2 leaves
        "2⁻, 1, 3" -> "1⁻, 3, 0"; // Passenger 1 leaves
        "2⁻, 1, 3" -> "3⁻, 1, 0"; // Passenger 3 leaves
        "3⁻, 2, 1" -> "2⁻, 1, 0"; // Passenger 2 leaves
        "3⁻, 2, 1" -> "1⁻, 2, 0"; // Passenger 1 leaves
        "1⁻, 3, 2" -> "3⁻, 2, 0"; // Passenger 3 leaves
        "1⁻, 3, 2" -> "2⁻, 3, 0"; // Passenger 2 leaves
        "3⁻, 1, 2" -> "1⁻, 2, 0"; // Passenger 1 leaves
        "3⁻, 1, 2" -> "2⁻, 1, 0"; // Passenger 2 leaves
        "2⁻, 3, 1" -> "3⁻, 2, 0"; // Passenger 3 leaves
        "2⁻, 3, 1" -> "1⁻, 3, 0"; // Passenger 1 leaves
        "1⁻, 2, 3" -> "2⁻, 1, 0"; // Passenger 2 leaves
        "1⁻, 2, 3" -> "3⁻, 2, 0"; // Passenger 3 leaves
    }
}
'''


sorted_dot_code = process_dot_code(dot_code)
print(sorted_dot_code)
