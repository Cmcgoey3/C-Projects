/**
 * Name: Connor McGoey
 * Date: February 9, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // Test to ensure only two additional command line parameters are passed to the program
    if (!(argc == 3))
    {
        printf("Proper usage is ./assignment-2 <4 digit integer> <4 digit integer>\n");
        return 0;
    }
    // Test to ensure that both of the numbers passed into the program are of length 4
    if ((!(strlen(argv[1]) == 4)) || (!(strlen(argv[2]) == 4))) {
        printf("Proper usage is ./assignment-2 <4 digit integer> <4 digit integer>\n");
        return 0;
    }    

    // Initialize the two numbers a and b, then partition them into their sub-numbers by using division by 100 and modulo
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int a1 = a / 100;
    int a2 = a % 100;
    int b1 = b / 100;
    int b2 = b % 100;

    printf("Your integers are %d %d\n", a, b);

    // Initialize the pid for forking, and both a child and parent port for communication
    pid_t pid;
    int parentPort[2];
    int childPort[2];

    // Test to ensure that the parent port is initialized correctly
    if (pipe(parentPort) < 0)
    {
        perror("pipe error");
        exit(0);
    }

    // Test to ensure that the child port is initialized correctly
    if (pipe(childPort) < 0)
    {
        perror("pipe error");
        exit(0);
    }

    // Create the fork
    pid = fork();
    if (pid < 0)        // Forking failed
    {
        perror("fork error");
        exit(0);
    }
    else if (pid > 0)   // Parent process
    {
        printf("Parent (PID %d): created child (PID %d)\n", getpid(), pid);

        // Pass a1 and b1 into the pipe and await child processing save value into A
        printf("\n###\n# Calculating X\n###\n");
        int A;
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        write(parentPort[1], &a1, sizeof(a1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
        write(parentPort[1], &b1, sizeof(b1));
        read(childPort[0], &A, sizeof(A));
        printf("Parent (PID %d): Received %d from child\n", getpid(), A);
        // Calculate X using math pow function
        int X = A * (pow(10, 4));

        // Pass a1 and b2 into the pipe and await child processing, save value into C
        printf("\n###\n# Calculating Y\n###\n");
        int C;
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a1);
        write(parentPort[1], &a1, sizeof(a1));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
        write(parentPort[1], &b2, sizeof(b2));
        read(childPort[0], &C, sizeof(C));
        printf("Parent (PID %d): Received %d from child\n", getpid(), C);
        
        // Pass a2 and b1 into the pipe and await child processing, save value into B
        int B;
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        write(parentPort[1], &a2, sizeof(a2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b1);
        write(parentPort[1], &b1, sizeof(b1));
        read(childPort[0], &B, sizeof(B));
        printf("Parent (PID %d): Received %d from child\n", getpid(), B);
        // Calculate Y using B, C, and the math pow function
        int Y = (B + C) * pow(10, 2);
        

        printf("\n###\n# Calculating Z\n###\n");
        int D;
        // Pass a2 and b2 into the pipe and await child processing, save value into D
        printf("Parent (PID %d): Sending %d to child\n", getpid(), a2);
        write(parentPort[1], &a2, sizeof(a2));
        printf("Parent (PID %d): Sending %d to child\n", getpid(), b2);
        write(parentPort[1], &b2, sizeof(b2));
        read(childPort[0], &D, sizeof(D));
        printf("Parent (PID %d): Received %d from child\n\n", getpid(), D);
        // Calculate Z using the math pow function
        int Z = D * pow(10, 0);

        // result/product is now the sum of X, Y, and Z
        int result = X + Y + Z;
        printf("%d*%d == %d + %d + %d == %d\n\n\n\n", a, b, X, Y, Z, result);
        return 0;
    }
    else if (pid == 0)  // Child process
    {
        int num1 = 0;   // num1 to be used to store the first of two values sent by parent process
        int num2 = 0;   // num2 to be used to store the second of two values sent by parent process

        // Read the two numbers (a1 & b1) from the parent pipe, multiple them, and pass them through the child pipe
        read(parentPort[0], &num1, sizeof(num1));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num1);
        read(parentPort[0], &num2, sizeof(num2));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num2);
        int A = num1 * num2;
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), A);
        write(childPort[1], &A, sizeof(A));

        // Read the two numbers (a1 & b2) from the parent pipe, multiple them, and pass them through the child pipe
        read(parentPort[0], &num1, sizeof(num1));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num1);
        read(parentPort[0], &num2, sizeof(num2));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num2);
        int B = num1 * num2;
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), B);
        write(childPort[1], &B, sizeof(B));

        // Read the two numbers (a2 & b1) from the parent pipe, multiple them, and pass them through the child pipe
        read(parentPort[0], &num1, sizeof(num1));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num1);
        read(parentPort[0], &num2, sizeof(num2));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num2);
        int C = num1 * num2;
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), C);
        write(childPort[1], &C, sizeof(C));

        // Read the two numbers (a2 & b2) from the parent pipe, multiple them, and pass them through the child pipe
        read(parentPort[0], &num1, sizeof(num1));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num1);
        read(parentPort[0], &num2, sizeof(num2));
        printf("\tChild (PID %d): Received %d from parent\n", getpid(), num2);
        int D = num1 * num2;
        printf("\tChild (PID %d): Sending %d to parent\n", getpid(), D);
        write(childPort[1], &D, sizeof(D));
        return 0;
    }
    return 0;
}
