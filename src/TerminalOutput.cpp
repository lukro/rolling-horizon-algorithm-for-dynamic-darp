#include "DARPH.h"
#include "RollingHorizon.h"

template<int Q>
std::string RollingHorizon<Q>::get_printable_header(int num_milps, double time) {
    std::stringstream header;
    int terminal_width = get_current_terminal_width();

    std::stringstream milp_stream;
    milp_stream << "MILP " << std::to_string(num_milps) << " at " << convertDoubleToMinutes(time) << " min";

    int length_space = (terminal_width - milp_stream.str().length()) / 2 - 2; // Subtract 2 for the spaces
    std::string space = std::string(length_space, ' ');
    header << std::endl << WHITE_MANJ_GREEN_BG << space << milp_stream.str() << space;

    // If the terminal width is odd and the milp_str length is even (or vice versa), print an extra dash
    if ((terminal_width - milp_stream.str().length()) % 2 != 0) { // Subtract 2 for the spaces
        std::cout << " ";
    }
    header << FORMAT_STOP << std::endl;
    return header.str();
}

template<int Q>
std::string RollingHorizon<Q>::get_printable_event_block(int node, double time, int& characters_printed, int terminal_width) {
    std::stringstream output;
    if (characters_printed + 14 > terminal_width) {
        output << std::endl;
        characters_printed = 0;
    }

    std::ostringstream event;
    //+ instead of << at the end because of setw
    if (node > n)
        event << std::setw(3) << "-" + std::to_string(node - n);
    else
        event << std::setw(3) << "+" + std::to_string(node);

    if (time < time_passed) 
        output << YELLOW_UNDERLINED << event.str() << WHITE;
    else 
        output << WHITE_YELLOW_BG << event.str() << BLACK_YELLOW_BG;
   
    output << std::setw(7) << std::setfill(' ') << convertDoubleToMinutes(time) << FORMAT_STOP << "  ";
    
    characters_printed += 14;  // Add the length of the output block to the counter
    return output.str();
}

template<int Q>
int RollingHorizon<Q>::get_current_terminal_width() {
    struct winsize w;
    if (isatty(STDOUT_FILENO)) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    } else {
        // If the output is not a terminal, set a default width
        w.ws_col = 100;
    }
    return w.ws_col;
    
}

template<int Q>
void RollingHorizon<Q>::print_node(std::string before, std::string color, NODE node, std::string after, int n) {
    std::string node_string;
    if(node[0] < n)
        node_string = "(+" + std::to_string(node[0]) + ",";
    else
        node_string = "(-" + std::to_string(node[0] - n) + ",";
    for(int i = 1; i < node.size(); i++) {
        if(node[i] == 0 && i < node.size() - 2){
            node_string += "0..0";
            break;
        }
        node_string += std::to_string(node[i]);
        if(i < node.size() - 1) 
            node_string += ",";
    }
    node_string += ")";
    std::cout << before << color << node_string << FORMAT_STOP << after;
}

template<int Q>
std::string RollingHorizon<Q>::convertDoubleToMinutes(double time) {
    std::stringstream stream;
    int minutes = time;
    int seconds = (time - minutes) * 60;
    stream << minutes << ":" << std::fixed << std::setw(2) << std::setfill('0') << seconds;
    return stream.str();
}

template class RollingHorizon<3>;
template class RollingHorizon<6>;
