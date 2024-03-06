// ANSI color codes
#define FORMAT_STOP             "\033[0m"
#define WHITE                   "\033[37m"
#define MANJ_GREEN              "\033[1m\033[38;2;22;160;133m"
#define MANJ_GREEN_BG           "\033[48;2;22;160;133m"
#define YELLOW_UNDERLINED       "\033[33m"  
#define WHITE_YELLOW_BG         "\033[1;37m\033[43m"
#define WHITE_MANJ_GREEN_BG     "\033[1;37m\033[48;2;22;160;133m"
#define BLACK_YELLOW_BG         "\033[0;30m\033[43m"


//TODO: template
    
template <int S>
class TerminalOutputFormatter {
private:
    typedef std::array<int,S> NODE;
    typedef std::array<NODE,2> ARC;
    int terminal_width;
    int event_char_counter;
public: 
    TerminalOutputFormatter();

    std::string get_printable_header(int num_milps, double time);
    std::string get_printable_event_block(int node_event, 
                                        double time, 
                                        double time_passed, 
                                        int n);
    std::string get_printable_node( std::string color, NODE node, int n);
    std::string convertDoubleToMinutes(double time);

    int get_current_terminal_width();
    void reset_event_char_counter();

};

