#!/usr/bin/python3
import graphviz

dot = graphviz.Graph()
added_nodes = set()
ors = set();
ands = set();
exors = set();
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
                dot.node(name, label=f"{name}{val}")
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
                dot.node(rhs, label=rhs)
                added_nodes.add(rhs)
            if lnode not in added_nodes:
                dot.node(lnode, label=lnode)
                added_nodes.add(lnode)
            if rnode not in added_nodes:
                dot.node(rnode, label=rnode)
                added_nodes.add(rnode)
            operation_name = f"{operation}{op_num}"
            dot.node(operation_name, label=operation)
            dot.edge(lnode, operation_name)
            dot.edge(rnode, operation_name)
            dot.edge(operation_name, rhs)
            op_num = op_num + 1

dot.render('doctest-output/round-table.gv', view=True)  # doctest: +SKIP
'doctest-output/round-table.gv.pdf'



print("Hello World!!");
