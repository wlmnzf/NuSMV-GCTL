def dot_to_json(file_in):

    import networkx

    from networkx.readwrite import json_graph

    import pydot

    graph_netx = networkx.drawing.nx_pydot.read_dot(file_in)

    graph_json = json_graph.node_link_data( graph_netx )

    return json_graph.node_link_data(graph_netx)

print(dot_to_json("/home/wanglimin/NuSMV-2.4.3/nusmv/spec.dot"))
