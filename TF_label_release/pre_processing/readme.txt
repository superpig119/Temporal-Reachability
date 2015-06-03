   compile: "g++ -o pre_check precheck.cpp -O3"
   run: ./pre_check ../dataset/p2p_scc.txt -i ../index/p2p_scc
   "../dataset/p2p_scc.txt" : the input DAG
   "../index/p2p_scc" : the file storing index(quey will use this index) after pre_processing 
   note: in this case we need to create a folder called "index" because of "../index/p2p_scc"
