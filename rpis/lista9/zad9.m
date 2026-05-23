X = csvread('z0909.csv');
k = 20;
x_mean = mean(X);

p_z_daszkiem = x_mean / k;
printf("estymator mle: %f\n", p_z_daszkiem);