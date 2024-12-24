#!/usr/bin/python3
import networkx as nx
from pyvis.network import Network

G = nx.DiGraph()
added_nodes = set()
mp = dict()

with open('input') as f:
    lines = f.readlines()
    op_num = 0;
    for line in lines:
        if len(line.strip()) == 0:
            continue
        if ':' in line:
            name = line[:line.find(':')].strip()
            val = line[line.find(':')+1:].strip()
            print(f"Node {name}")
            if name not in added_nodes:
                G.add_node(name)
                added_nodes.add(name)
        else:
            lhs: str = line[:line.find('->')].strip()
            rhs: str = line[line.find('->')+2:].strip()
            operation: str = ""
            if "AND" in lhs:
                operation = "AND"
            elif "XOR" in lhs:
                operation = "XOR"
            elif "OR" in lhs:
                operation = "OR"
            else:
                # print(f'"{lhs}"')
                # print(f"'{line}'")
                assert(False)
            lnode = lhs[:lhs.find(operation)].strip()
            rnode = lhs[lhs.find(operation) + len(operation):].strip()
            print(f"{lnode} {operation} {rnode} -> {rhs}")
            if rhs not in added_nodes:
                G.add_node(rhs)
                added_nodes.add(rhs)
            if lnode not in added_nodes:
                G.add_node(lnode)
                added_nodes.add(lnode)
            if rnode not in added_nodes:
                G.add_node(rnode)
                added_nodes.add(rnode)
            operation_name = f"{operation}{op_num}"
            G.add_node(operation_name)
            G.add_edge(lnode, operation_name)
            G.add_edge(rnode, operation_name)
            G.add_edge(operation_name, rhs)
            op_num = op_num + 1

net = Network(
    directed = True,
    # select_menu = True, # Show part 1 in the plot (optional)
    # filter_menu = True, # Show part 2 in the plot (optional)
)
net.show_buttons() # Show part 3 in the plot (optional)
net.from_nx(G) # Create directly from nx graph
net.save_graph(name='doctest-output/test.html')

print("Hello World!!");
