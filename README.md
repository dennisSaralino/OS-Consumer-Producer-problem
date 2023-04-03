Compiled and ran with
```
  gcc producer.c -pthread -lrt -o producer
  gcc consumer.c -pthread -lrt -o consumer
  ./producer & ./consumer &
```

(Using semaphores) Producer produces two integers and stores them in shared memory. 
Consumer then reads and removes the two values. The process is repeated for a total of three iterations.

