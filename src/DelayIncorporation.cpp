#include "DARPH.h"
#include "RollingHorizon.h"

template<int Q>
void RollingHorizon<Q>::incorporate_delay(std::stringstream& name, IloEnv& env, IloModel& model, IloNumVarArray& B, IloRangeArray& fixed_B) {
    std::map <NODE, double> node_delay;

    std::sort(fixed_edges.begin(), fixed_edges.end(),
        [this](const ARC& a, const ARC& b) {
            return this->active_node[a[1][0]-1].second < this->active_node[b[1][0]-1].second;
        }
    );
    std::cout << MANJ_GREEN << "FIXED EDGES: " << FORMAT_STOP << std::endl;

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
            print_node("", MANJ_GREEN, from, " -> ", n);
            print_node("", MANJ_GREEN, to, " ", n);
            std::cout << "RANDOM delay of " << convertDoubleToMinutes(bv_delay) << " min\n";
            node_delay[to] += bv_delay;
        } else {
            print_node("", MANJ_GREEN, from, " -> ", n);
            print_node("", MANJ_GREEN, to, " no independent delay\n", n);
        }
        
        //(to oder delayed_nodes[to]) und delayed_nodes übergeben
        propagate_delay(to, node_delay);

        double& toEventTime = active_node[passengerTo].second;
        toEventTime += node_delay[to];
        
        print_node("\t", MANJ_GREEN, to, " TOTAL delay of ", n);
        std::cout << convertDoubleToMinutes(node_delay[to]) << " min\n";

        fixed_B[vmap[to]] = IloRange(env,
                                    toEventTime - epsilon, 
                                    B[vmap[to]], 
                                    toEventTime + epsilon, 
                                    name.str().c_str());
        
        model.add(fixed_B[vmap[to]]);
        name.str("");  
    }
}

template<int Q>
//nur a und delayed_nodes als Parameter, 
void RollingHorizon<Q>::propagate_delay(NODE delayed_event, std::map<NODE, double>& node_delay) {
    for (const auto& fixed_arc: fixed_edges)
    {
        NODE start_event = fixed_arc[0];
        NODE dest_event = fixed_arc[1];

        if(start_event == delayed_event) {

            if(node_delay[delayed_event] == 0) {
                print_node("\t", MANJ_GREEN, start_event, " propagated ZERO delay to ", n);
                print_node("", MANJ_GREEN, dest_event, "\n", n);
                return;
            }

            print_node("\t", MANJ_GREEN, start_event, " propagated delay of ", n);
            std::cout << node_delay[delayed_event] << " min to ";
            print_node("", MANJ_GREEN, dest_event, "\n", n);

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

template class RollingHorizon<3>;
template class RollingHorizon<6>;
