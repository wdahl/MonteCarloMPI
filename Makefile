run: Homework_7_serial.out Homework_7_distributed.out 

Homework_7_distributed.out: Homework_7_distributed.c timing.c
        mpicc Homework_7_distributed.c timing.c -o Homework_7_distributed.out

Homework_7_serial.out: Homework_7_serial.c timing.c
        gcc -g Homework_7_serial.c timing.c -o Homework_7_serial.out

clean:
        rm *.out
