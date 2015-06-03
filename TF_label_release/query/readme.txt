   compile: "g++ -o queryscc queryscc.cpp -O3"
   run: ./queryscc -scc 48438 -i ../index/p2p_scc -q query_file/p2p_query.txt 
   "48438" : the total number of vertex in DAG
   "../index/p2p_scc" : the index file, which should be the same as the index file in pre_processing
   "query_file/p2p_query.txt" : the query file, which is randomly generated
   (you can generate the query file by your own too)
   the default number of query pair is 1000000
