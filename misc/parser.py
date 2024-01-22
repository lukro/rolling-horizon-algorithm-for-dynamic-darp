def reorder_sequence(seq):
    # Split the sequence into parts and remove spaces
    parts = [part.strip() for part in seq.split(',')]
    # Sort based on the numeric value
    sorted_parts = sorted(parts, key=lambda x: int(''.join(filter(str.isdigit, x))))
    return ','.join(sorted_parts)

def process_dot_code(dot_code):
    processed_lines = []
    for line in dot_code.split('\n'):
        # Check if the line contains a node or edge definition
        if "->" in line or '"' in line:
            # Extract the label(s), remove spaces, and reorder them
            line.strip()
            parts = line.split('"')
            for i, part in enumerate(parts):
                if ',' in part:
                    parts[i] = reorder_sequence(part)
            processed_line = '"'.join(parts)
            processed_lines.append(processed_line)
        else:
            processed_lines.append(line)
    return '\n'.join(processed_lines)

# Example usage
dot_code = '''
digraph G {
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
