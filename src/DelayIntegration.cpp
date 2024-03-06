#include "DARPH.h"
#include <map>


template <int Q>
DelayIntegration<Q>::DelayIntegration(double probability, double delay, TerminalOutputFormatter<Q>* tof) {
    this->probability = probability;
    this->delay = delay;
    this->tof = tof;
}

template <int Q>
void DelayIntegration<Q>::incorporate_delay(std::stringstream& name,
                                IloEnv& env, 
                                IloModel& model, 
                                IloNumVarArray& B, 
                                IloRangeArray& fixed_B, 
                                std::vector<ARC> fixed_edges,
                                std::pair<NODE,double>* active_node,
                                std::unordered_map <NODE,uint64_t,HashFunction<Q>> vmap,
                                const double epsilon,
                                int n) 
{
    std::map <NODE, double> node_delay;

    std::sort(fixed_edges.begin(), fixed_edges.end(),
        [active_node](const ARC& a, const ARC& b) {
            return active_node[a[1][0]-1].second < active_node[b[1][0]-1].second;
        }
    );
    for(int i = 0; i < tof->get_current_terminal_width(); i++) {
        std::cout << "-";
    }
    std::cout << std::endl << MANJ_GREEN << "FIXED EDGES: " << FORMAT_STOP << std::endl;

    // fix variable B_w for new fixed d 
    for (const auto& a: fixed_edges)
    {
        if constexpr (Q==3)
            name << "fixed_B_(" << a[1][0] << "," << a[1][1] << "," << a[1][2] << ")";
        else
            name << "fixed_B_(" << a[1][0] << "," << a[1][1] << "," << a[1][2] << "," << a[1][3] << "," << a[1][4] << "," << a[1][5] << ")";

        NODE from = a[0];
        NODE to = a[1];
        int passengerFrom = from[0] - 1;
        int passengerTo = to[0] - 1;
        
        if (probability == 1 || dis(gen) <= probability) {
            std::cout << tof->get_printable_node(MANJ_GREEN, from, n) << " -> " << tof->get_printable_node(MANJ_GREEN, to, n);
            std::cout << " RANDOM delay of " << tof->convertDoubleToMinutes(delay) << " min\n";
            node_delay[to] += delay;
        } else {
            std::cout << tof->get_printable_node(MANJ_GREEN, from, n) << " -> " << tof->get_printable_node(MANJ_GREEN, to, n);
            std::cout << " no independent delay\n";
        }
        
        //(to oder delayed_nodes[to]) und delayed_nodes übergeben
        propagate_delay(to, node_delay, fixed_edges, n);

        double& toEventTime = active_node[passengerTo].second;
        toEventTime += node_delay[to];
        
        std::cout << "\t" << tof->get_printable_node(MANJ_GREEN, to, n);
        std::cout  << " TOTAL delay of " << tof->convertDoubleToMinutes(node_delay[to]) << " min\n";

        fixed_B[vmap[to]] = IloRange(env,
                                    toEventTime - epsilon, 
                                    B[vmap[to]], 
                                    toEventTime + epsilon, 
                                    name.str().c_str());
        
        model.add(fixed_B[vmap[to]]);
        name.str("");  
    }
}

template <int Q>
void DelayIntegration<Q>::propagate_delay(NODE delayed_event, 
                        std::map<NODE, double> &node_delay, 
                        std::vector<ARC> fixed_edges, 
                        int n) 
{
    for (const auto& fixed_arc: fixed_edges)
    {
        NODE start_event = fixed_arc[0];
        NODE dest_event = fixed_arc[1];

        if(start_event == delayed_event) {

            if(node_delay[delayed_event] == 0) {
                std::cout << "\t" << tof->get_printable_node(MANJ_GREEN, start_event, n) << " propagated ZERO delay to ";
                std::cout << tof->get_printable_node(MANJ_GREEN, dest_event, n) << std::endl;
                return;
            }
            std::cout << "\t" << tof->get_printable_node(MANJ_GREEN, start_event, n) << " propagated delay of ";
            std::cout << tof->convertDoubleToMinutes(node_delay[delayed_event]) << " min to ";
            std::cout << tof->get_printable_node(MANJ_GREEN, dest_event, n) << std::endl;

            node_delay[dest_event] += node_delay[delayed_event];
            return;
        }
    }
}
/*Alternative mit späterem Aufruf 
template<int Q>
void RollingHorizon<Q>::propagate_delay_after_fixing(std::map<NODE, double>& delayed_nodes) {
    for (const auto& fixed_arc: fixed_edges)
    {
        NODE from = fixed_arc[0];
        NODE to = fixed_arc[1];
        int passengerFrom = from[0] - 1;
        int passengerTo = to[0] - 1;
        double& toEventTime = active_node[passengerTo].second;

        for(auto& [delayed_node, propagated_delay]: delayed_nodes) {
            if (from == delayed_node) {
                toEventTime += propagated_delay;
                std::cout << from << " -> " << to << " propagated delay of "  << propagated_delay << " min\n";
                delayed_nodes[to] += propagated_delay;
                break;
            }
        }
    }
}*/

template class DelayIntegration<3>;
template class DelayIntegration<6>;
