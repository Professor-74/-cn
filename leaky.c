#include <stdio.h>

int main() {
    int bucketSize, outputRate, n, packetSize;
    int bucket = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);

    printf("Enter output rate: ");
    scanf("%d", &outputRate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        printf("\nEnter packet size %d: ", i);
        scanf("%d", &packetSize);

        if(bucket + packetSize <= bucketSize) {
            bucket += packetSize;
            printf("Packet added to bucket\n");
        } else {
            printf("Packet dropped (bucket overflow)\n");
        }

        printf("Bucket content before leak: %d\n", bucket);

        if(bucket < outputRate)
            bucket = 0;
        else
            bucket -= outputRate;

        printf("Bucket content after leak: %d\n", bucket);
    }

    return 0;
}
