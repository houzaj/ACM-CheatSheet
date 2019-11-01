mt19937 ren(time(NULL));
uniform_int_distribution<int> dist(1, n);

int num_nums = i * 10000;
printf("%d\n", num_nums);
while(num_nums--) {
    printf("%d ", dist(ren));
}
