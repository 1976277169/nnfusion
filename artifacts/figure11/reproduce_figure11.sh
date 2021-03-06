# run experiments and get logs
bash codegen_and_build.sh
bash run_all.sh

# process log
python process_log.py

# draw figure
# paper result
cd paper_result/
gnuplot gpu1_batch_cuda_multifig.plt
cd ..
# reproduce result
cd reproduce_result/
gnuplot gpu1_batch_cuda_multifig.plt
cd ..