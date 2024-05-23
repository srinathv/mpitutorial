EXECS=reduce_avg reduce_stddev reduce_int64_t_stddev
MPICC?=mpicc

all: ${EXECS}

reduce_avg: reduce_avg.c
	${MPICC} -g -O3 -o reduce_avg reduce_avg.c

reduce_stddev: reduce_stddev.c
	${MPICC} -g -O3 -o reduce_stddev reduce_stddev.c -lm

reduce_int64_t_stddev: reduce_int64_t_stddev.c
	${MPICC} -g -O3 -o reduce_int64_t_stddev reduce_int64_t_stddev.c -lm
clean:
	rm -f ${EXECS}
