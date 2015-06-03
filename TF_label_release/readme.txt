1. dataset: 
   the input file is a txt file;
   it corresponds to a DAG.
   the format:(please refer to file "p2p_scc.txt" in folder "dataset" for detail)
   total_vertex_number total_edge_number
   vertex_u u_deg v1 v2...vn
   ...
   
2. pre_processing: 
   compile: "g++ -o pre_check precheck.cpp -O3"
   run: ./pre_check ../dataset/p2p_scc.txt -i ../index/p2p_scc
   "../dataset/p2p_scc.txt" : the input DAG
   "../index/p2p_scc" : the file storing index(quey will use this index) after pre_processing 
   note: in this case we need to create a folder called "index" because of "../index/p2p_scc"
   
3. query
   compile: "g++ -o queryscc queryscc.cpp -O3"
   run: ./queryscc -scc 48438 -i ../index/p2p_scc -q query_file/p2p_query.txt 
   "48438" : the total number of vertex in DAG
   "../index/p2p_scc" : the index file, which should be the same as the index file in pre_processing
   "query_file/p2p_query.txt" : the query file, which is randomly generated
   (you can generate the query file by your own too)
   the default number of query pair is 1000000


