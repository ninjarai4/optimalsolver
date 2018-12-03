\ //void  search_tree(Full_cube  *p_cube, Search_node  *node_arr, int p_node_index)
\
{\

if (node_arr[p_node_index].remain_depth == 0)\
    {\
    if (test_for_solution(p_cube, node_arr) &&\
        p_current_options->one_solution_only)\
      {} \ // figure out how to quit
    }\
 else\
    {\
\
#pragma omp parallel for num_threads(3) default(shared) reduction(+:n_nodes)  \
  reduction(+:n_tests) reduction(max:sol_found) firstprivate(node_arr,p_cube,p_node_index) if(p_node_index<2)\
/* #pragma omp for schedule(static,1) nowait if(0) */\
    for (register int twist = 0; twist < N_TWIST; twist++)\
        {\
          Search_node *p_node = node_arr+p_node_index;\
		register int virtual_twist, new_sym_factor;\
        p_node[1].follow_type =\
                        (int)twist_on_follow[twist][p_node->follow_type];\
\
        if (p_node[1].follow_type == FOLLOW_INVALID)\
          continue;\
\
        p_node[1].remain_depth = p_node->remain_depth -\
                                    p_current_metric->twist_length[twist];\
        if (p_node[1].remain_depth < 0)\
          continue;\
\
        n_nodes++;\
\
        virtual_twist =\
                    (int)invsym_on_twist_ud[p_node->ud.sym_state][twist];\
        new_sym_factor =\
          (int)twist_x_edge_to_sym[virtual_twist][p_node->ud.edge_state];\
        p_node[1].ud.edge_state =\
                (int)twist_on_edge[virtual_twist][p_node->ud.edge_state];\
        p_node[1].ud.sym_state =\
          (int)sym_x_invsym_to_sym[p_node->ud.sym_state][new_sym_factor];\
        p_node[1].ud.corner_state = (int)sym_on_corner[new_sym_factor]\
          [(int)twist_on_corner[virtual_twist][p_node->ud.corner_state]];\
\
        if (p_node[1].remain_depth <\
                DIST(p_node[1].ud.corner_state, p_node[1].ud.edge_state))\
          continue;\
\
\
        virtual_twist =\
                    (int)invsym_on_twist_rl[p_node->rl.sym_state][twist];\
        new_sym_factor =\
          (int)twist_x_edge_to_sym[virtual_twist][p_node->rl.edge_state];\
        p_node[1].rl.edge_state =\
                (int)twist_on_edge[virtual_twist][p_node->rl.edge_state];\
        p_node[1].rl.sym_state =\
          (int)sym_x_invsym_to_sym[p_node->rl.sym_state][new_sym_factor];\
        p_node[1].rl.corner_state = (int)sym_on_corner[new_sym_factor]\
          [(int)twist_on_corner[virtual_twist][p_node->rl.corner_state]];\
\
        if (p_node[1].remain_depth <\
                DIST(p_node[1].rl.corner_state, p_node[1].rl.edge_state))\
          continue;\
\
\
        virtual_twist =\
                    (int)invsym_on_twist_fb[p_node->fb.sym_state][twist];\
        new_sym_factor =\
          (int)twist_x_edge_to_sym[virtual_twist][p_node->fb.edge_state];\
        p_node[1].fb.edge_state =\
                (int)twist_on_edge[virtual_twist][p_node->fb.edge_state];\
        p_node[1].fb.sym_state =\
          (int)sym_x_invsym_to_sym[p_node->fb.sym_state][new_sym_factor];\
        p_node[1].fb.corner_state = (int)sym_on_corner[new_sym_factor]\
          [(int)twist_on_corner[virtual_twist][p_node->fb.corner_state]];\
\
        if (p_node[1].remain_depth <\
                DIST(p_node[1].fb.corner_state, p_node[1].fb.edge_state))\
          continue;\
\
\
        p_node[1].twist = twist;\
        p_node[2].twist = -1;\
        search_tree(p_cube, node_arr, p_node_index+1);\
        }\
      }\
\
}
