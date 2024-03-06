#include "DARPH.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>

template <int Q>
TerminalOutputFormatter<Q>::TerminalOutputFormatter() {
    this->event_char_counter = 0;
    this->terminal_width = get_current_terminal_width();
}

template <int Q>
std::string TerminalOutputFormatter<Q>::get_printable_header(int num_milps, double time) {
    std::stringstream header;
    int terminal_width = get_current_terminal_width();

    std::stringstream milp_stream;
    milp_stream << "MILP " << std::to_string(num_milps) << " at " << convertDoubleToMinutes(time) << " min";

    int length_space = (terminal_width - milp_stream.str().length()) / 2;
    std::string space = std::string(length_space, ' ');
    header << std::endl << WHITE_MANJ_GREEN_BG << space << milp_stream.str() << space;

    if ((terminal_width - milp_stream.str().length()) % 2 != 0) { 
        header << " ";
    }
    header << FORMAT_STOP << std::endl;
    return header.str();
}

template <int Q>
std::string TerminalOutputFormatter<Q>::get_printable_event_block(int node_event, double time, double time_passed, int n) {
    std::stringstream output;
    if (this->event_char_counter + 12 > get_current_terminal_width()) {
        output << std::endl;
        this->event_char_counter = 0;
    }

    std::ostringstream event;
    //+ instead of << at the end because of setw
    if (node_event > n)
        event << std::setw(3) << "-" + std::to_string(node_event - n);
    else
        event << std::setw(3) << "+" + std::to_string(node_event);
    if (time < time_passed) 
        output << YELLOW_UNDERLINED << event.str() << WHITE;
    else 
        output << WHITE_YELLOW_BG << event.str() << BLACK_YELLOW_BG;
   
    output << std::setw(7) << std::setfill(' ') << convertDoubleToMinutes(time) << FORMAT_STOP << "  ";
    
    std::string ostr = output.str();
    this->event_char_counter += 12;  // Add the length of the output block to the counter
    return ostr;
}

template <int Q> 
std::string TerminalOutputFormatter<Q>::get_printable_node(const std::string color, const std::array<int,Q> node, int n) {
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
    node_string = color + node_string + FORMAT_STOP;
    return node_string;
}

template <int Q>
int TerminalOutputFormatter<Q>::get_current_terminal_width() {
    struct winsize w;
    if (isatty(STDOUT_FILENO)) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    } else {
        // If the output is not a terminal, set a default width
        w.ws_col = 100;
    }
    this->terminal_width = w.ws_col;
    return w.ws_col;
    
}

template <int Q>
std::string TerminalOutputFormatter<Q>::convertDoubleToMinutes(double time) {
    std::stringstream stream;
    int minutes = time;
    int seconds = (time - minutes) * 60;
    stream << minutes << ":" << std::fixed << std::setw(2) << std::setfill('0') << seconds;
    return stream.str();
}

template <int Q>
void TerminalOutputFormatter<Q>::reset_event_char_counter() {
    this->event_char_counter = 0;
}

template class TerminalOutputFormatter<3>;
template class TerminalOutputFormatter<6>;
